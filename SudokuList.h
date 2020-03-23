#ifndef SudokuList_h
#define SudokuList_h
#include "Game.h"


const int MAX_SUDOKUS = 20;
const std::string sudokuListName = "sudokulist.txt";
typedef tSudoku tSudokus[MAX_SUDOKUS];

typedef struct {
	tSudokus sudokus;
	int count;
}tSudokuList;

void createList(tSudokuList &list); 
bool load(tSudokuList &list); 
void display(const tSudokuList &list); 
void orderList(tSudokuList &list);
bool save(const tSudokuList &list);
bool registerSudoku(tSudokuList &list);
bool findFile(const tSudokuList &list, const std::string &filename);
int findPosition(const tSudokuList &list, const tSudoku &sudoku);
#endif