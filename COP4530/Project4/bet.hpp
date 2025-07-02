#ifndef BET_HPP
#define BET_HPP
#include <sstream>
#include "bet.h"

using namespace std;

    BET::BET() : root(nullptr)
    { }

    BET::BET(const string postfix)
    { buildFromPostfix(postfix); }

    BET::BET(const BET& rhs) : root(nullptr)
    { root = clone(rhs.root); }

    BET::~BET()
    { makeEmpty(root); }

    bool BET::buildFromPostfix(const string postfix)
    {
        stack<BinaryNode*> S; // stack of pointers to BinaryNode objects
        istringstream extractTokens(postfix);
        string token;

        while (extractTokens >> token) // extract tokens from postfix
        {
            if (token != "+" && token != "-" && token != "*" && token != "/") // if token is operand
            {
                BinaryNode* n = new BinaryNode(token); // create new BinaryNode with token
                S.push(n); // push it into the stack
            }
            else if (token == "+" || token == "-" || token == "*" || token == "/") // if token is operator
            {
                if (S.size() < 2) // need to have at least two operands for the operator
                {
                    root = nullptr;
                    cout << "Wrong postfix expression" << endl;
                    return false;
                }
                // get left and right children for operator, pop from stack
                BinaryNode* r = S.top();
                S.pop();
                BinaryNode* l = S.top();
                S.pop();
                BinaryNode* n = new BinaryNode(token, l, r); // create new BinaryNode with operator and operand children
                S.push(n); // push it into the stack
            }
            else
            {
                root = nullptr;
                cout << "Wrong postfix expression" << endl;
                return false;
            }
        }
        if (S.size() != 1) // final stack should have one element only, the root of the BET
        {
            root = nullptr;
            cout << "Wrong postfix expression" << endl;
            return false;
        }
        root = S.top();
        S.pop();

        return true;
    }

    const BET& BET::operator=(const BET & rhs)
    {
        if (this != &rhs)
        {
            makeEmpty(root);
            root = clone(rhs.root);
        }
        return *this;
    }

    void BET::printInfixExpression()
    { printInfixExpression(root); }

    void BET::printPostfixExpression()
    { printPostfixExpression(root); }

    size_t BET::size()
    { return size(root); }

    size_t BET::leaf_nodes()
    { return leaf_nodes(root); }

    bool BET::empty()
    { return root == nullptr; }

    void BET::printInfixExpression(BinaryNode* n)
    {
        if (n != nullptr)
        {
            int pr = precedence(n->element);
            bool parenLeft = false;
            bool parenRight = false;

            if (n->left)
            {
                if(n->left->element == "+" || n->left->element == "-" || n->left->element == "*" || n->left->element == "/")
                {
                    int leftpr = precedence(n->left->element);
                    if (leftpr > pr)
                        parenLeft = false;
                    else if (leftpr < pr)
                        parenLeft = true;
                    else if (leftpr == pr && (n->element == "-" || n->element == "/"))
                        parenLeft = false;
                    else if (leftpr == pr && (n->element == "+" || n->element == "*"))
                        parenLeft = false;
                    else
                        parenLeft = true;
                }
            } 
            if (n->right)
            {
                if(n->right->element == "+" || n->right->element == "-" || n->right->element == "*" || n->right->element == "/")
                {
                    int rightpr = precedence(n->right->element);
                    if (rightpr > pr)
                        parenRight = false;
                    else if (rightpr < pr)
                        parenRight = true;
                    else if (rightpr == pr && (n->element == "-" || n->element == "/"))
                        parenRight = true;
                    else if (rightpr == pr && (n->element == "+" || n->element == "*"))
                        parenRight = true;
                    else
                        parenRight = false;
                    
                }
            }
            if(parenLeft)
                cout << "( ";
            printInfixExpression(n->left);
            if(parenLeft)
                cout << ") ";

            cout << n->element << " ";

            if(parenRight)
                cout << "( ";
            printInfixExpression(n->right);
            if(parenRight)
                cout << ") ";
        }
        if (n == root)
            cout << endl;  
    }

    void BET::makeEmpty(BinaryNode* &t)
    {
        if (t != nullptr) // if it hasn't reached the end
        {
            makeEmpty(t->left); // left subtree
            makeEmpty(t->right); // right subtree
            delete t;
            t = nullptr;
        }
        t = nullptr;
    }

    BET::BinaryNode* BET::clone(BinaryNode* t) const
    {
        if (t == nullptr)
            return nullptr; // base case, reached the end
        // recursively call subtrees, starting from the left
        return new BinaryNode{t->element, clone(t->left), clone(t->right)}; // return cloned node
    }

    void BET::printPostfixExpression(BinaryNode *n)
    {
        if (n != nullptr)
        {
            printPostfixExpression(n->left); // left subtree
            printPostfixExpression(n->right); // right subtree
            cout << n->element << " "; // print current node element
        }
        if (n == root)
            cout << endl; 
    }

    size_t BET::size(BinaryNode *t)
    {
        if (t == nullptr) 
            return 0; // return 0, no nodes, nothing to count
        // count this node + size of left and right subtrees
        size_t count = 1 + size(t->left) + size(t->right);
        return count; // return count
    }

    size_t BET::leaf_nodes(BinaryNode *t)
    {
        if (t == nullptr) 
            return 0; // return 0, no nodes, nothing to count
        if (t->left == nullptr && t->right == nullptr)
            return 1; // return 1 if both children are nullptr, leaf node
        size_t count = leaf_nodes(t->left) + leaf_nodes(t->right); 
        return count; // return count
    }

    int BET::precedence(const string& token)
    {
        if (token == "*"|| token == "/")
            return 2;
        else if (token == "+"|| token == "-")
            return 1;
        else
            return 0;
    }

#endif