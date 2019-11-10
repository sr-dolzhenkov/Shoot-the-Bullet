#include <LCD5110_Graph.h>

#include "Field.h"
#include "playerShip.h"

#define UP_PIN 2
#define RIGHT_PIN 3
#define DOWN_PIN 4
#define LEFT_PIN 5

LCD5110 LCD(9, 10, 11, 12, 13);

playerShip Player;
Field Field;

void input();
void output();

const int width = 13;
const int height = 20;

void setup() {
  pinMode(UP_PIN, INPUT_PULLUP);
  digitalWrite(UP_PIN, HIGH);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  digitalWrite(RIGHT_PIN, HIGH);
  pinMode(DOWN_PIN, INPUT_PULLUP);
  digitalWrite(DOWN_PIN, HIGH);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  digitalWrite(LEFT_PIN, HIGH);

  LCD.InitLCD();  

  Serial.begin(115200);
}

void loop() {
  
  //ввод данных
  for (int i = 2; i < 6; i++) {
    if (digitalRead(i) == LOW) {
      input(i);
    }
  }

  //выввод данных и не только
  output();
  delay(250);
  Field.flightShells();
  output();
  delay(250);
  Field.flightShells();
  output();
  delay(250);
  Field.flightShells();
  output();
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
      Field.newGame();
      Player.newGame();
      delay(250);
      break;
  }
}

void output() {
  if (!(Field.getLoseTrigger())) {
    LCD.disableSleep();
    LCD.clrScr();

    LCD.drawRect(0, 0, 12, 19);
    LCD.setPixel(Player.getX(), Player.getY());
    for (int i = 0; i < height - 2; i++) {
      for (int j = 0; j < width - 2; j++) {
        if (Field.getDataRows(i, j)) {
          LCD.setPixel(i + 1, j + 1);
        }
      }
    }
    for (int i = 0; i < height - 2; i++) {
      if (Field.getDataShellsX(i) != -1) {
        LCD.setPixel(Field.getDataShellsX(i), Field.getDataShellsY(i));
      }
    }
    LCD.update();
    
    LCD.print("POINTS", 14, 0);
    LCD.printNumI(Field.getPoints(), 14, 8);
    LCD.enableSleep();
  }
  else {
    LCD.disableSleep();
    LCD.clrScr();
    LCD.print("GAME OVER", CENTER, 0);
    LCD.enableSleep();
  }
}
