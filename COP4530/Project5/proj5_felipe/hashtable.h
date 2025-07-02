#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include<list>
#include <utility>
#include <fstream>
#include <sstream>

namespace cop4530
{
    template <typename K, typename V>
        class HashTable
        {
            public:
                HashTable(size_t size = 101); // constructor
                ~HashTable(); // destructor
                bool contains(const K & k) const; // check if key k is in the hash table
                bool match(const std::pair<K, V> &kv) const; // check if key-value pair is in the hash table
                bool insert(const std::pair<K, V> & kv); // add  the key-value pair kv into the hash table
                bool insert (std::pair<K,  V> && kv); // move version of insert
                bool remove(const K & k); // delete the key k and the corresponding value if it is in the hash table
                void clear(); // delete all elements in the hash table
                bool load(const char *filename); // load the content of the file with name filename into the hash table
                void dump() const; // display all entries in the hash table
                size_t size() const; // return the number of elements in the hash table
                bool write_to_file(const char *filename) const; // write all elements in the hash table into a file with name filename

            private:
                void makeEmpty(); // delete all elements in the hash table
                void rehash(); // rehash function
                size_t myhash(const K &k) const; // return the index of the vector entry where k should be stored
                // two helpful functions to determine the proper prime numbers used in setting up the vector size:
                unsigned long prime_below (unsigned long);
                void setPrimes(std::vector<unsigned long>&);

                std::vector<std::list<std::pair<K, V>>> theLists;
                size_t currentSize; 
                static const unsigned int max_prime = 1301081; // max_prime is used by the helpful functions provided to you
                static const unsigned int default_capacity = 101; // the default_capacity is used if the initial capacity of the underlying vector of the hash table is zero
        };

    #include "hashtable.hpp"
}

#endif
