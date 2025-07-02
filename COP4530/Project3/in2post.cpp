#include <iostream>
#include <string>
#include <vector>
#include "stack.hpp"

using namespace std;
vector<string> separateTokens(const string& input);
bool isOperator(string token);
bool isParenthesis(string token);
bool isOperand(string token);
int precedence(const string& op);
void infix2postfix(const vector<string>& expinfixression, vector<string>& postfix);
bool isNumeric(const vector<string>& postfix);
double evaluate(vector<string>& postfix);

int main()
{
    string input = "";
    vector<string> infix;
    vector<string> postfix;
    string postfixStr;

    while (input != "exit")
    {
        cout << "Enter infix expression (\"exit\" to quit): ";
        getline(cin, input);
        cout << endl;
        infix = separateTokens(input);
        
        if (input != "exit")
        {
            infix2postfix(infix, postfix);
            for (int i = 0; i < postfix.size(); ++i)
                postfixStr += postfix[i] + " ";

            if (!postfix.empty())
            {
                cout << "Postfix evaluation: " << postfixStr << " = ";
                if (isNumeric(postfix))
                {
                    double result = evaluate(postfix);
                    cout << result << endl;
                    postfix.clear();
                }
                else
                {
                    cout << postfixStr << endl;
                    postfix.clear();
                }
                postfixStr = "";
            }
        }
    }
    
    return 0;
}

vector<string> separateTokens(const string& input)
{
    vector<string> infix;
    string token = "";

    for (char ch : input)
    {
        if (!isspace(ch))
            token += ch;
        else if (!token.empty())
        {
            infix.push_back(token);
            token = "";
        }
    }
    if (!token.empty())
        infix.push_back(token);    

    return infix;   
}

bool isOperator(string token)
{ return (token == "+" || token == "-" || token == "*" || token == "/"); }

bool isParenthesis(string token)
{ return (token == "(" || token == ")"); }

bool isOperand(string token)
{
    if (!isOperator(token) && !isParenthesis(token))
        return true;
    return false;
}

int precedence(const string& op)
{
    if (op == "*"|| op == "/")
        return 2;
    else if (op == "+"|| op == "-")
        return 1;
    else
        return 0;
}

void infix2postfix(const vector<string>& infix, vector<string>& postfix)
{
    int operands = 0, operators = 0;
    Stack<string> parenthesis;
    Stack<string> s;
    
    string infixStr;
    for (int i = 0; i < infix.size(); ++i)
            infixStr += infix[i] + " ";

    for (int i = 0; i < infix.size(); ++i)
    {
        if ((i == 0 && isOperator(infix[i])) || (i == (infix.size() - 1) && isOperator(infix[i])))
        {
            cout << "Error: Missing operands in the expression" << endl;
            postfix.clear();
            return;
        }
        if (isOperand(infix[i]))
        {
            if (i + 1 < infix.size() && !isOperator(infix[i + 1]) && infix[i + 1] != ")")
            {
                cout << "Error: Missing operators in the expression" << endl;
                postfix.clear();
                return;
            }
            postfix.push_back(infix[i]);
            operands++;
        }
        else if (isOperator(infix[i]))
        {
            if (!isOperand(infix[i - 1]) && infix[i - 1] != ")")
            {
                cout << "Error: Missing operands in the expression" << endl;
                postfix.clear();
                return;
            }
            while (!s.empty() && s.top() != "(" && (precedence(s.top()) >= precedence(infix[i])))
            {
                postfix.push_back(s.top());
                s.pop();
            }
            s.push(infix[i]);
            operators++;
        }
        else if (infix[i] == "(")
        {
            s.push(infix[i]);
            parenthesis.push(infix[i]);
        }
        else if (infix[i] == ")")
        {
            if (parenthesis.empty())
            {
                cout << "Error: Infix expression: " << infixStr << "has mismatched parens!" << endl;
                postfix.clear();
                return;
            }
            while (s.top() != "(")
            {
                postfix.push_back(s.top());
                s.pop();
            }
            if (!s.empty()) 
            {
                s.pop();
                parenthesis.pop();
            }
            else
            {
                cout << "Error: Infix expression: " << infixStr << "has mismatched parens!" << endl;
                postfix.clear();
                return;
            }
        }
    }
    while (!s.empty())
    {
        postfix.push_back(s.top());
        s.pop();
    }

    if (!parenthesis.empty()) 
    {
        cout << "Error: Infix expression: " << infixStr << "has mismatched parens!" << endl;
        postfix.clear();
        return;
    }
    
    if ((operands != operators + 1) && (operands != 0 && operators != 0))
    {
        cout << "Error: Missing operators in the expression" << endl;
        postfix.clear();
        return;
    }

    if (!postfix.empty())
    {
        cout << "Postfix expression: ";
        for (int i = 0; i < postfix.size(); ++i)
                cout << postfix[i] + " ";
        cout << endl;
    }
    else
        cout << "Postfix evaluation:  = Empty postfix" << endl;
}

bool isNumeric(const vector<string>& postfix)
{
    for (const auto& token : postfix)
        for (char ch : token)
            if (isalpha(ch))
                return false;
                
    return true;
}

double evaluate(vector<string>& postfix)
{
    Stack<double> operands;
    double result = 0;

    for (int i = 0; i < postfix.size(); ++i)
    {
        string t = postfix[i];
        if (!isOperator(t))
        {
            operands.push(stod(t));
        }
        else
        {
            double op2 = operands.top();
            operands.pop();
            double op1 = operands.top();
            operands.pop();
            result = 0;

            if (t == "*")
                result = op1 * op2;
            else if (t == "/")
                result = op1 / op2;
            else if (t == "+")
                result = op1 + op2;
            else if (t == "-")
                result = op1 - op2;

            operands.push(result);
        }
    }
    return operands.top();
}