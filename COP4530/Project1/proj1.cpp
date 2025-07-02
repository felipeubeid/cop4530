#include <iostream>
#include <cctype>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void ExtractChars(const string& str, vector <char>& charList);
void CountChars(const string& str, vector <char>& charList, vector<int>& charCount);
void SortChars(vector<char>& charList, vector<int>& charCount);

bool IsWord(const string& word);
bool IsMixed(const string& word);
string ToLower(const string& word);

void ExtractWordsNum(const string& str, vector<string>& wordsNum);
void SeparateMixed(const string& word, vector<string>& wordsNum);

void ExtractWords(const string& str, vector<string>& wordList, const  vector<string>& wordsNum);
void ExtractNum(const string& str, vector<string>& numList, const  vector<string>& wordsNum);

void CountWordsNum(const vector<string>& wordsNum, const vector<string>& list, vector<int>& countList);
void SortAndWordsNum(vector<string>& list, vector<int>& countList);

void findLongest(const vector<string>& wordList, const vector<string>& numList, int& longestWordNumSize);
void PrintChars(vector<char>& charList, vector<int>& charCount, const int& longestWordNumSize);
void PrintWords(const vector<string>& wordList, const vector<int>& wordCount, const int& longestWordNumSize);
void PrintNums(const vector<string>& numList, const vector<int>& numCount, const int& longestWordNumSizee);

int main()
{
    string str; 
    char ch;
    while (cin.get(ch)) // read ch from input until it reaches the end
        str += ch; // append ch to the str

    vector<char> charList; // store list of characters
    vector<int> charCount; // store the count for each character
    ExtractChars(str, charList); // extract exclusive characters from string into a vector
    CountChars(str, charList, charCount); // add count of each character to a vector
    SortChars(charList, charCount); // sort character list
    
    vector<string> wordsNum; // to store words and numbers
    ExtractWordsNum(str, wordsNum); // extract all words and numbers from string into a vector

    vector<string> wordList; // store list of words
    vector<int> wordCount; // store the count for each word
    ExtractWords(str, wordList, wordsNum); // extract exclusive words from string into a vector
    CountWordsNum(wordsNum, wordList, wordCount); // add count of each word to a vector
    SortAndWordsNum(wordList, wordCount); // sort word list

    vector<string> numList; // store list of numbers
    vector<int> numCount; // store the count for number
    ExtractNum(str, numList, wordsNum); // extract exclusive numbers from string into a vector
    CountWordsNum(wordsNum, numList, numCount); // add count of each number to a vector
    SortAndWordsNum(numList, numCount); // sort number list

    int longestWordNumSize = 0;
    findLongest(wordList, numList, longestWordNumSize); // find the lenght of the longest word to be printed
    PrintChars(charList, charCount, longestWordNumSize); // print final list of chars
    cout << endl;
    PrintWords(wordList, wordCount, longestWordNumSize); // print final list of words
    cout << endl;
    PrintNums(numList, numCount, longestWordNumSize); // print final list of nums

    return 0;
}

// ---------------------------------------------------------------------------------------------------------

void ExtractChars(const string& str, vector <char>& charList)
{
    for (int i = 0; i < str.size(); i++) // iterate through the string
    {
        bool repeated = false; // initialize to false in every iteration
        // iterate through the char list to check if the current char is already present
        for (int j = 0; j < charList.size(); j++)
            if (charList[j] == str[i])
            {
                repeated = true; // change repeated to true if repeated
                break; // exit loop if repeated char is found
            }
        if (!repeated)
            // push current char into charList if repeated is false
            charList.push_back(str[i]);
    }
}

void CountChars(const string& str, vector <char>& charList, vector<int>& charCount)
{
    int count;
    for (int i = 0; i < charList.size(); i++) // iterate through the list of individual characters
    {
        count = 0; // initialize to 0 in every iteration
        for (int j = 0; j < str.size(); j++) // iterate through the string
            if (charList[i] == str[j])
                count++; // increment cound if match is found
        charCount.push_back(count); // push count
    }  
}

void SortChars(vector<char>& charList, vector<int>& charCount)
{
    int key = 0;
    char temp;
    int j = 1;

    // insertion sort in descending order. sort char and count in the same index at the same time
    for (int i = 1; i < charList.size(); i++)
    {
        key = charCount[i];
        temp = charList[i];
        j = i - 1;
        // sort in descending order. if count is equal, sort by char ascii value
        while (j >= 0 && ((charCount[j] < key) || (charCount[j] == key && charList[j] > temp)))
        {
            charCount[j + 1] = charCount[j];
            charList[j + 1] = charList[j];

            j -= 1;
        }
        charCount[j + 1] = key;
        charList[j + 1] = temp;
    }
}

bool IsWord(const string& word)
{
    for (int i = 0; i < word.size(); i++)
    {
        if (isdigit(word[i])) // if current char is a digit, return false
            return false;
    }
    
    return true;
}

