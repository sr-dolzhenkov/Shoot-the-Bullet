#include "Row.h"
#include <cstdlib>

Row::Row(int _y) {
	y = _y;
	x = 0;
}

Row::~Row() {}

void Row::CreateBlock(int _x) {
	x |= _x;
}

bool Row::CheckWin() {
	return x == 511;
}

void Row::CreateRow() {
	x = rand() % 511;
}

void Row::Clean() {
	x = 0;
}

bool Row::CheckLose() {

}

void Row::NewGame() {
	
}