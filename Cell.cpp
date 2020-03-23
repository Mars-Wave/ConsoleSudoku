#include "Cell.h"
#include "Windows.h"
#include <iostream>
#include "checkML.h"
using namespace std;


void initCell(tCell &cell) {
	cell.state = Empty;
	fullSet(cell.set);
}

void fillCell(tCell &cell, char c, bool fixed) {	//Check it outa
		if (c == ' ') {
			cell.state = Empty;
		}
		else{
			cell.state = Full;
		}
		if (fixed) {
			cell.state = Fixed;
		}
		cell.number = c;
}

void drawCell(const tCell &cell) {
	HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	if (cell.state == Fixed) {
		SetConsoleTextAttribute(hConsoleHandle, 144); //blue
	}
	else if (cell.state == Full) {
		SetConsoleTextAttribute(hConsoleHandle, 192); //red
	}
	cout << cell.number;
	SetConsoleTextAttribute(hConsoleHandle, 15);
}

bool isSimple(const tCell & cell, int & number) {			//Check it outa
	bool itIs = false;
	if (cell.state == Empty) {
		if (one(cell.set, number)) {
			itIs = true;
		}
	}
	return itIs;
}