bool IsMixed(const string& word)
{
    // check if the current word has numbers in some of it and vice versa
    bool digit = false; 
    bool letter = false;
    bool specialChar = false;
    bool mixed = false;

    for (int i = 0; i < word.size(); i++) // iterate through the word size
    {
        if (isalpha(word[i])) 
            letter = true;
        if (isdigit(word[i]))
            digit = true;
        if (!isalpha(word[i]) && !isdigit(word[i])) // if not a letter or a number, it is a special char
            specialChar = true;
    }

    if ((letter && digit) || specialChar)
        mixed = true; // mixed if more than one bool are true, word is mixed

    return mixed;
}

string ToLower(const string& word)
{
    string lower;
    char character;

    for (int i = 0; i < word.size(); i++) // make word passed in all lowercase, needs to be case insensitive
    {
        character = word[i];
        lower += tolower(character); // append lower version of the current char to the string
    }
    
    return lower; // return lowercase word
}

void ExtractWordsNum(const string& str, vector<string>& wordsNum)
{
    // words and numbers will be stored as string types, so extract each of them into a single string
    istringstream streamWordsNum(str);
    string extractedWordsNum;

    while (streamWordsNum >> extractedWordsNum) // extract words and numbers in the string
    {
        if (IsMixed(extractedWordsNum))
            SeparateMixed(extractedWordsNum, wordsNum);
        else
            wordsNum.push_back(ToLower(extractedWordsNum));
    }
}

void SeparateMixed(const string& word, vector<string>& wordsNum)
{
    string tempWord = "";
    string tempNum = "";

    for (int i = 0; i < word.size(); i++) // iterate through the word size
    {
        if (isalpha(word[i]))
        {
            if (tempNum != "") // if there was a number stored, push it to tempNum
            {
                wordsNum.push_back(tempNum); 
                tempNum = "";
            }
            tempWord += word[i]; // append current char into tempWord

        }
        else if (isdigit(word[i]))
        {
            if (tempWord != "") // if there was a char stored, push it to tempWord
            {
                wordsNum.push_back(ToLower(tempWord));
                tempWord = "";
            }
            tempNum += word[i]; // append current num into tempNum
        }
        else // if current char is somethin else
        {
            if (tempNum != "")
            {
                wordsNum.push_back(tempNum); // if there was a number stored, push it to tempNum
                tempNum = "";
            }
            if (tempWord != "")
            {
                wordsNum.push_back(ToLower(tempWord)); // if there was a char stored, push it to tempWord
                tempWord = "";
            }
        }
    }

    // push any ramaining words or nums

    if (tempWord != "")
        wordsNum.push_back(ToLower(tempWord));
    else if (tempNum != "")
        wordsNum.push_back(tempNum);
}

void ExtractWords(const string& str, vector<string>& wordList, const  vector<string>& wordsNum)
{
    // same logic as ExtractChars
    for (int i = 0; i < wordsNum.size(); i++)
    {
        bool repeated = false;
        for (int j = 0; j < wordList.size(); j++)
            if (wordList[j] == wordsNum[i])
            {
                repeated = true;
                break;
            }
        if (!repeated && IsWord(wordsNum[i])) // push if IsWord is true
            wordList.push_back(wordsNum[i]);
    }
}

void ExtractNum(const string& str, vector<string>& numList, const  vector<string>& wordsNum)
{
    // same logic as ExtractChars and ExtractWords
    for (int i = 0; i < wordsNum.size(); i++)
    {
        bool repeated = false;
        for (int j = 0; j < numList.size(); j++)
            if (numList[j] == wordsNum[i])
            {
                repeated = true;
                break;
            }
        if (!repeated && !IsWord(wordsNum[i])) // push if IsWord is false
            numList.push_back(wordsNum[i]);
    }
}

void CountWordsNum(const vector<string>& wordsNum, const vector<string>& list, vector<int>& countList)
{
    int count;
    for (int i = 0; i < list.size(); i++) // go through a loop to check each exclusive word in the list
    {
        count = 0; // set count of each different word to 0
        for (int j = 0; j < wordsNum.size(); j++) // go through the list with all separate words
            if (list[i] == wordsNum[j]) // if a match is found, increment count
                count++;
        countList.push_back(count); // add count of each word to the list, index will match word and count
    }    
}

void SortAndWordsNum(vector<string>& list, vector<int>& countList)
{
    // insertion sort in descending order. sort char and count in the same index at the same time
    int key = 0;
    string temp;
    int j = 1;;

    for (int i = 1; i < list.size(); i++)
    {
        key = countList[i];
        temp = list[i];
        j = i - 1;
        // sort in descending order
        while (j >= 0 && countList[j] < key)
        {
            countList[j + 1] = countList[j];
            list[j + 1] = list[j];

            j -= 1;
        }
        countList[j + 1] = key;
        list[j + 1] = temp;
    }
}

