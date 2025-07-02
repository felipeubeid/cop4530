#ifndef BET_H
#define BET_H
#include <iostream>
#include <string>
#include <stack>

using namespace std;

// namespace cop4530
// {
    class BET
    {
        public:
            BET(); // default zero-parameter constructor
            BET(const string postfix); // one-parameter constructor
            BET(const BET& rhs); // copy constructor
            ~BET(); // destructor
            bool buildFromPostfix(const string postfix); // Build tree based on the postfix expression
            const BET & operator= (const BET & rhs); // assignment operator
            void printInfixExpression(); // print out the infix expression
            void printPostfixExpression(); // print out the postfix expression
            size_t size(); // return the number of nodes in the tree
            size_t leaf_nodes(); // return the number of leaf nodes in the tree
            bool empty(); // return true if the tree is empty. Return false otherwise.

        private:
            struct BinaryNode
            {
                string element;  // data in the node
                BinaryNode *left;   // left child
                BinaryNode *right;  // right child
                BinaryNode(const string& e, BinaryNode *l = nullptr, BinaryNode *r = nullptr)
                    : element{e}, left{l}, right{r} { }
                BinaryNode(string && e, BinaryNode *l = nullptr, BinaryNode *r = nullptr)
                    : element{std::move(e)}, left{l}, right{r} { } // needed?
            };

            BinaryNode* root;

            void printInfixExpression(BinaryNode *n); // print to the standard output the corresponding infix expression
            void makeEmpty(BinaryNode* &t); // delete all nodes in the subtree pointed to by t
            BinaryNode * clone(BinaryNode *t) const; // clone all nodes in the subtree pointed to by t
            void printPostfixExpression(BinaryNode *n); // print to the standard output the corresponding postfix expression
            size_t size(BinaryNode *t); // return the number of nodes in the subtree pointed to by t
            size_t leaf_nodes(BinaryNode *t); // return the number of leaf nodes in the subtree pointed to by t

            int precedence(const string& token); // helper function to check precedence

    };
    #include "bet.hpp"
// }

#endif