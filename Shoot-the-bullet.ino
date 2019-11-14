#include <LCD5110_Graph.h>

#include "string.h"

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

void input(int buttonNumber);
void output();

const int width = 13;
const int height = 20;

int sizeField;
bool t = false;

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
  label:
  if (Field.getMenuTrigger()) {
    for (int i = 2; i < 6; i++) {
      if (digitalRead(i) == LOW) {
        input(i);
      }
    }
    output();
    delay(150);
  }
  //каждые 150 мс выввод данных и полёт снарядов
  //каждые 4.5 с опускается ряды на первой сложности
  else if (Field.getGameTrigger()) {
    for (int h = 0; h < 40 - Field.getDifficulty() * 10; h++) {
      output();
      for (int i = 2; i < 6; i++) {
        if (digitalRead(i) == LOW) {
          input(i);
          if (t) {
            t = false;
            goto label;
          }
        }
      }
      delay(150);
      Field.flightShells();
    }
    Field.fallingRow();
  }
  else if (Field.getLoseTrigger()) {
    for (int i = 2; i < 6; i++) {
      if (digitalRead(i) == LOW) {
        input(i);
      }
    }
    output();
    delay(150);
  }
  else if (Field.getTabTrigger()) {
    for (int i = 2; i < 6; i++) {
      if (digitalRead(i) == LOW) {
        input(i);
      }
    }
    output();
    delay(150);
  }
}
//смотрим состояние игры - рисуем соответсвующие элементы
void input(int buttonNumber) {
  if (Field.getMenuTrigger()) {
    switch (buttonNumber){
     case 2:
       Field.minusMenuState();
       break;
     case 3:
       if (Field.getMenuState() == 0) { 
         Field.newGame();
         Player.newGame();
       }
       else if ((Field.getMenuState() == 1) && (Field.getGameState())) {
         Field.toGame(); 
       }
       else if ((Field.getMenuState() == 2)) {
         Field.plusDifficulty(); 
       }
       else if ((Field.getMenuState() == 3)) {
         Field.plusSizeField(); 
       }
       else if ((Field.getMenuState() == 4)) {
         Field.toTab(); 
       }
       break;
     case 4:
       Field.plusMenuState();
       break;
    }
  }
  else if (Field.getGameTrigger()) {
    switch (buttonNumber){
     case 2:
       Field.createShell(Player.getX());
       break;
     case 3:
       Player.moveRight();
       break;
     case 4:
       Field.toMenu();
       t = true;
       break;
     case 5:
       Player.moveLeft();
       break;
    }
  }
  else if (Field.getLoseTrigger()) {
    switch (buttonNumber){
     case 2:
       Field.minusName(Field.getLoseState());
       break;
     case 3:
       if ((Field.getLoseState() == 0) || (Field.getLoseState() == 1)) {
         Field.plusLoseState();
       }
       else if (Field.getLoseState() == 2) {
         Field.writeTab();
         Field.toMenu();
         Field.saveTab();
       }
       break;
     case 4:
       Field.plusName(Field.getLoseState());
       break;
     case 5:
       if ((Field.getLoseState() == 1) || (Field.getLoseState() == 2)) {
         Field.minusLoseState();
       }
       break;
    }
  }
  else if (Field.getTabTrigger()) {
    switch (buttonNumber){
      case 5:
        Field.reset();
        break;
      default:
        Field.toMenu();
        break;
    }
  }
}
//смотрим состояние игры - рисуем соответсвующие элементы
void output() {
  if (Field.getMenuTrigger()) {
    LCD.clrScr();
    LCD.print("NEW GAME", LEFT + 8, 0);
    LCD.print("CONTINUE", LEFT + 8, 8);
    LCD.print("DIFFICULTY", LEFT + 8, 16);
    LCD.printNumI(Field.getDifficulty(), RIGHT, 16);
    LCD.print("SIZE", LEFT + 8, 24);
    LCD.printNumI(Field.getSizeField(), RIGHT, 24);
    LCD.print("HIGHCORES", LEFT + 8, 32);
    LCD.drawRect(0, 8 * Field.getMenuState(), 7, 8 * Field.getMenuState() + 6);
    LCD.update();
  }
  else if (Field.getGameTrigger()) {
    sizeField = Field.getSizeField();
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
  else if (Field.getLoseTrigger()) {
    LCD.clrScr();
    LCD.print("GAME OVER", CENTER, 0);
    LCD.print("POINTS", CENTER, 8);
    LCD.printNumI(Field.getPoints(), CENTER, 16);
    LCD.print(String(Field.getName(0)) + String(Field.getName(1)) + String(Field.getName(2)), CENTER, 24);
    LCD.drawLine(34 + Field.getLoseState() * 6, 32, 39 + Field.getLoseState() * 6, 32);
    LCD.update();
  }
  else if (Field.getTabTrigger()) {
    LCD.clrScr();
    LCD.print("HIGHCORES", CENTER, 0);
    for (int i = 0; i < 5; i++) {
      LCD.print(String(Field.getTabName1(i)) + String(Field.getTabName2(i)) + String(Field.getTabName3(i)), LEFT, (i + 1) * 8);
      LCD.printNumI(Field.getTabPoints(i), RIGHT, (i + 1) * 8);
    }
    LCD.update();
  }
}
