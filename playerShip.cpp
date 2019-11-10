#include "playerShip.h"

playerShip::playerShip() {
  x = 5;
}

playerShip::~playerShip() {}

void playerShip::moveLeft() {
  if (x > 1) {
    x--;
  }
  else {
    x = 11;
  }
}

void playerShip::moveRight() {
  if (x < 11) {
    x++;
  }
  else {
    x = 1;
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
