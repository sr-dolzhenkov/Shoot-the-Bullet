#include "playerShip.h"

playerShip::playerShip() {
  x = 5;
}

playerShip::~playerShip() {}

void playerShip::moveLeft() {
  if (x > 0) {
    x--;
  }
  else {
    x = 10;
  }
}

void playerShip::moveRight() {
  if (x < 10) {
    x++;
  }
  else {
    x = 0;
  }
}

void playerShip::newGame() {
  x = 5;
}

const int playerShip::getX() {
  return x;
}

const int playerShip::getY() {
  return y;
}
