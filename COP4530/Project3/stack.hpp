#ifndef STACK_HPP
#define STACK_HPP

#include "stack.h"

using namespace cop4530;

    template <typename T> // zero-argument constructor
    Stack<T>::Stack() : sta{}
    { }

    template <typename T> // destructor
    Stack<T>::~Stack()
    { clear(); }

    template <typename T> // copy constructor 
    Stack<T>::Stack(const Stack<T>& rhs) : sta{rhs.sta} // use deque copy constructor
    { }

    template <typename T> // move constructor
    Stack<T>::Stack(Stack<T>&& rhs) : sta{std::move(rhs.sta)} // use deque move constructor??
    { }

    template <typename T> // copy assignment operator=
    Stack<T>& Stack<T>::operator=(const Stack<T>& rhs) 
    {
        if (this != &rhs) // check for self assignment
            sta = rhs.sta; // use deque assignment operator
        return *this;
    }

    template <typename T> // move assignment operator=
    Stack<T>& Stack<T>::operator=(Stack<T>&& rhs) 
    {
        if (this != &rhs)
            sta = std::move(rhs.sta); // deque move assignment operator??
        return *this;
    }

    template <typename T> // returns true if the Stack contains no elements, and false otherwise
    bool Stack<T>::empty() const
    { return sta.empty(); }

    template <typename T> // delete all elements from the stack.
    void Stack<T>::clear()
    { sta.clear(); }

    template <typename T> // adds x to the Stack. copy version
    void Stack<T>::push(const T& x)
    { sta.push_front(x); }

    template <typename T> // adds x to the Stack. move version
    void Stack<T>::push(T&& x)
    { sta.push_front(std::move(x)); }

    template <typename T> // removes and discards the most recently added element of the Stack
    void Stack<T>::pop()
    {   
        if (empty()) // check if empty
            std::cout << "(empty)" << std::endl;
        else
            sta.pop_front(); 
    } 

    template <typename T> // mutator that returns a reference to the most recently added element of the Stack
    T& Stack<T>::top()
    { return sta.front(); } 

    template <typename T> // accessor that returns the most recently added element of the Stack
    const T& Stack<T>::top() const
    {   
        if (empty()) // check if empty
            std::cout << "(empty)" << std::endl;
        else
            return sta.front(); } 

    template <typename T> // returns the number of elements stored in the Stack
    int Stack<T>::size() const
    { return sta.size(); }

    template <typename T> // print elements of Stack to ostream os
    void Stack<T>::print(std::ostream& os, char ofc) const
    {
        if (this->empty())
            os << "(empty)";
        else
        {
            auto itr = sta.end();
            --itr;
            while (itr != sta.begin())
                os << *itr-- << ofc;
            os << sta.front() << ofc;
        }
    }

    template <typename T> // invokes the print() method to print the Stack<T> a in the specified ostream
    std::ostream& cop4530::operator<<(std::ostream& os, const Stack<T>& a)
    {
        a.print(os);
        return os;
    }


    template <typename T> // returns true if the two compared Stacks have the same elements, in the same order
    bool cop4530::operator==(const Stack<T>& a, const Stack<T>& b)
    { 
        if (a.size() != b.size()) // need to be the same size to be equal
            return false;
        Stack<T> aTemp(a);
        Stack <T> bTemp(b);
        while(!aTemp.empty())
        {
            if (aTemp.top() != bTemp.top())
                return false;
            aTemp.pop();
            bTemp.pop();
        }
        return true;
    } 

    template <typename T> // opposite of operator==()
    bool cop4530::operator!=(const Stack<T>& a, const Stack<T>& b)
    { return !(a == b); }

    template <typename T> // returns true if every element in Stack a is smaller than or equal to the corresponding element of Statck b
    bool cop4530::operator<=(const Stack<T>& a, const Stack<T>& b)
    {
        if (a.size() != b.size()) // need to be the same size, if a size > b size loop won't work, for example
            return false;
        Stack<T> aTemp(a);
        Stack <T> bTemp(b);
        while(!aTemp.empty())
        {
            if (!(aTemp.top() <= bTemp.top()))
                return false;
            aTemp.pop();
            bTemp.pop();
        }
        return true;
    }

#endif