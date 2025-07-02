#include <iostream>
#include <string>
#include <limits>
#include "MyMemory.h"

using namespace std;

void print_menu() 
{
	cout << string(20, '=') << endl;
	cout << "d: memory dump" << endl;
	cout << "r: request memory" << endl;
	cout << "l: release memory" << endl;
	cout << "m: merge memory" << endl;
	// cout << "e: resize memory" << endl;
	cout << "x: quit program" << endl;
	cout << "Your choice: ";	
}

int main()
{
	int num = 0, len = 0;
	bool valid = false;

	cout << "Memory configuration: " << endl;
	
	cout << "Number of memory blocks (integer): ";
	while (!(cin >> num))
	{
		cout << endl;
		cout << "Memory configuration: " << endl;
		cout << "Number of memory blocks (integer): ";
		cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	if (num < 0)
		num = 0;
	
	cout << endl;
	cout << "Memory block size (integer): ";
	while (!(cin >> len))
	{
		cout << endl;
		cout << "Memory configuration: " << endl;
		cout << "Number of memory blocks (integer): ";
		cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	
	MyMemory MyMem(num, len);

	char choice = ' ';
	while (choice != 'x')
	{
		print_menu();
		cin >> choice;
		cout << "choice: " << choice << endl;
		switch (choice)
		{
			case 'd':
				MyMem.dump(); break;
			case 'r':
			{
				int len1 = 0;
				cout << "Requested memory size (integer): ";
				cin >> len1;
				MyMem.req_mem(len1);
				break;
			}
			case 'l':
			{
				int ind1 = 0, len1 = 0;
				cout << "Release memory index (integer): ";
				cin >> ind1;
				cout << "Release memory length (integer): ";
				cin >> len1;
				bool success = MyMem.release_mem(ind1, len1);
				if(success != true)
					cout << "Memory release operation failed" << endl;
				break;
			}
			case 'm':
				MyMem.merge_mem(); break;
			// case 'e':
			// {
			// 	int num1 = 0, len1 = 0;
			// 	cout << "New number of memory blocks (integer): ";
			// 	cin >> num1;
			// 	cout << "New block size (integer): ";
			// 	cin >> len1;
			// 	MyMem.resize(num1, len1);
			// 	break;
			// }
			case 'x':
				break;
			
			default:
			{
				cout << endl;
				cout << "*****Error: Invalid entry.  Try again." << endl; break;
			}
		}
	}
	

	return 0;
}
