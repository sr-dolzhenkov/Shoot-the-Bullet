#pragma once

class playerShip {
public:
  playerShip();
  ~playerShip();
  void moveLeft();
  void moveRight();

  int getX();
  int getY();

private:
  int x;
  const static int y = 17;
};
