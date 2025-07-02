#ifndef LIST_HPP
#define LIST_HPP

#include "List.h"

using namespace cop4530;

    // const_iterator ------------------------------------------------------------------------------------

    template <typename T> // default zero parameter constructor
    List<T>::const_iterator::const_iterator() : current{nullptr}
    {}

    template <typename T> // operator*() to return element
    const T& List<T>::const_iterator::operator*() const
    { return retrieve(); }

    template <typename T> // operator->() to return pointer to element
    const T* List<T>::const_iterator::operator->() const // ????? Not on textbook
    { return &(retrieve()); }

    template <typename T> // prefix increment
    typename List<T>::const_iterator& List<T>::const_iterator::operator++() 
    {
        current = current->next;
        return *this;
    }

    template <typename T> // postfix increment
    typename List<T>::const_iterator List<T>::const_iterator::operator++(int)
    {
        const_iterator old = *this;
        ++(*this);
        return old;
    }

    template <typename T> // prefix decrement
    typename List<T>::const_iterator& List<T>::const_iterator::operator--()
    {
        current = current->prev;
        return *this;
    }

    template <typename T> // prefix decrement
    typename List<T>::const_iterator List<T>::const_iterator::operator--(int)
    {
        const_iterator old = *this;
        --(*this);
        return old;
    }

    template <typename T> // comparison operator ==
    bool List<T>::const_iterator::operator==(const const_iterator & rhs) const 
    { return current == rhs.current; }

    template <typename T> // comparison operator !=
    bool List<T>::const_iterator::operator!=(const const_iterator & rhs) const 
    { return !(*this == rhs); }

    template <typename T> // retrieve the element refers to
    T& List<T>::const_iterator::retrieve() const 
    { return current->data; }

    template <typename T> // protected constructor
    List<T>::const_iterator::const_iterator(Node *p) : current{p}
    { }

    // iterator -------------------------------------------------------------------------------------------

    template <typename T> // default zero parameter constructor
    List<T>::iterator::iterator() 
    { }

    template <typename T>
    T& List<T>::iterator::operator*() // operator*() to return element
    { return const_iterator::retrieve(); }

    template <typename T> // operator*() to return element, const
    const T& List<T>::iterator::operator*() const
    { return const_iterator::operator*(); }

    template <typename T> // return pointer to element
    T* List<T>::iterator::operator->() 
    { return &(const_iterator::retrieve()); }

    template <typename T> // return pointer to content element
    const T* List<T>::iterator::operator->() const 
    { return &(const_iterator::operator*()); }

    template <typename T> // prefix increment
    typename List<T>::iterator& List<T>::iterator::operator++() 
    {
        this->current = this->current->next;
        return *this;
    }

    template <typename T> // postfix increment
    typename List<T>::iterator List<T>::iterator::operator++(int)
    {
        iterator old = *this;
        ++(*this);
        return old;
    }

    template <typename T> // prefix decrement
    typename List<T>::iterator& List<T>::iterator::operator--()
    {
        this->current = this->current->prev;
        return *this;
    }

    template <typename T> // postfix decrement
    typename List<T>::iterator List<T>::iterator::operator--(int)
    {
        iterator old = *this;
        --(*this);
        return old;
    }

    template <typename T> // protected constructor
    List<T>::iterator::iterator(Node *p) : const_iterator{p}
    { }

    // list ----------------------------------------------------------------------------------------------

    template <typename T>  // default zero parameter constructor
    List<T>::List() 
    { init(); }

    template <typename T> // copy constructor
    List<T>::List(const List & rhs) 
    {
        init();
        for(auto & val : rhs)
            push_back(val);

    }

    template <typename T> // move constructor
    List<T>::List(List && rhs) : theSize{rhs.theSize}, head{rhs.head}, tail{rhs.tail}
    {
        rhs.theSize = 0;
        rhs.head = nullptr;
        rhs.tail = nullptr;

    }

    template <typename T> // num elements with value of val
    List<T>::List(int num, const T &val) // why explicit ?????
    {
        init();
        for (int i = 0; i < num; i++)
            push_back(val);
    }

    template <typename T> // constructs with elements [start, end)
    List<T>::List(const_iterator start, const_iterator end) // // ????? Not on textbook
    {
        init();
        for (auto itr = start; itr != end; ++itr)
            push_back(*itr);
    }

    template <typename T> // destructor
    List<T>::~List() 
    {
        clear();
        delete head;
        delete tail;
    }

    template <typename T> // copy assignment operator=
    const List<T>& List<T>::operator=(const List & rhs) 
    {
        List copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    template <typename T> // move assignment operator=
    List<T>& List<T>::operator=(List && rhs) 
    {
        std::swap(theSize, rhs.theSize);
        std::swap(head, rhs.head);
        std::swap(tail, rhs.tail);
        return *this;
    }

    template <typename T> // number of elements
    int List<T>::size() const 
    { return theSize; }

    template <typename T> // check if list is empty
    bool List<T>::empty() const
    { return size() == 0; }

    template <typename T> // delete all elements
    void List<T>::clear() 
    {
        while(!empty())
            pop_front();
    }

    template <typename T> // reverse the order of the elements
    void List<T>::reverse() 
    {
        if (size() <= 1)
            return;

        Node *currentNode = head;
        Node *temp = nullptr;
        while (currentNode != nullptr)
        {
            std::swap(currentNode->prev, currentNode->next);
            currentNode = currentNode->prev;
        }
        std::swap(head, tail);
    }


    template <typename T> // reference to the first element
    T& List<T>::front() 
    { return *begin(); } // What if list is empty? ??????

    template <typename T> // reference to the first element (const)
    const T& List<T>::front() const 
    { return *begin(); } // Same?

    template <typename T> // reference to the last element
    T& List<T>::back() 
    { return *--end(); }

    template <typename T> // reference to the last element (const)
    const T& List<T>::back() const 
    { return *--end(); }

    template <typename T> // insert to the beginning
    void List<T>::push_front(const T& val) 
    { insert(begin(), val); }

    template <typename T> // move version of insert
    void List<T>::push_front(T && val) 
    { insert(begin(), std::move(val)); }

    template <typename T> // insert to the end
    void List<T>::push_back(const T& val) 
    { insert(end(), val); }

    template <typename T> // move version of insert
    void List<T>::push_back(T && val) 
    { insert(end(), std::move(val)); }

    template <typename T> // delete first element
    void List<T>::pop_front() 
    { erase(begin()); }

    template <typename T> // delete last element
    void List<T>::pop_back() 
    { erase(--end()); }

    template <typename T> // remove all elements with value = val
    void List<T>::remove(const T &val) // ????? Not on textbook
    {
        for (auto itr = begin(); itr != end();)
        {
            if (*itr == val)
                itr = erase(itr); // already increments itr?
            else
                ++itr; // need to increment if that wasn't done by erase
        }
    }

    template <typename T> // print out all elements. ofc is deliminitor
    void List<T>::print(std::ostream& os, char ofc) const
    {
        if (this->empty())
            os << "(empty)";
        else
        {
            auto itr = begin();
            while (itr != end())
                os << *itr++ << ofc;
        }
    }

    template <typename T> // iterator to first element
    typename List<T>::iterator List<T>::begin() 
    { return iterator(head->next);}

    template <typename T> // const_iterator to first element
    typename List<T>::const_iterator List<T>::begin() const 
    { return const_iterator(head->next); }

    template <typename T> // end marker iterator
    typename List<T>::iterator List<T>::end() 
    { return iterator(tail); }

    template <typename T> // end marker const_iterator
    typename List<T>::const_iterator List<T>::end() const 
    { return const_iterator(tail); }

    template <typename T> // insert val ahead of itr
    typename List<T>::iterator List<T>::insert(iterator itr, const T& val) 
    {
        Node *p = itr.current;
        ++theSize;
        return iterator(p->prev = p->prev->next = new Node{val, p->prev, p});
    }

    template <typename T> // move version of insert
    typename List<T>::iterator List<T>::insert(iterator itr, T && val) 
    {
        Node *p = itr.current;
        ++theSize;
        return iterator(p->prev = p->prev->next = new Node{std::move(val), p->prev, p});
    }

    template <typename T> // erase one element
    typename List<T>::iterator List<T>::erase(iterator itr) 
    {
        Node *p = itr.current;
        iterator retVal(p->next);
        p->prev->next = p->next;
        p->next->prev = p->prev;
        delete p;
        --theSize;
        return retVal;
    }

    template <typename T> // erase [start, end)
    typename List<T>::iterator List<T>::erase(iterator start, iterator end) // Assume start is always < end?
    {
        for(iterator itr = start; itr != end;)
            itr = erase(itr);
        return end;
    }

    template <typename T> // initialization
    void List<T>::init()
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }

    template <typename T> // overloading comparison operators ==
    bool cop4530::operator==(const List<T> &lhs, const List<T> &rhs) // ????? Not on textbook
    {
        if (lhs.size() != rhs.size())
            return false;
        
        auto lhsItr = lhs.begin();
        for (auto rhsItr = rhs.begin(); rhsItr != rhs.end(); ++rhsItr )
        {
            if (*lhsItr != *rhsItr)
                return false;
            ++lhsItr;
        }

        return true;
    }

    template <typename T> // overloading comparison operators !=
	bool cop4530::operator!=(const List<T> & lhs, const List<T> &rhs)
    {
        return !(lhs == rhs);
    }

    template <typename T> // overloading output operator
	std::ostream & cop4530::operator<<(std::ostream &os, const List<T> &l)
    {
        l.print(os);
        return os;
    }

#endif
