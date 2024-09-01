#include <iostream>
#include <fstream>
#include <stdlib.h> // atoi() => convert string to int
#include<cstring>  // strcopy() , strcat()
#include<cstdlib> 
#include<string> 
#include"StudentL.h"
using namespace std;

static void choices()
{
	cout << "\t\t\t\t*******************************************" << endl;
	cout << "\t\t\t\t* Enter 1 to insert    Enter 2 to display *" << endl;
	cout << "\t\t\t\t* Enter 3 to search    Enter 4 to remve   *" << endl;
	cout << "\t\t\t\t* Enter 5 to update    Enter 0 to end     *" << endl;
	cout << "\t\t\t\t*******************************************" << endl << endl;
}

static bool fileEmpty(ifstream& file, StudentL& stu)
{
	file.seekg(0, ios::end);
	int filesize = file.tellg();
	return (filesize == 0 || stu.count == -1);
}

int main()
{
	StudentL stu;
	int choice = 0;

	do
	{
		choices();
		ifstream file;
		file.open("Student.txt", ios::binary);

		if (fileEmpty(file, stu))
			cout << "The file is empty, to insert enter 1: " << endl;
		else
			cout << "Enter Your choice: " << endl;
		file.close();
		char s;
		cin >> s;
		choice = int(s) - 48;
		if (s >= '0' && s <= '5')
		{
			stu.create_tow_list();
			char id[30];
			switch (choice)
			{
			case 1:
				system("cls");
				stu.input();
				stu.pack();
				stu.write();
				system("cls");
				break;
			case 2:
				system("cls");
				if (!fileEmpty(file, stu))
				{
					stu.display();
					cout << "____________________________________________" << endl;
				}
				break;
			case 3:
				system("cls");
				if (!fileEmpty(file, stu))
				{
					stu.display();
					cout << "____________________________________________" << endl;
					cin.ignore();
					cout << "Enter id to search for: " << endl;
					cin.getline(id, 30);
					stu.search(id);
				}
				break;
			case 4:
				system("cls");
				if (!fileEmpty(file, stu))
				{
					stu.display();
					cout << "____________________________________________" << endl;
					cin.ignore();
					cout << "Enter id to remove: " << endl;
					cin.getline(id, 30);
					stu.remove(id);
				}
				break;
			case 5:
				system("cls");
				if (!fileEmpty(file, stu))
				{
					stu.display();
					cout << "____________________________________________" << endl;
					cin.ignore();
					cout << "Enter id to update: " << endl;
					cin.getline(id, 30);
					stu.update(id);
					system("cls");
				}
				break;
			}
		}
		else
		{
			system("cls");
			cout << "Invalid choice. Please try again." << endl;
			file.close();
		}
	} while (choice != 0);
	return 0;
}