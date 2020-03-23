#include "SudokuList.h"
#include <iostream>
#include <windows.h>
#include "checkML.h"
using namespace std;

void createList(tSudokuList &list) {
	list.count = 0;
}

bool load(tSudokuList &list) {
	bool canBeLoaded = true;
	ifstream file;
	string name;
	int score, pos = 0;
	file.open(sudokuListName);
	if (!file.is_open()) {
		canBeLoaded = false;
	}
	else {
		while (!file.eof()) {
			file >> name;
			file >> score;
			list.sudokus[list.count].file = name;
			list.sudokus[list.count].points = score;
			list.count++;
		}
		orderList(list);
	}
	return canBeLoaded;
}

void display(const tSudokuList &list) {
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, 240);
	cout << "Sudokus found in your library:" << endl <<endl;
	for (int i = 0; i < list.count; i++) {
		SetConsoleTextAttribute(hConsoleHandle, 159);
		cout << "Sudoku number ";
		SetConsoleTextAttribute(hConsoleHandle, 156);
		cout << i + 1; 
		SetConsoleTextAttribute(hConsoleHandle, 159);
		cout << ":" << endl;
		SetConsoleTextAttribute(hConsoleHandle, 8);
		cout << "    Text file: ";
		SetConsoleTextAttribute(hConsoleHandle, 15);
		cout << list.sudokus[i].file << endl;
		SetConsoleTextAttribute(hConsoleHandle, 8);
		cout << "    Difficulty points: ";
		SetConsoleTextAttribute(hConsoleHandle, 15);
		cout << list.sudokus[i].points << endl << endl;
	}
}

void orderList(tSudokuList &list)
{
	tSudoku sudaka;
	for (int i = 0; i < list.count; i++) {
		for (int j = 0; j < list.count; j++) {
			if (list.sudokus[i].points < list.sudokus[j].points) {
				sudaka = list.sudokus[i];
				list.sudokus[i] = list.sudokus[j];
				list.sudokus[j] = sudaka;
			}
			else if (list.sudokus[i].points == list.sudokus[j].points) {
				if (list.sudokus[i].file < list.sudokus[j].file) {
					sudaka = list.sudokus[i];
					list.sudokus[i] = list.sudokus[j];
					list.sudokus[j] = sudaka;
				}
			}
		}
	}
}

bool save(const tSudokuList &list) {
	bool canBeSaved = true;
	ofstream file;
	file.open(sudokuListName);
	if (!file.is_open()) {
		canBeSaved = false;
	}
	else {
		file << list.sudokus[0].file << " " << list.sudokus[0].points;
		for (int i = 1; i < list.count; i++)
		{
			file << endl << list.sudokus[i].file << " " << list.sudokus[i].points;
		}
		file.close();
	}
	return canBeSaved;
}

bool registerSudoku(tSudokuList &list) {
	bool canBeRegistered = true, found = false;
	string fileName;
	int score, pos = 0;
	tSudoku sud;
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (list.count < MAX_SUDOKUS) {
		SetConsoleTextAttribute(hConsoleHandle, 240);
		cout << "New Sudoku:"<<endl <<endl <<endl;
		SetConsoleTextAttribute(hConsoleHandle, 3);
		cout << "   Enter the new sudoku's ";
		SetConsoleTextAttribute(hConsoleHandle, 12);
		cout << "filename";
		SetConsoleTextAttribute(hConsoleHandle, 3);
		cout << ": ";
		SetConsoleTextAttribute(hConsoleHandle, 15);
		cin >> fileName;
		if (!findFile(list, fileName)) {
			SetConsoleTextAttribute(hConsoleHandle, 3);
			cout << endl <<endl << "   Enter the ";
			SetConsoleTextAttribute(hConsoleHandle, 12);
			cout << "difficulty points";
			SetConsoleTextAttribute(hConsoleHandle, 3);
			cout << " the new sudoku will be worth: ";
			SetConsoleTextAttribute(hConsoleHandle, 15);
			cin >> score;
			sud.file = fileName;
			sud.points = score;
			pos = findPosition(list, sud);
			for (int i = list.count - 1; i >= pos; i--)		
			{
					list.sudokus[i + 1] = list.sudokus[i];
			}
			list.sudokus[pos].file = fileName;
			list.sudokus[pos].points = score;
			list.count++;
		}
		else {
			SetConsoleTextAttribute(hConsoleHandle, 79); 
			cout <<endl << endl<< "Filename is already registered in your library." << endl;
			SetConsoleTextAttribute(hConsoleHandle, 15);
			canBeRegistered = false;
		}
	}
	else {
		canBeRegistered = false;
		SetConsoleTextAttribute(hConsoleHandle, 79);
		cout << endl << endl << "You can't register more sudokus!" << endl;
		SetConsoleTextAttribute(hConsoleHandle, 15);
	}
	return canBeRegistered;
}

bool findFile(const tSudokuList &list, const string &filename) {
	bool found = false;
	int pos = 0;
	while (pos < list.count && !found)
	{
		if (list.sudokus[pos].file == filename) {
			found = true;
		}
		pos++;
	}
	return found;
}

int findPosition(const tSudokuList &list, const tSudoku &sudoku) {
	int pos = -1, beg = 0, end = list.count - 1, middle;
	bool found = false;
	while ((beg <= end) && !found) {
		middle = (beg + end) / 2;
		if (sudoku.points == list.sudokus[middle].points) {
			while ((beg <= end) && !found) {
				middle = (beg + end) / 2;
				if (sudoku.file > list.sudokus[middle].file && sudoku.file < list.sudokus[middle + 1].file || middle == end || middle == 0) {
					found = true;
				}
				else if (sudoku.file < list.sudokus[middle].file) {
					end = middle - 1;
				}
				else if (sudoku.file > list.sudokus[middle].file) {
					beg = middle + 1;
				}
			}
		}
		if (sudoku.points > list.sudokus[middle].points && sudoku.points < list.sudokus[middle+1].points || middle == end || middle == 0) {
			found = true;
		}
		else if (sudoku.points < list.sudokus[middle].points) {
			end = middle - 1;
		}
		else if (sudoku.points > list.sudokus[middle].points) {
			beg = middle + 1;
		}
	}
	if (found) {
		pos = middle+1;
	}
	return pos;
}