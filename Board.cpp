#include <Windows.h>
#include <iostream>
#include "Board.h"
#include "checkML.h"
using namespace std;

void init(tBoard board) {						//We have to also do all values in interval [1,,,9]
	for (int row = 0; row < NUMBERS; row++) {
		for (int col = 0; col < NUMBERS; col++) {
			initCell(board[row][col]);
		}
	}
}

bool load(const string &filename, tBoard board) {	//Check if file.get works!
	bool canBeLoaded = true;
	ifstream file;
	char num, discard;
	file.open(filename);
	if (!file.is_open()) {
		canBeLoaded = false;
	}
	else {
		for (int row = 0; row < NUMBERS; row++) {
			for (int col = 0; col < NUMBERS; col++) {
				file.get(num);
				if (place(board, row, col, integer(num))) { //trivially true
					fillCell(board[row][col], num, num != ' ');
				}
			}
			file.get(discard);
		}
	}
	return canBeLoaded;
}

void draw(const tBoard board) {
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "    ";
	putchar(179);
	for (int i = 1; i < 10; i++) {
		SetConsoleTextAttribute(hConsoleHandle, 224);
		cout << " " << i << " ";
		SetConsoleTextAttribute(hConsoleHandle, 15);
		putchar(179);
	}
	cout << endl;
	//nums

	putchar(196);
	putchar(196);
	putchar(196);
	cout << " ";

	SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE);
	putchar(218);
	putchar(196);
	putchar(196);
	putchar(196);
	for (int i = 0; i < 8; i++) {
		putchar(194);
		putchar(196);
		putchar(196);
		putchar(196);
	}
	putchar(191);
	cout << endl;
	//toprow

	SetConsoleTextAttribute(hConsoleHandle, 224);
	cout << " 1 ";
	SetConsoleTextAttribute(hConsoleHandle, 15);
	cout << " ";
	SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE);
	putchar(179);
	for (int j = 1; j < 10; j++) {
		cout << " ";
		if (board[0][j - 1].state != Empty) {
			drawCell(board[0][j - 1]);
		}
		else {
			cout << " ";
		}
		cout << " "; //board[i][j];
		if (j % 3 == 0) {
			SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE);
		}
		else {
			SetConsoleTextAttribute(hConsoleHandle, 15);
		}
		putchar(179);
	}
	cout << endl;
	SetConsoleTextAttribute(hConsoleHandle, 15); //starting row


	for (int i = 2; i < 10; i++) { //starts at 2 for cout purposes

		putchar(196);
		putchar(196);
		putchar(196);
		cout << " ";

		SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE);
		putchar(195);
		if ((i - 1) % 3 == 0) {
			SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE);
		}
		else {
			SetConsoleTextAttribute(hConsoleHandle, 15);
		}
		for (int k = 1; k < 9; k++) {
			putchar(196);
			putchar(196);
			putchar(196);
			if (k % 3 == 0 || k == 9) {
				SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE);
			}
			putchar(197);
			if ((i - 1) % 3 == 0) {
				SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE);
			}
			else {
				SetConsoleTextAttribute(hConsoleHandle, 15);
			}
		}
		putchar(196);
		putchar(196);
		putchar(196);
		SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE);
		putchar(180);
		cout << endl;
		SetConsoleTextAttribute(hConsoleHandle, 224);
		cout << " " << i << " ";
		SetConsoleTextAttribute(hConsoleHandle, 15);
		cout << " ";
		SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE);
		putchar(179);
		for (int j = 1; j < 10; j++) {
			cout << " ";
			if (board[i - 1][j - 1].state != Empty) {
				drawCell(board[i - 1][j - 1]);
			}
			else {
				cout << " ";
			}
			cout << " ";//board[i][j];
			if (j % 3 == 0) {
				SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE);
			}
			else {
				SetConsoleTextAttribute(hConsoleHandle, 15);
			}
			putchar(179);
			SetConsoleTextAttribute(hConsoleHandle, 15);
		}
		cout << endl;


	}		//body of sudoku


	putchar(196);
	putchar(196);
	putchar(196);
	SetConsoleTextAttribute(hConsoleHandle, FOREGROUND_BLUE);
	cout << " ";
	putchar(192);
	putchar(196);
	putchar(196);
	putchar(196);
	for (int i = 0; i < 8; i++) {
		putchar(193);
		putchar(196);
		putchar(196);
		putchar(196);
	}
	putchar(217);
	//botrow
	cout << endl;
	SetConsoleTextAttribute(hConsoleHandle, 15);
}


bool place(tBoard board, int row, int col, int c) {
	bool aux = board[row][col].state == Empty && (c < 10 && c > 0);
	if (aux) {
		char disp = tochar(c);
		board[row][col].number = disp;
		for (int i = 0; i < 9; i++) {
			erase(board[row][i].set, c);
			erase(board[i][col].set, c);
		}                                            //row n col

		for (int i = (row / 3) * 3; i < row / 3 * 3 + 3; i++) {
			for (int j = (col / 3) * 3; j < col / 3 * 3 + 3; j++) {
				erase(board[i][j].set, c);
			}
		}                                    //region
		board[row][col].state = Full;
	}
	return aux;
}

bool erase(tBoard board, int row, int col) {
	bool aux = board[row][col].state == Full && board[row][col].state != Fixed;
	if (aux) {
		board[row][col].state = Empty;
		for (int i = 0; i < 9; i++) {
			add(board[row][i].set, integer(board[row][col].number));
			add(board[i][col].set, integer(board[row][col].number));
		}                                            //row n col

		for (int i = (row / 3) * 3; i < row / 3 * 3 + 3; i++) {
			for (int j = (col / 3) * 3; j < col / 3 * 3 + 3; j++) {
				add(board[i][j].set, integer(board[row][col].number));
			}
		}                                                    //region
	}

	return aux;
}

bool full(const tBoard board) {
	bool aux = true;
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			if (size(board[row][col].set) != 0) {
				aux = false;
			}
		}
	}
	return aux;
}

void possible(const tBoard board, int row, int col) {
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, 63);
	cout << "All possible values for cell at " << col + 1 << " , " << row + 1 << " are:" << endl;
	SetConsoleTextAttribute(hConsoleHandle, 9);
	display(board[row][col].set);
	SetConsoleTextAttribute(hConsoleHandle, 15);
}

void fillSimple(tBoard board) {
	int n;
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			if (isSimple(board[row][col], n)) {
				place(board, row, col, n);
			}
		}
	}
}

int integer(char num) {
	int aux = num - '0';
	return aux;
}

int tochar(int value)
{
	return '0' + value;
}
