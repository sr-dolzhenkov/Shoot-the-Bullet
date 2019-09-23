#include "Shell.h"

Shell::Shell(int _x) {
	x = _x;
	y = 1;
}

Shell::~Shell() {}

bool Shell::Let() {

}

void Shell::Flight() {
	y++;
}