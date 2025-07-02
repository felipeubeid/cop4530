#ifndef HASHTABLE_HPP
#define HASHTABLE_HPP

#include "hashtable.h"
#include <sstream>

using namespace cop4530;

    template <typename K, typename V>
    HashTable<K, V>::HashTable(size_t size) : theLists(prime_below(size)), currentSize(0)
    { }

    template <typename K, typename V>
    HashTable<K, V>::~HashTable() 
    { clear(); }

    template <typename K, typename V>
    bool HashTable<K, V>::contains(const K &k) const
    {
        auto & whichList = theLists[myhash(k)];
        for (const auto &whichPair : whichList)
        {
            if (whichPair.first == k)
                return true;
        }
        return false;
        // return find(begin(whichList), end(whichList), k) != end(whichList);
    }

    template <typename K, typename V>
    bool HashTable<K, V>::match(const std::pair<K, V> &kv) const
    {
        auto & whichList = theLists[myhash(kv.first)];
        for (const auto &whichPair : whichList)
        {
            if (whichPair == kv)
                return true;
        }
        return false;
    }

    template <typename K, typename V>
    bool HashTable<K, V>::insert(const std::pair<K, V> & kv)
    {
        auto & whichList = theLists[myhash(kv.first)];
        for (auto &whichPair : whichList)
        {
            if (whichPair.first == kv.first)
            {
                if (whichPair.second == kv.second)
                    return false;
                else
                {
                    whichPair.second = kv.second;
                    return true;
                }
            }
        }
        whichList.push_back(kv);
        if (++currentSize > theLists.size())
            rehash();
        return true;
    }

    template <typename K, typename V>
    bool HashTable<K, V>::insert(std::pair<K,  V> && kv)
    {
        auto & whichList = theLists[myhash(kv.first)];
        for (auto &whichPair : whichList)
        {
            if (whichPair.first == kv.first)
            {
                if (whichPair.second == kv.second)
                    return false;
                else
                {
                    whichPair.second = std::move(kv.second);
                    return true;
                }
            }
        }
        whichList.push_back(std::move(kv));
        if (++currentSize > theLists.size())
            rehash();
        return true;
    }

    template <typename K, typename V>
    bool HashTable<K, V>::remove(const K & k)
    {
        auto & whichList = theLists[myhash(k)];
        for (auto itr = whichList.begin(); itr != whichList.end(); ++itr)
        {
            if (itr->first == k)
            {
                whichList.erase(itr);
                --currentSize;
	            return true;
            }
        }
        return false;
    }

    template <typename K, typename V>
    void HashTable<K, V>::clear()
    { makeEmpty(); }

    template <typename K, typename V>
    bool HashTable<K, V>::load(const char *filename)
    {
        std::ifstream infile(filename);
        if (!infile.is_open())
        {
            std::cout << "Error: Cannot open file " << filename << std::endl;
            return false;
        }
        std::string line;
        while (std::getline(infile, line))
        {
            std::istringstream iss(line);
            K key;
            V val;
            if (iss >> key >> val)
            {
                if (contains(key))
                    std::cout << "Warning: Duplicate key '" << key << "', value updated" << std::endl;
                insert(std::make_pair(key, val));
            }
            else
                std::cout << "Error: Loading file entry is incorrect" << std::endl;
        }
        infile.close();
        return true;
    }

    template <typename K, typename V>
    void HashTable<K, V>::dump() const
    {
        for (int i = 0; i < theLists.size(); ++i)
        {
            std::cout << "v[" << i << "]: ";
            const auto &whichList = theLists[i];
            if (!whichList.empty())
            {
                size_t i = 0;
                for (const auto &whichPair : whichList)
                {
                    if (i != 0)
                        std::cout << ":";
                    std::cout << whichPair.first << " " << whichPair.second;
                    ++i;
                }
            }
            std::cout << std::endl;
        }
    }

    template <typename K, typename V>
    size_t HashTable<K, V>::size() const
    { 
        size_t count = 0;
        for (const auto &whichList : theLists)
            count += whichList.size();
        return count;
    }

    template <typename K, typename V>
    bool HashTable<K, V>::write_to_file(const char *filename) const
    {
        std::ofstream outfile(filename);
        if (!outfile.is_open())
        {
            std::cout << "Error: Cannot open file " << filename << std::endl;
            return false;
        }
        for (int i = 0; i < theLists.size(); ++i)
        {
            for (const auto &whichPair : theLists[i])
                outfile << whichPair.first << " " << whichPair.second << std::endl;
        }
        outfile.close();
        return true;
    }

    template <typename K, typename V>
    void HashTable<K, V>::makeEmpty()
    {
        for (auto &whichList : theLists)
            whichList.clear();
        currentSize = 0;
    }

    template <typename K, typename V>
    void HashTable<K, V>::rehash()
    {
        std::vector<std::list<std::pair<K, V>>> oldLists = theLists;
        theLists.resize(prime_below(2 * theLists.size()));
        makeEmpty();

        for (auto &thisList : oldLists) 
        {
            for (auto &kv : thisList) 
                insert(std::move(kv));
        }
    }

    template <typename K, typename V>
    size_t HashTable<K, V>::myhash(const K &k) const
    {
        static std::hash<K> hf;
	    return hf(k) % theLists.size();
    }

    // returns largest prime number <= n or zero if input is too large
    // This is likely to be more efficient than prime_above(), because it only needs a vector of size n
    template <typename K, typename V>
    unsigned long HashTable<K, V>::prime_below (unsigned long n)
    {
        if (n > max_prime)
        {
            std::cerr << "** input too large for prime_below()\n";
            return 0;
        }
        if (n == max_prime)
        {
            return max_prime;
        }
        if (n <= 1)
        {
            std::cerr << "** input too small \n";
            return 0;
        }
        // now: 2 <= n < max_prime
        std::vector <unsigned long> v (n+1);
        setPrimes(v);
        while (n > 2)
        {
            if (v[n] == 1)
            return n;
            --n;
        }
        return 2;
    }

    // Sets all prime number indexes to 1. Called by method prime_below(n) 
    template <typename K, typename V>
    void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
    {
        int i = 0;
        int j = 0;

        vprimes[0] = 0;
        vprimes[1] = 0;
        int n = vprimes.capacity();

        for (i = 2; i < n; ++i)
            vprimes[i] = 1;

        for( i = 2; i*i < n; ++i)
        {
            if (vprimes[i] == 1)
            for(j = i + i ; j < n; j += i)
                vprimes[j] = 0;
        }
    }

#endif