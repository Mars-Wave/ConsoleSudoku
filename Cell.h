#ifndef Cell_h
#define Cell_h
#include "Set.h"

typedef enum { Empty, Fixed, Full } tCellState;

typedef struct {
	tCellState state;
	char number;
	tSet set;
}tCell;

void initCell(tCell &cell);
void fillCell(tCell &cell, char c, bool fixed = false);
void drawCell(const tCell &cell);
bool isSimple(const tCell & cell, int & number);
#endif