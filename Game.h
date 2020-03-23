#ifndef Game_h
#define Game_h
#include <string>
#include "Board.h"

typedef struct {
	int points;
	std::string file;
}tSudoku;

typedef struct {
	tSudoku sudoku;			//Represents which sudoku we be playin.
	tBoard board;			//Represents the board
	//bool gameOver;			//Represents if the board is full or not yet.
}tGame;

namespace gameSpace{
	int menu();
};

void initGame(tGame &game, const tSudoku &sudoku);
void displayGame(const tGame &game);
bool loadGame(tGame &game, const tSudoku &sudoku);
int playSudoku(const tSudoku &sudoku);
void restart(tGame &game);
#endif