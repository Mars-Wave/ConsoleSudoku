#include "Game.h"
#include "SudokuList.h"
#include <iostream>
#include <Windows.h>
#include "checkML.h"
using namespace std;

void initGame(tGame &game, const tSudoku &sudoku) {
	game.sudoku.file = sudoku.file;
	game.sudoku.points = sudoku.points;
	init(game.board);
}

void displayGame(const tGame &game) {
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, 112);
	cout << "Solving:";
	SetConsoleTextAttribute(hConsoleHandle, 7);
	cout << " " << game.sudoku.file;
	SetConsoleTextAttribute(hConsoleHandle, 15);
	cout << "     ";
	SetConsoleTextAttribute(hConsoleHandle, 112);
	cout << "Score:";
	SetConsoleTextAttribute(hConsoleHandle, 7);
	cout << " " << game.sudoku.points << endl << endl;
	SetConsoleTextAttribute(hConsoleHandle, 15);
	draw(game.board);
	cout << endl;
}

bool loadGame(tGame &game, const tSudoku &sudoku) {
	bool canBeLoaded = true;
	if (!load(sudoku.file, game.board)) {
		canBeLoaded = false;
	}
	return canBeLoaded;
}

int playSudoku(const tSudoku &sudoku) {
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	int score = 0, sudokuNumber, option;
	tGame game;
	int row, col, number;
	initGame(game, sudoku);
	if (load(game.sudoku.file, game.board)) {
		do {
			displayGame(game);
			option = gameSpace::menu();
			switch (option) {
			case 1:
				cout <<endl <<"Provide cell's column: ";
				cin >> col;
				cout << "Provide cell's row: ";
				cin >> row;
				cout << endl;
				possible(game.board, row - 1, col - 1);
				Sleep(3500);										//Time to read it before system("cls") is 3.5s
				break;
			case 2:
				cout <<endl<< "Provide cell's column: ";
				cin >> col;
				cout << "Provide cell's row: ";
				cin >> row;
				cout << "Provide the value to insert: ";
				cin >> number;
				place(game.board, row - 1, col - 1, number);
				break;
			case 3:
				cout <<endl << "Provide cell's column:: ";
				cin >> col;
				cout << "Provide cell's row: ";
				cin >> row;
				if (game.board[row -1][col-1].state != Fixed) {
					erase(game.board, row - 1, col - 1);
				}
				break;
			case 4:
				restart(game);
				break;
			case 5:
				fillSimple(game.board);
				break;
			default:
				break;

			}
			system("cls");
		} while (!full(game.board) && option != 0);
		if (full(game.board)) {
			draw(game.board);
			score = sudoku.points;
			SetConsoleTextAttribute(hConsoleHandle, 240);
			cout << endl << "Congratulations! You won " << game.sudoku.file << "!" << endl << endl;
			SetConsoleTextAttribute(hConsoleHandle, 15);
		}
	}
	else {
		SetConsoleTextAttribute(hConsoleHandle, 79);
		cout << "Sudoku file not found in game library!" << endl;
		SetConsoleTextAttribute(hConsoleHandle, 15);
	}
	return score;
}

int gameSpace::menu() {
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsoleHandle, 15);
	int option;
	SetConsoleTextAttribute(hConsoleHandle, 240);
	cout << "Game Menu:" << endl << endl;
	SetConsoleTextAttribute(hConsoleHandle, 8);
	cout << "   1. Check values for a cell" << endl;
	cout << "   2. Put a value in a cell" << endl;
	cout << "   3. Delete cell's value" << endl;
	cout << "   4. Restart board" << endl;
	SetConsoleTextAttribute(hConsoleHandle, 12);
	cout << "   5. Autofill trivial cells" << endl;
	SetConsoleTextAttribute(hConsoleHandle, 4);
	cout << "   0. Return to main menu" << endl << endl;
	SetConsoleTextAttribute(hConsoleHandle, 15);
	cout << "Your choice: ";
	cin >> option;
	return option;
}

void restart(tGame &game) {
	initGame(game, game.sudoku);
	load(game.sudoku.file, game.board);
}