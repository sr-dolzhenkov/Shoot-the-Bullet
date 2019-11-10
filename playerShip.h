#pragma once

class playerShip {
public:
  playerShip();
  ~playerShip();
  void moveLeft();
  void moveRight();
  void newGame();//перемещаем все элименты в начальное состояние

  const int getX();
  const int getY();

private:
  int x;
  const static int y = 17;
};
