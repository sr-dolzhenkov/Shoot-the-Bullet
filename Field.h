#pragma once

class Field {
public:
  Field();
  ~Field();
  void createShell(int _x);
  void deleteShell(int pos);
  void createRow();
  void fallingRow();
  void deleteRow(int _y);
  bool checkCollision(int _x, int _y);
  void flightShells();
  void changeRow(int _x, int _y);
  bool checkRow(int _y);
  bool checkLose();
  void lose();
  void newGame();

  const int* getDataShells();
  const bool* getDataRows();

private:
  const static int width = 13;
  const static int height = 20;

  //bool field [height][width];//???
  int dataShells[height - 2][2];
  bool dataRows[height - 2][width - 2];
};
