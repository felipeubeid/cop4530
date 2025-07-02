#include <iostream>
#include <string>
#include "passserver.h"

using namespace std;

void Menu();

int main()
{
    int serverSize;
    cout << "Enter preferred hash table capacity (integer): ";
    cin >> serverSize;
    cout << serverSize << endl;
    PassServer server(serverSize);
    char choice;

    do
    {
        Menu();
        cin >> choice;
        cout << "choice : " << choice << endl;
        switch (choice)
        {
            case 'l':
            {
                char infile[256];
                cout << "Enter password file name to load from: ";
                cin >> infile;
                server.load(infile);
                break;
            }
            case 'a':
            {
                string user, pass;
                cout << "Enter username: ";
                cin >> user;
                cout << "Enter password: ";
                cin >> pass;
                
                cout << endl;
                if (server.addUser(make_pair(user, pass)))
                    cout << "User " << user << " added." << endl;
                else
                    cout << "*****Error: User already exists. Could not add user." << endl;
                break;
            }
            case 'r':
            {
                string user;
                cout << "Enter username: ";
                cin >> user;
                
                if (server.removeUser(user))
                    cout << "User " << user << " deleted." << endl;
                else
                    cout << endl << "*****Error: User not found.  Could not delete user" << endl;

                break;
            }
            case 'c':
            {
                string user, pass, newpass;
                cout << "Enter username: ";
                cin >> user;
                cout << "Enter password: ";
                cin >> pass;
                cout << endl;
                cout << "Enter new password: ";
                cin >> newpass;
                
                cout << endl;
                if (server.changePassword(make_pair(user,pass), newpass))
                    cout << "Password changed for user " << user << endl;
                else
                    cout << "*****Error: Could not change user password" << endl;
                break;
            }
            case 'f':
            {
                string user;
                cout << "Enter username: ";
                cin >> user;

                cout << endl;
                if (server.find(user))
                    cout << "User '" << user << "' found." << endl;
                else
                    cout << "User '" << user << "' not found." << endl;
                break;
            }
            case 'd':
            {
                server.dump();
                break;
            }
            case 's':
            {
                int size = server.size();
                cout << "Size of hashtable: " << size << endl;
                break;
            }
            case 'w':
            {
                char outfile[256];
                cout << "Enter password file name to write to: ";
                cin >> outfile;
                server.write_to_file(outfile);
                break;
            }
            case 'x':
                break;
            default:
            {
                cout << endl;
                cout << "*****Error: Invalid entry.  Try again." << endl;
                break;
            }
        }
        
    } while (choice != 'x');
    return 0;
}

void Menu()
{
    cout << "\n\n";
    cout << "l - Load From File" << endl;
    cout << "a - Add User" << endl;
    cout << "r - Remove User" << endl;
    cout << "c - Change User Password" << endl;
    cout << "f - Find User" << endl;
    cout << "d - Dump HashTable" << endl;
    cout << "s - HashTable Size" << endl;
    cout << "w - Write to Password File" << endl;
    cout << "x - Exit program" << endl;
    cout << "\nEnter choice : ";
}