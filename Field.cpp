#include "Field.h"

Field::Field() {
  for (int i = 0; i < height - 2; i++) {
    for (int j = 0; j < width - 2; j++) {
      dataRows[i][j] = false;
    }
  }

  for (int i = 0; i < height - 2; i++) {
    dataShells[i][0] = -1;
    dataShells[i][1] = -1;
  }

  points = 0;

  loseTrigger = false;
}

Field::~Field() {}

void Field::createShell(int _x) {
  for (int i = 0; i < height - 2; i++) {
    if (dataShells[i][0] == 0) {
      dataShells[i][0] = _x;
      dataShells[i][1] = height - 4;
      break;
    }
  }
}

void Field::deleteShell(int pos) {
  dataShells[pos][0] = -1;
  dataShells[pos][1] = -1;
}

void Field::createRow() {
  int t = 0;
  for (int j = 0; j < width - 2; j++) {
    //dataRows[0][j] = random(2);
    dataRows[0][j] = 1;
    if (dataRows[0][j] == 1) {
      t++;
    }
  }
  if (t == width - 2) {
    //dataRows[0][random(18)] = 0;
    dataRows[0][0] = 0;
  }
}

void Field::fallingRow() {
  for (int i = height - 3; i > 0; i--) {
    for (int j = 0; j < width - 2; j++) {
      dataRows[i][j] = dataRows[i - 1][j];
    }
  }

  createRow();
  if (checkLose()) {
    lose();
  }
}

void Field::deleteRow(int _y) {
  for (int j = 0; j < width - 2; j++) {
    dataRows[_y][j] = 0;
  }
  points++;
}

bool Field::checkCollision(int _x, int _y) {
  return (dataRows[--_y][_x] == 1);
}

void Field::flightShells() {
  for (int i = 0; i < height - 2; i++) {
    if (dataShells[i][0] != -1) {
      dataShells[i][1]--;
      if ((checkCollision(dataShells[i][0], dataShells[i][1])) || (dataShells[i][1] == 0)) {
        deleteShell(i);
        changeRow(dataShells[i][0], dataShells[i][1]);
        if (checkRow(dataShells[i][1])) {
          deleteRow(dataShells[i][1]);
        }
      }
    }
  }
}

void Field::changeRow(int _x, int _y) {
  dataRows[_y][_x] = 1;
}

bool Field::checkRow(int _y) {
  bool t = true;
  for (int j = 0; j < width - 2; j++) {
    if (dataRows[_y][j] == 0) {
      t = false;
      break;
    }
  }
  return t;
}

bool Field::checkLose() {
  bool t = false;
  for (int j = 0; j < width - 2; j++) {
    if (dataRows[height - 3][j] == 1) {
      t = true;
      break;
    }
  }
  return t;
}

void Field::lose() {
  loseTrigger = true;
}

void Field::newGame() {
  for (int i = 0; i < height - 2; i++) {
    for (int j = 0; j < width - 2; j++) {
      dataRows[i][j] = false;
    }
  }
  for (int i = 0; i < height - 2; i++) {
    dataShells[i][0] = -1;
    dataShells[i][1] = -1;
  }
  points = 0;
  loseTrigger = false;
}

const int Field::getDataShellsX(int _i) {
  return dataShells[_i][0];
}

const int Field::getDataShellsY(int _i) {
  return dataShells[_i][1];
}

const bool Field::getDataRows(int _x, int _y) {
  return dataRows[_x][_y];
}

const int Field::getPoints() {
  return points;
}

const bool Field::getLoseTrigger() {
  return loseTrigger;
}
