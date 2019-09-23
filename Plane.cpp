#include "Plane.h"

Plane::Plane() {
	x = 1>>5;
	y = 1;
}

Plane::~Plane() {}

void Plane::MoveLeft() {
	x <<= 1;
}

void Plane::MoveRight() {
	x >>= 1;
}