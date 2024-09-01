#include <iostream>
#include <fstream>
#include <stdlib.h> // atoi() => convert string to int
#include<cstring>  // strcopy() , strcat()
#include<cstdlib> 
#include<vector>
#include<string>
#include"StudentL.h"
using namespace std;
// get the input from the user:
void StudentL::input()
{
	cout << "Enter student ID: ";
	cin >> Id;
	cin.ignore();
	cout << "Enter student name: ";
	cin.getline(Name, 20);
	cout << "Enter student GPA: ";
	cin.getline(GPA, 4);
	cout << "Enter student address: ";
	cin.getline(Address, 50);
}
// save them in one line variable (buffer):
void StudentL::pack()
{
	// first make them all char []
	string strid = to_string(Id);
	char id[5] = {};
	for (int i = 0; i < strid.length(); ++i)
	{
		id[i] = strid[i];
	}

	strcpy_s(buffer, id);
	strcat_s(buffer, "|");
	strcat_s(buffer, Name);
	strcat_s(buffer, "|");
	strcat_s(buffer, GPA);
	strcat_s(buffer, "|");
	strcat_s(buffer, Address);
	strcat_s(buffer, "#");
}
// writing it in the file:
void StudentL::write()const
{
	fstream file;
	file.open("Student.txt", ios::app);
	file << buffer << endl;
	file.close();
}
// creating list for ids and indexes:
void StudentL::create_tow_list()
{
	int index = 0;
	count = -1;
	fstream file;
	file.open("Student.txt", ios::in);

	while (true)
	{
		file.getline(buffer, '#');
		int len = strlen(buffer);
		if (file.eof() || len == 0)
			break;
		if (*buffer == '*') // check if iti is deleted
		{
			index += len + 2;
			continue;
		}
		char* ptr = buffer;
		while (*ptr != '|')
			ptr++;
		*ptr = '\0';

		strcpy_s(id_list[++count], buffer);
		rec_index_list[count] = index;
		index += len + 2;
	}
	file.close();
	// sort them in the lists not the file
	sort();
}
// sorting them in the two lists:
void StudentL::sort()
{
	char temp[30];
	for (int x = 0; x <= count; x++)
		for (int y = x + 1; y <= count; y++)
			if (atoi(id_list[x]) > atoi(id_list[y]))
			{
				strcpy_s(temp, id_list[x]);
				strcpy_s(id_list[x], id_list[y]);
				strcpy_s(id_list[y], temp);

				int temp = rec_index_list[x];
				rec_index_list[x] = rec_index_list[y];
				rec_index_list[y] = temp;
			}
}
// the searching by id to get the index:
int StudentL::search_id(char key[30])
{
	int low = 0;
	int high = count;
	int mid = 0;
	int flag = 0;
	while (low <= high)
	{
		mid = (low + high) / 2;
		if (atoi(id_list[mid]) == atoi(key))
		{
			flag = 1;
			break;
		}
		else if (atoi(key) > atoi(id_list[mid]))
			low = mid + 1;// ignore the low half (binary search)
		else if (atoi(key) < atoi(id_list[mid]))
			high = mid - 1;// ignore the great half 
	}
	if (flag == 1)
		return mid;
	else
		return -1;// not found
}
// the basic search func():
void StudentL::search(char key[30])
{
	int index = search_id(key);// gitting the index for the id
	if (index != -1)// make sure that it is exist
	{
		int rec_index = rec_index_list[index];
		fstream file;
		file.open("Student.txt", ios::in);
		file.seekp(rec_index, ios::beg);
		file.getline(buffer, '#');
		cout << "Record Found: " << buffer << endl;
	}
	else
		cout << "Record Not Found" << endl;
}
//
void StudentL::remove(char key[30])
{
	int index = search_id(key);
	if (index != -1)
	{
		fstream file;
		file.open("Student.txt", ios::in | ios::out);
		int index_rec = rec_index_list[index];
		file.seekp(index_rec, ios::beg);
		file << '*';
		cout << "Record Deleted" << endl;
		count--;
		file.close();
	}
	else
		cout << "Record Not Found!" << endl;
}
//
void StudentL::update(char key[30])
{
	int index = search_id(key);
	if (index != -1)
	{
		remove(key);
		cout << "Enter new details:" << endl;
		input();

		buffer[0] = '\0';
		pack();

		fstream file;
		file.open("Student.txt", ios::in | ios::out);
		file.seekp(0, ios::end);
		file << buffer << endl;

		cout << "Record Updated Successfully!" << endl;
		file.close();
	}
	else
		cout << "Record Not Found!" << endl;
}

void StudentL::display()
{
	fstream file;
	file.open("Student.txt", ios::in);
	for (int x = 0; x < count + 1; x++)
	{
		int rec_index = rec_index_list[x];
		file.seekp(rec_index, ios::beg);
		file.getline(buffer, '#');
		cout << buffer << endl;
	}
	file.close();
}