void findLongest(const vector<string>& wordList, const vector<string>& numList, int& longestWordNumSize)
{
    if (wordList.size() >= 10) // find longest word in top 10 if there are more than 10 words in the list
    {
        for (int i = 0; i < 10; i++)
        {
            if (wordList[i].size() > longestWordNumSize)
                longestWordNumSize = wordList[i].size();
        }
    }
    else // find longest word in the list if there are less than 10 words in the list
    {
        for (int i = 0; i < wordList.size(); i++)
        {
            if (wordList[i].size() > longestWordNumSize)
                longestWordNumSize = wordList[i].size();
        }
    }

    if (numList.size() >= 10) // find longest number in top 10 if there are more than 10 numbers in the list
    {
        for (int i = 0; i < 10; i++)
        {
            if (numList[i].size() > longestWordNumSize)
                longestWordNumSize = numList[i].size();
        }
    }
    else // find longest number in the list if there are less than 10 numbers in the list
    {
        for (int i = 0; i < numList.size(); i++)
        {
            if (numList[i].size() > longestWordNumSize)
                longestWordNumSize = numList[i].size();
        }
    } 
}

void PrintChars(vector<char>& charList, vector<int>& charCount, const int& longestWordNumSize)
{
    string space = "";
    for (int i = 0; i < (longestWordNumSize); i++) // create string of the longest word or num size with spaces
        space += " ";

    if (charList.size() >= 10) // print top 10 chars if there are more than 10 different chars in the list
    {
        cout << "Total " << charList.size() << " different characters, 10 most used characters:" << endl;

        for (int i = 0; i < 10; i++)
        {
            // print space followed by 4 spaces for \n and \t. /n and /t have 2 chars instead of 1, so in those cases 1 space less
            if (charList[i] == '\n')
                cout << "No. " << i << ": " << "\\n" << space << "    " << charCount[i] << endl;
            else if (charList[i] == '\t')
                cout << "No. " << i << ": " << "\\t" << space << "    " << charCount[i] << endl;
            else // print space followed by 4 spaces
                cout << "No. " << i << ": " << charList[i] << space << "     " << charCount[i] << endl;
        }
    }
    else // print the whole list if there are less than 10 chars in it
    {
        cout << "Total " << charList.size() << " different characters, " <<  charList.size() << " most used characters:" << endl;

        for (int i = 0; i < charList.size(); i++)
        {
            if (charList[i] == '\n')
                cout << "No. " << i << ": " << "\\n" << space << "    " << charCount[i] << endl;
            else if (charList[i] == '\t')
                cout << "No. " << i << ": " << "\\t" << space << "    " << charCount[i] << endl;
            else
                cout << "No. " << i << ": " << charList[i] << space << "     " << charCount[i] << endl;
        }
    }
}

void PrintWords(const vector<string>& wordList, const vector<int>& wordCount, const int& longestWordNumSize)
{
    string space = "";

    if (wordList.size() >= 10) // print top 10 words if there are more than 10 different words in the list
    {
        cout << "Total " << wordList.size() << " different words, 10 most used words:" << endl;

        for (int i = 0; i < 10; i++)
        {
            space = "";
            // create string of the longest word or num size with spaces + 5
            for (int j = 0; j < (longestWordNumSize - wordList[i].size() + 5); j++)
                space += " ";
            cout << "No. " << i << ": " << wordList[i] << space << wordCount[i] << endl;
        }
    }
    else // print the whole list if there are less than 10 words in it
    {
        cout << "Total " << wordList.size() << " different words, " <<  wordList.size() << " most used words:" << endl;

        for (int i = 0; i < wordList.size(); i++)
        {
            space = "";
            for (int j = 0; j < (longestWordNumSize - wordList[i].size() + 5); j++)
                space += " ";
            cout << "No. " << i << ": " << wordList[i] << space << wordCount[i] << endl;
        }
    }
}

void PrintNums(const vector<string>& numList, const vector<int>& numCount, const int& longestWordNumSize)
{
    // same logic as PrintWords
    string space = "";

    if (numList.size() >= 10)
    {
        cout << "Total " << numList.size() << " different numbers, 10 most used numbers:" << endl;

        for (int i = 0; i < 10; i++)
        {
            space = "";
            for (int j = 0; j < (longestWordNumSize - numList[i].size() + 5); j++)
                space += " ";
            cout << "No. " << i << ": " << numList[i] << space << numCount[i] << endl;
        }
    }
    else
    {
        cout << "Total " << numList.size() << " different numbers, " <<  numCount.size() << " most used numbers:" << endl;

        for (int i = 0; i < numList.size(); i++)
        {
            space = "";
            for (int j = 0; j < (longestWordNumSize - numList[i].size() + 5); j++)
                space += " ";
            cout << "No. " << i << ": " << numList[i] << space << numCount[i] << endl;
        }
    } 
}