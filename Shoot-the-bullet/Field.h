#pragma once

class Field {
public:
  Field();
  ~Field();
  //методы логики игры и взаимодествия с меню
  void createShell(int _x);//создаём снаряд
  void deleteShell(int pos);//удляем снаряд
  void createRow();//генерируем неполный ряд
  void fallingRow();//логика падения радов
  void deleteRow(int _y);//очищаем строку
  bool checkCollision(int _x, int _y);//проверяем не столкнулся ли снаряд со строкой
  void flightShells();//логика полёта снарядов
  void changeRow(int _x, int _y);//заполняем соответствующую позицию в ряде
  bool checkRow(int _y);//проверяем не полный ли ряд
  bool checkLose();//проверяе не дошли ли строка до игрока
  void lose();//меняем состояние игры на проигрышь
  void newGame();//перемещаем все элименты в начальное состояние
  void rewriteRows(int _y);//довляем в строку блок на _y позиции
  void toMenu();//переход вменю, меняем состояния игры
  void minusMenuState();//перемщение курсора в меню вверх
  void plusMenuState();//перемещение курсора в меню вниз
  void toGame();//переход в игру, меняем состояния игры
  void plusSizeField();//изменение размера поля
  void plusDifficulty();//изменение сложности игры
  void plusLoseState();//перемещение курсора в окне проигрыша вправо
  void plusName(int i);//изменеие буквы в имени игрока вниз по алфавиту
  void minusName(int i);//изменение буквы в имени игрока вверх по алфавиту
  void toTab();//пеход к таблице результатов, меняем состояния игры
  void writeTab();//записываем результат в таблицу
  void rewriteTab(int pos);//перезаписываем результаты в таблице на уровень ниже начиная с pos строки
  void minusLoseState();//перемещение курсора в окне проигрыша влево
  void saveTab();//сохранение таблици в память
  void reset();//сброс результатов таблици на изначальные
  void saveDifficulty();//сохранение сложности в память
  void saveSize();//сохранение размера в память
  //методы для получение данных объекта
  const int getDataShellsX(int _i);
  const int getDataShellsY(int _i);
  const bool getDataRows(int _x, int _y);
  const int getPoints();
  const bool getLoseTrigger();
  const bool getMenuTrigger();
  const bool getGameTrigger();
  const bool getTabTrigger();
  const int getSizeField();
  const int getDifficulty();
  const int getMenuState();
  const bool getGameState();
  const int getLoseState();
  const char getName(int i);
  const char getTabName1(int i);
  const char getTabName2(int i);
  const char getTabName3(int i);
  const int getTabPoints(int i);

private:
  const static int width = 13;
  const static int height = 20;

  int dataShells[height - 2][2];//массив содежащий координаты снарядов(x в первом столбике, y во втором)
  bool dataRows[height - 2][width - 2];//массив содежащий информацию о рядах

  int points;//очки ирока
  //состояния игры
  bool loseTrigger;
  bool menuTrigger;
  bool gameTrigger;
  bool tabTrigger;
  bool gameState;
  
  int sizeField;
  int difficulty;
  //состояние курсора в меню и окне проигрыша
  int menuState;
  int loseState;

  char Name[3];
  
  char tabName[5][3];
  int tabPoints[5];

  bool t;
  bool t1;
};
