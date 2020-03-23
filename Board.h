#ifndef Board_h
#define Board_h
#include "Cell.h"
#include <string>
#include <fstream>

typedef tCell tBoard[NUMBERS][NUMBERS];

void init(tBoard board);
bool load(const std::string &filename, tBoard board);
void draw(const tBoard board);
bool place(tBoard board, int row, int col, int c);
bool erase(tBoard board, int row, int col);
bool full(const tBoard board);
void possible(const tBoard board, int row, int col);
void fillSimple(tBoard board);
int integer(char num);
int tochar(int value);
#endif