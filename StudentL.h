#pragma once
class StudentL
{
private:
	char Name[20];
	int Id;
	char GPA[5];
	char Address[50];
	char buffer[80];
	char id_list[1000][80];
	int rec_index_list[1000];
public:
	int count;
	StudentL() :buffer("") {}
	void input();
	void pack();
	void write()const;
	void create_tow_list();
	int search_id(char key[30]);
	void search(char key[30]);
	void sort();
	void remove(char key[30]);
	void display();
	void update(char key[30]);
};

