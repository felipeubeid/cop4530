#ifndef MY_MEMORY_BLOCK_H
#define MY_MEMORY_BLOCK_H

#include <iostream>
#include "List.h"
using namespace cop4530;
using namespace std;

class MyMemory
{
    public:

        class MyMemoryBlock // nested MyMemoryBlock class
        {
            public:
                MyMemoryBlock(int ind = 0, int len = 0) : index(ind), length(len)
                {}

                int get_length()
                { return length; }

                int get_index()
                { return index; }

                int allocate_mem(int len)
                {
                    if (len > length)
                        return -1;
                    length -= len;
                    return len;
                }

                void free_mem(int len)
                { length += len; }

            private:
                int index;
                int length;        
        };        
        
        MyMemory(int num = 0, int len = 0) : max_index(num - 1), block_size(len)
        {
            for (int i = 0; i < num; ++i)
                mlist.push_back(MyMemoryBlock(i, len));
        }

        void resize(int num = 100, int len = 100)
        { 
            if (!mlist.empty())
                mlist.clear();
            for (int i = 0; i < num; ++i)
                mlist.push_back(MyMemoryBlock(i, len));
            max_index = num - 1;
            block_size = num - 2;
        }

        int req_mem(int len)
        { 
            for (auto itr = mlist.begin(); itr != mlist.end(); ++itr)
            {
                if (itr->get_length() >= len)
                {
                    itr->allocate_mem(len);
                    int return_intex = itr->get_index();
                    if(itr->get_length() == 0)
                    {
                        itr = mlist.erase(itr);
                        --max_index;
                    }
                    return return_intex;
                }
            } 
            return -1;
        }

        bool release_mem(int ind, int len)
        {
            if (ind < 0 || ind > max_index || len < 0 || len > block_size)
                return false;

            for (auto itr = mlist.begin(); itr != mlist.end(); ++itr)
            {
                if (itr->get_index() == ind)
                {                    
                    cout << "Inside if" << endl;
                    itr->free_mem(len);
                    return true;
                }
            }

            auto itr2 = mlist.begin();
            while (itr2 != mlist.end() && itr2->get_index() < ind)
                ++itr2;
            mlist.insert(itr2, MyMemoryBlock(ind,len));
            return true;
        }

        void merge_mem()
        { 
            auto itr = mlist.begin();
            auto next = itr; // itr to the item after the current itr
            bool merged = false;
            while (itr != mlist.end())
            {
                if (!merged)
                    ++next;
                while (next != mlist.end() && (itr->get_length() + next->get_length()) <= block_size)
                {
                    itr->free_mem(next->get_length());
                    next = mlist.erase(next); 
                    --max_index;
                    merged = true;
                }
                ++itr;
            }
        }

        void dump()
        {
            cout << "Number of blocks: " << max_index + 1<< endl;
            for (auto itr = mlist.begin(); itr != mlist.end(); ++itr)
                cout << "Block(index = " << itr->get_index() << "): " << itr->get_length() << endl;
        }

        ~MyMemory()
        { mlist.clear(); }

    protected:
        List<MyMemoryBlock> mlist;
        int max_index;
        int block_size;
};

#endif