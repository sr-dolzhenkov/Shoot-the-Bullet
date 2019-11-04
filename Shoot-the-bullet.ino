#include "Field.h"
#include "playerShip.h"

const int UP = 2;
const int RIGHT = 3;
const int DOWN = 4;
const int LEFT = 5;

playerShip Player;
Field Field;

void setup() {
  pinMode(UP, INPUT_PULLUP);
  pinMode(RIGHT, INPUT_PULLUP);
  pinMode(DOWN, INPUT_PULLUP);
  pinMode(LEFT, INPUT_PULLUP);

  //вывод статических элиментов

  Serial.begin(115200);
}

void loop() {
  
  //ввод данных
  //вывод динамических данных
  Field.flightShells();
  
  Field.fallingRow();

  delay(1000);
}
