#ifndef DL_STACK_H
#define DL_STACK_H
#include <iostream>
#include <deque>

namespace cop4530
{
    template <typename T>
        class Stack
        {
            public:
                Stack(); // zero-argument constructor
                ~Stack(); // destructor
                Stack(const Stack<T>&); // copy constructor 
                Stack(Stack<T> &&); // move constructor
                Stack<T>& operator=(const Stack <T>&); // copy assignment operator=
                Stack<T>& operator=(Stack<T> &&); // move assignment operator=
                bool empty() const; // returns true if the Stack contains no elements, and false otherwise
                void clear(); // delete all elements from the stack
                void push(const T& x); // adds x to the Stack. copy version
                void push(T&& x); // adds x to the Stack. move version
                void pop(); // removes and discards the most recently added element of the Stack
                T& top(); // mutator that returns a reference to the most recently added element of the Stack
                const T& top() const; // accessor that returns the most recently added element of the Stack
                int size() const; // returns the number of elements stored in the Stack
                void print(std::ostream& os, char ofc = ' ') const; // print elements of Stack to ostream os

            private:
                std::deque<T> sta;
        };

    // invokes the print() method to print the Stack<T> a in the specified ostream   
    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Stack<T>& a); 

    // returns true if the two compared Stacks have the same elements, in the same order
    template <typename T>
    bool operator==(const Stack<T>&, const Stack <T>&);

    // opposite of operator==()
    template <typename T>
    bool operator!=(const Stack<T>&, const Stack <T>&);

    // returns true if every element in Stack a is smaller than or equal to the corresponding element of Statck b
    template <typename T>
    bool operator<=(const Stack<T>& a, const Stack <T>& b);

    #include "stack.hpp"
}

#endif