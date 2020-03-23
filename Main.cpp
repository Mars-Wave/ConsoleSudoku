/*
Project 2: Sudoku.

	By: Team #16: Mohamed Ghanem & Tomás Moro Lías

	Notes: 
		- We are aware that we extensively use Windows.h library for aesthetic purposes, 
		and specially on the Sleep(3500) line it makes this project device-specific.

Hope you enjoy our take on the project!
*/

#include <iostream>
#include <conio.h> //we use getch
#include <Windows.h> // aesthetic use inside main
#include "checkML.h"
#include "SudokuList.h"
#include "PlayerList.h"
using namespace std;

int menu();

void waitkey(); //aesthetic use of getch()

void displayart();  //display asthetic art

void size(); //initial size is too small to see every ascii art, just there for comfort

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	tGame game;
	tSudokuList sudokulist;
	tPlayerList playerlist, rankAux;
	int aux= 0, aux1=0, aux2;
	size();
	createList(sudokulist);
	load(sudokulist);
	create(playerlist);
	load(playerlist);
	do {
		aux = menu();
		system("cls");
		switch (aux) {
		case 1:
			display(sudokulist);
			cout << "Your choice: ";
			cin >> aux2;
			system("cls");
			aux1 = playSudoku(sudokulist.sudokus[aux2 - 1]); //any sudoku choice not listed will show you main menu again
			if (aux1 > 0) {
				playerScore(playerlist, aux1);
			}
			break;
		case 2:
			sortByID(playerlist); //We understood ascending order as in A on top Z on bottom
			display(playerlist); 
			break;
		case 3:
			rankAux = rankSort(playerlist);  //We understood ascending order as in high on top, low on bottom
			display(rankAux);
			break;
		case 4:
			registerSudoku(sudokulist);
			break;
		default:
			break;
		}
		if (aux != 0 && aux != 1) { //if you exit or come back from sudoku you are not interested in the screen
			waitkey();
		}
		system("cls");
	} while (aux != 0);
	save(sudokulist);
	sortByID(playerlist);
	save(playerlist);
	free(playerlist);
	return 0;
}

int menu() {
	int option;
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	do {
		system("CLS"); //menu should just be once in screen
		displayart();
		SetConsoleTextAttribute(hConsoleHandle, 240);
		cout << "Main Menu:" << endl<<endl;
		SetConsoleTextAttribute(hConsoleHandle, 11);
		cout << "   1. Play" << endl;
		SetConsoleTextAttribute(hConsoleHandle, 14);
		cout << "   2. See players, sorted by ID" << endl;
		cout << "   3. See players, sorted by score" << endl;
		cout << "   4. Add sudoku" << endl;
		SetConsoleTextAttribute(hConsoleHandle, 4);
		cout << "   0. Exit" << endl << endl;
		SetConsoleTextAttribute(hConsoleHandle, 15);
		cout << "Your choice: ";
		cin >> option;
	} while (option < 0 || option > 4);
	return option;
}

void waitkey() {
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, 240);
	cout << endl<<"Press any key to continue";
	_getch();
	SetConsoleTextAttribute(hConsoleHandle, 15);
}

void displayart() {
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	string graphic="               ___          ___                       ___          ___          ___     \n              /\\__\\        /\\  \\        _____        /\\  \\        /|  |        /\\  \\    \n             /:/ _/_       \\:\\  \\      /::\\  \\      /::\\  \\      |:|  |        \\:\\  \\   \n            /:/ /\\  \\       \\:\\  \\    /:/\\:\\  \\    /:/\\:\\  \\     |:|  |         \\:\\  \\  \n           /:/ /::\\  \\  ___  \\:\\  \\  /:/  \\:\\__\\  /:/  \\:\\  \\  __|:|  |     ___  \\:\\  \\ \n          /:/_/:/\\:\\__\\/\\  \\  \\:\\__\\/:/__/ \\:|__|/:/__/ \\:\\__\\/\\ |:|__|____/\\  \\  \\:\\__\\\n          \\:\\/:/ /:/  /\\:\\  \\ /:/  /\\:\\  \\ /:/  /\\:\\  \\ /:/  /\\:\\/:::::/__/\\:\\  \\ /:/  /\n           \\::/ /:/  /  \\:\\  /:/  /  \\:\\  /:/  /  \\:\\  /:/  /  \\::/~~/~     \\:\\  /:/  / \n            \\/_/:/  /    \\:\\/:/  /    \\:\\/:/  /    \\:\\/:/  /    \\:\\~~\\       \\:\\/:/  /  \n              /:/  /      \\::/  /      \\::/  /      \\::/  /      \\:\\__\\       \\::/  /   \n              \\/__/        \\/__/        \\/__/        \\/__/        \\/__/        \\/__/    \n";
	string sudo = "                                   +-------+-------+-------+\n                                   | 3 9 4 | 8 5 2 | 6 7 1 | \n                                   | 2 6 8 | 3 7 1 | 4 5 9 | \n                                   | 5 7 1 | 6 9 4 | 8 2 3 | \n                                   +-------+-------+-------+\n                                   | 1 4 5 | 7 8 3 | 9 6 2 | \n                                   | 6 8 2 | 9 4 5 | 3 1 7 | \n                                   | 9 3 7 | 1 2 6 | 5 8 4 | \n                                   +-------+-------+-------+\n                                   | 4 1 3 | 5 6 7 | 2 9 8 | \n                                   | 7 5 9 | 2 3 8 | 1 4 6 | \n                                   | 8 2 6 | 4 1 9 | 7 3 5 | \n                                   +-------+-------+-------+\n\n";
	for (char &a : graphic) {
		if (a == '\\') {
			SetConsoleTextAttribute(hConsoleHandle, 6);
			putchar(a);
		}
		else if (a == ' ') {
			SetConsoleTextAttribute(hConsoleHandle, 15);
			putchar(a);
		}
		else if (a == ':') {
			SetConsoleTextAttribute(hConsoleHandle, 3);
			putchar(a);
		}
		else {
			SetConsoleTextAttribute(hConsoleHandle, 8); //blue
			putchar(a);
		}
		SetConsoleTextAttribute(hConsoleHandle, 15);
	}
	cout << "\n\t\t\t\tBy: Tomas Moro & Mohamed Ghanem.\n\n";
	for (char &a : sudo) {
		if (isdigit(a)) {
			SetConsoleTextAttribute(hConsoleHandle, 192); //red
			putchar(a);
		}
		else if (a == ' '|| a == '\n') {
			SetConsoleTextAttribute(hConsoleHandle, 15);
			putchar(a);
		}
		else if (a == '+') {
			SetConsoleTextAttribute(hConsoleHandle, 240);
			putchar(a);
		}
		else {
			SetConsoleTextAttribute(hConsoleHandle, 144); //blue
			putchar(a);
		}
		SetConsoleTextAttribute(hConsoleHandle, 15);
	}

}


void size() {
	system("MODE CON COLS=105 LINES=40");
	/*HANDLE hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);*/
}