#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include "string.h"

#include "Field.h"
#include "playerShip.h"

#define UP_PIN 2
#define RIGHT_PIN 3
#define DOWN_PIN 4
#define LEFT_PIN 5

Adafruit_PCD8544 display = Adafruit_PCD8544(9, 10, 11, 12, 13);

playerShip Player;
Field Field;

void input(int buttonNumber);
void output();

const int width = 13;
const int height = 20;

int sizeField;
bool t = false;
int mil;

void setup() {
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);  
  
  pinMode(UP_PIN, INPUT_PULLUP);
  digitalWrite(UP_PIN, HIGH);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  digitalWrite(RIGHT_PIN, HIGH);
  pinMode(DOWN_PIN, INPUT_PULLUP);
  digitalWrite(DOWN_PIN, HIGH);
  pinMode(LEFT_PIN, INPUT_PULLUP);
  digitalWrite(LEFT_PIN, HIGH);

  display.begin();
  display.setContrast(50);
  display.setTextColor(BLACK);
  display.setTextSize(1);

  Serial.begin(115200);
}


void loop() {
//в соответсвии с состоянием игры вызываем методы для функционирования программы
  if (Field.getMenuTrigger()) {
    delay(200);
    for (int i = 2; i < 6; i++) {
      if (digitalRead(i) == LOW) {
        input(i);
        delay(200);
      }
    }
    output();
  }
  //раз в 0.2 с. вызываем метод полёта снарядов 50 - уровень ложности * 5 раз
  //потом вызываем метод падения срок, условия с t нужно для корректного выхода в меню во время игры
  else if (Field.getGameTrigger()) {
    for (int h = 0; h < 50 - Field.getDifficulty() * 5; h++) {
      output();
      for (int i = 2; i < 6; i++) {
        if (digitalRead(i) == LOW) {
          input(i);
          if (t) {
            break;
          }
        }
      }
      if (t) {
        break;
      }
      delay(200);
      Field.flightShells();
    }
    if (!t) {
      Field.fallingRow();
    }
    else {
      t = false;
    }
  }
  //поражение
  else if (Field.getLoseTrigger()) {
    delay(200);
    for (int i = 2; i < 6; i++) {
      if (digitalRead(i) == LOW) {
        input(i);
      }
    }
    output();
    delay(50);
  }
  //таблица рекордов
  else if (Field.getTabTrigger()) {
    delay(200);
    for (int i = 2; i < 6; i++) {
      if (digitalRead(i) == LOW) {
        input(i);
      }
    }
    output();
    delay(50);
  }
}
//смотрим состояние игры - ативируем соотвествующие кнопки
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
     case 5:
       Field.createShell(Player.getX());
       break;
     case 2:
       Player.moveRight();
       break;
     case 3:
       Field.toMenu();
       t = true;
       break;
     case 4:
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
    display.setRotation(0);
    display.clearDisplay();
    display.setCursor(8,0);
    display.println("NEW GAME");
    display.setCursor(8,8);
    display.println("CONTINUE");
    display.setCursor(8,16);
    display.println("DIFFICULTY");
    display.setCursor(76,16);
    display.println(Field.getDifficulty());
    display.setCursor(8,24);
    display.println("SIZE");
    display.setCursor(76,24);
    display.println(Field.getSizeField());
    display.setCursor(8,32);
    display.println("HIGHCORES");
    display.drawRect(0, 8 * Field.getMenuState(), 7, 7, BLACK);
    display.display();
  }
  else if (Field.getGameTrigger()) {
    display.setRotation(1);
    sizeField = Field.getSizeField();
    display.clearDisplay();
    display.drawRect(0, 0, 11 * sizeField + 2, 18 * sizeField + 2, BLACK);
    display.fillRect(Player.getX() * sizeField + 1, Player.getY() * sizeField + 1, sizeField, sizeField, BLACK);
    for (int i = 0; i < height - 2; i++) {
      for (int j = 0; j < width - 2; j++) {
        if (Field.getDataRows(i, j)) {
          display.drawRect(j * sizeField + 1, i * sizeField + 1, sizeField, sizeField, BLACK);
        }
      }
    }
    for (int i = 0; i < height - 2; i++) {
      if (Field.getDataShellsX(i) != -1) {
        display.drawRect(Field.getDataShellsX(i) * sizeField + 1, Field.getDataShellsY(i) * sizeField + 1, sizeField, sizeField, BLACK);
      }
    }

    display.setCursor(36,0);
    display.println("PT");
    display.setCursor(36,8);
    display.println(Field.getPoints());
    display.display();
  }
  else if (Field.getLoseTrigger()) {
    display.setRotation(0);
    display.clearDisplay();
    display.setCursor(0,0);
    display.println("GAME OVER");
    display.setCursor(0,8);
    display.println("POINTS");
    display.setCursor(0,16);
    display.println(Field.getPoints());
    display.setCursor(0,24);
    display.println(String(Field.getName(0)) + String(Field.getName(1)) + String(Field.getName(2)));
    display.drawLine(Field.getLoseState() * 6, 32, 4 + Field.getLoseState() * 6, 32, BLACK);
    display.display();
  }
  else if (Field.getTabTrigger()) {
    display.setRotation(0);
    display.clearDisplay();
    display.setCursor(14,0);
    display.println("HIGHCORES");
    for (int i = 0; i < 5; i++) {
      display.setCursor(0,(i + 1) * 8);
      display.println(String(Field.getTabName1(i)) + String(Field.getTabName2(i)) + String(Field.getTabName3(i)));
      display.setCursor(60,(i + 1) * 8);
      display.println(Field.getTabPoints(i));
    }
    display.display();
  }
}
