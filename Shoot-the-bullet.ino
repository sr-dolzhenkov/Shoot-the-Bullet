#include <LCD5110_Graph.h>

#include "Field.h"
#include "playerShip.h"

#define UP_PIN 2
#define RIGHT_PIN 3
#define DOWN_PIN 4
#define LEFT_PIN 5

//LCD5110 LCD(9, 10, 11, 13, 12);
LCD5110 LCD(9, 10, 11, 12, 13);

extern unsigned char SmallFont[];

playerShip Player;
Field Field;

void input();
void output();

const int width = 13;
const int height = 20;

const int sizeField = 2;

void setup() {
  //pinMode(7, OUTPUT);
  //digitalWrite(7, LOW);  
  
  pinMode(UP_PIN, INPUT_PULLUP);
  digitalWrite(UP_PIN, HIGH);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  digitalWrite(RIGHT_PIN, HIGH);
  pinMode(DOWN_PIN, INPUT_PULLUP);
  digitalWrite(DOWN_PIN, HIGH);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  digitalWrite(LEFT_PIN, HIGH);

  LCD.InitLCD();

  LCD.setFont(SmallFont);

  Serial.begin(115200);
}

void loop() {
  
  //ввод данных, если есть сигнал, то обрабатываем его
  //каждую четверть секунды происходит выввод данных и полёт снарядов
  //каждую секунду опускается ряды
  for (int i = 0; i < 20; i++) {
    output();
    for (int i = 2; i < 6; i++) {
      if (digitalRead(i) == LOW) {
       input(i);
      }
    }
    delay(150);
    Field.flightShells();
  }
  
  Field.fallingRow();
}

void input(int buttonNumber) {
  switch (buttonNumber){
    case 2:
      Field.createShell(Player.getX());
      break;
    case 3:
      Player.moveRight();
      break;
    case 4:
      Field.newGame();
      Player.newGame();
      break;
    case 5:
      Player.moveLeft();
      break;
  }
}
//если состояние игры не проигрышь, то рисуем соответсвующие элименты, иначе выводим информацию о проигрыше
void output() {
  if (!(Field.getLoseTrigger())) {
    LCD.clrScr();
    LCD.drawRect(0, 0, 11 * sizeField + 1, 18 * sizeField + 1);
    for (int i = 0; i < sizeField; i++) {
      for (int j = 0; j < sizeField; j++) {
        LCD.setPixel(Player.getX() * sizeField + 1 + i, Player.getY() * sizeField + 1 + j);
      }
    }
    for (int i = 0; i < height - 2; i++) {
      for (int j = 0; j < width - 2; j++) {
        if (Field.getDataRows(i, j)) {
          for (int _i = 0; _i < sizeField; _i++) {
            for (int _j = 0; _j < sizeField; _j++) {
              LCD.setPixel(j * sizeField + 1 + _j, i * sizeField + 1 + _i);
            }
          }
        }
      }
    }
    for (int i = 0; i < height - 2; i++) {
      if (Field.getDataShellsX(i) != -1) {
        for (int _i = 0; _i < sizeField; _i++) {
          for (int _j = 0; _j < sizeField; _j++) {
            LCD.setPixel(Field.getDataShellsX(i) * sizeField + 1 + _i, Field.getDataShellsY(i) * sizeField + 1 + _j);
          }
        }
      }
    }
    
    LCD.print("POINTS", RIGHT, 0);
    LCD.printNumI(Field.getPoints(), RIGHT, 8);
    LCD.update();
  }
  else {
    LCD.clrScr();
    LCD.print("GAME OVER", CENTER, 0);
    LCD.print("POINTS", CENTER, 8);
    LCD.printNumI(Field.getPoints(), CENTER, 16);
    LCD.update();
  }
}
