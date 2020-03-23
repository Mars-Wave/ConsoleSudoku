#include <iostream>
#include <iomanip>
#include <fstream>
#include <Windows.h>
#include "PlayerList.h"
#include "checkML.h"
using namespace std;

void create(tPlayerList &list) {
	list.playerArr = new tPlayerPtr[init_NUM];
	list.size = init_NUM;
	list.count = 0;
}

bool load(tPlayerList &list) {	// list.size
	bool aux = false;
	ifstream file;
	file.open("playerlist.txt");
	if (file.is_open())
	{
		aux = true;
		do {
			list.playerArr[list.count] = new tPlayer;
			file >> list.playerArr[list.count]->ID >> list.playerArr[list.count]->points; //Check
			list.count++;
			if (list.size == list.count) {
				resize(list);
			}
		} while (!file.eof() /*&& list.count < MAX_PLAYERS*/); //no limit to # of players
		file.close();
	}
	return aux;
}

void display(const tPlayerList &list) {
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, 240);
	cout << "NAME";
	SetConsoleTextAttribute(hConsoleHandle, 15);
	cout << "                                                  ";
	SetConsoleTextAttribute(hConsoleHandle, 240);
	cout << "SCORE" << endl;
	SetConsoleTextAttribute(hConsoleHandle, 3);
	cout << "~~~~                                                  ~~~~~" << endl << endl;
	SetConsoleTextAttribute(hConsoleHandle, 15);
	cout << "-----------------------------------------------------------" << endl;
	for (int i = 0; i < list.count; i++)
	{
		SetConsoleTextAttribute(hConsoleHandle, 15);
		cout << left << setw(40);
		SetConsoleTextAttribute(hConsoleHandle, 14);
		cout << list.playerArr[i]->ID;
		cout << setw(18);
		SetConsoleTextAttribute(hConsoleHandle, 7);
		cout << right << fixed << setprecision(2) << list.playerArr[i]->points<<endl; 
		SetConsoleTextAttribute(hConsoleHandle, 6);
		if (i < list.count - 1) {
			cout << "-----------------------------------------------------------" << endl; // last line this will be white
		}
		SetConsoleTextAttribute(hConsoleHandle, 15);
	}
	cout << "-----------------------------------------------------------" << endl;
	cout << endl;
}

bool save(const tPlayerList &list) {
	bool aux = false;
	ofstream file;
	file.open("playerlist.txt");
	if (file.is_open())
	{
		aux = true;
		file << toString(*list.playerArr[0]);
		for (int i = 1; i < list.count; i++)
		{
			file << endl << toString(*list.playerArr[i]);
		}
	}
	return aux;
}

void playerScore(tPlayerList &list, int score) {
	int pos = 0;			// int pos; kanet
	string aux;
	cout << "Enter player ID (ONE WORD): ";  //we tried using getline but we couldn't handle the buffer butting in characters and sometimes winded up with 2 players with same ID
	cin >> aux;
	if (find(list, aux, pos))
	{
		modifyPlayer(*list.playerArr[pos], score);
	}
	else {
		list.playerArr[pos] = new tPlayer;
		list.playerArr[pos]->ID = aux;
		list.playerArr[pos]->points = score;
		list.count++;
		if (list.count == list.size) {
			resize(list);
		}
	}
}

bool find(const tPlayerList &list, string id, int &pos) {
	bool found = false;
	int beg = 0, end = list.count - 1;
	pos = binarySearch(list, id, beg, end);
	if (pos != -1) {
		found = true;
	}
	else {
		pos = list.count;
	}
	return found;
}

int binarySearch(const tPlayerList &list, string id, int beg, int end) {
	int pos = -1, middle;
	if (beg <= end) {
		middle = (beg + end) / 2;
		if (id == list.playerArr[middle]->ID) {
			pos = middle;
		}
		else if (id < list.playerArr[middle]->ID) {
			pos = binarySearch(list, id, beg, middle - 1);
		}
		else {
			pos = binarySearch(list, id, middle + 1, end);
		}
	}
	return pos;
}

tPlayerList rankSort(const tPlayerList &list) {
	tPlayerList aux;	
	tPlayer player;
	aux = list;
	for (int i = 0; i < list.count; i++) {
		for (int j = 0; j < list.count; j++) {
			if (smaller(*aux.playerArr[j], *aux.playerArr[i])) {
				player = *aux.playerArr[i];
				*aux.playerArr[i] = *aux.playerArr[j];
				*aux.playerArr[j] = player;
			}
		}
	}
	return aux;
}

void sortByID(tPlayerList &list) {
	tPlayer player;
	for (int i = 0; i < list.count; i++) {
		for (int j = 0; j < list.count; j++) {
			if (*list.playerArr[j] < *list.playerArr[i]) {
				player = *list.playerArr[i];
				*list.playerArr[i] = *list.playerArr[j];
				*list.playerArr[j] = player;
			}
		}
	}
}

void free(tPlayerList &list) {
	for (int i = 0; i < list.count; i++)
	{
		delete list.playerArr[i];
	}
	delete[] list.playerArr;
}

void resize(tPlayerList &list) {
	tPlayerList newList;
	newList.playerArr = new tPlayerPtr[2*list.size];
	newList.size = 2 * list.size;
	newList.count = list.count;
	for (int i = 0; i < list.count; i++)
	{
		newList.playerArr[i] = new tPlayer;
		*newList.playerArr[i] = *list.playerArr[i];
	}
	free(list);
	list = newList;

}