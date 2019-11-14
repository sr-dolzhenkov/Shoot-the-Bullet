#pragma once

class Field {
public:
  Field();
  ~Field();
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
  void rewriteRows(int _y);
  void toMenu();
  void minusMenuState();
  void plusMenuState();
  void toGame();
  void plusSizeField();
  void plusDifficulty();
  void plusLoseState();
  void plusName(int i);
  void minusName(int i);

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

private:
  const static int width = 13;
  const static int height = 20;

  int dataShells[height - 2][2];//массив содежащий координаты снарядов(x в первом столбике, y во втором)#pragma once

class Field {
public:
  Field();
  ~Field();
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
  void rewriteRows(int _y);
  void toMenu();
  void minusMenuState();
  void plusMenuState();
  void toGame();
  void plusSizeField();
  void plusDifficulty();
  void plusLoseState();
  void plusName(int i);
  void minusName(int i);
  void toTab();
  void writeTab();
  void rewriteTab(int pos);
  void minusLoseState();
  void saveTab();
  void reset();

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

  bool loseTrigger;//состояние игры
  bool menuTrigger;
  bool gameTrigger;
  bool tabTrigger;
  bool gameState;

  int sizeField;
  int difficulty;

  int menuState;
  int loseState;

  char Name[3];
  
  char tabName[5][3];
  int tabPoints[5];

  bool t;
};

  bool dataRows[height - 2][width - 2];//массив содежащий информацию о рядах

  int points;//очки ирока

  bool loseTrigger;//состояние игры
  bool menuTrigger;
  bool gameTrigger;
  bool tabTrigger;
  bool gameState;

  int sizeField;
  int difficulty;

  int menuState;
  int loseState;

  char Name[3];
};
