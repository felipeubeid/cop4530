#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

int main()
{
    string str;
    cout << "Enter string: ";
    getline(cin, str);
    cout << str;

    vector<string> words;
    vector <char> chars;
    vector <int> numbers;

    istringstream stream(str);
    string extracted;

    while (stream >> extracted)
    {
        words.push_back(extracted);
    }
    
    cout << endl;
    cout << "Words extracted: " << endl;
    for (int i = 0; i < words.size(); i++)
    {
        cout << "No. " << i << ": " << words[i] << endl;
    }

    cout << "str after: " << str;

    return 0;
}