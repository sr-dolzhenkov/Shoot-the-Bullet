#include <iostream>
#include "Reader.h"
#include "Plane.h"

Reader::Reader() {

}

Reader::~Reader() {

}

void Reader::read(char _button) {
	switch (_button) {
	case 65: MoveLeft();
		break;
	case 68: MoveRight();
		break;
	case 87: Shell();
		break;
	case 27: exit(0);
		break;
	}
}