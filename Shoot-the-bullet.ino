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
  digitalWrite(UP, HIGH);
  pinMode(RIGHT, INPUT_PULLUP);
  digitalWrite(RIGHT, HIGH);
  pinMode(DOWN, INPUT_PULLUP);
  digitalWrite(DOWN, HIGH);
  pinMode(LEFT, INPUT_PULLUP);
  digitalWrite(LEFT, HIGH);

  


  Serial.begin(115200);
}

void loop() {
  
  //ввод данных
  for (int i = 2; i < 6; i++) {
    if (digitalRead(i) == LOW) {
      input(i);
    }
  }

  //выввод данных
  output();
  
  delay(250);
  Field.flightShells();
  delay(250);
  Field.flightShells();
  delay(250);
  Field.flightShells();
  delay(250);
  Field.flightShells();
  Field.fallingRow();
}

void input(int buttonNumber) {
  switch (buttonNumber){
    case 2:
      Field.createShell(Player.getX());
      delay(250);
      break;
    case 3:
      Player.moveRight();
      delay(250);
      break;
    case 4:
      Player.moveLeft();
      delay(250);
      break;
    case 5:
      break;
  }
}

void output() {
  
}
