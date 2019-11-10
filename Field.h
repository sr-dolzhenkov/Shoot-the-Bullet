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

  const int getDataShellsX(int _i);
  const int getDataShellsY(int _i);
  const bool getDataRows(int _x, int _y);
  const int getPoints();
  const bool getLoseTrigger();

private:
  const static int width = 13;
  const static int height = 20;

  int dataShells[height - 2][2];//массив содежащий координаты снарядов(x в первом столбике, y во втором)
  bool dataRows[height - 2][width - 2];//массив содежащий информацию о рядах

  int points;//очки ирока

  bool loseTrigger;//состояние игры
};
