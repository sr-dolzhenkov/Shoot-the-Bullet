# Shoot-the-bullet
Проек повторяет игру Shoot-the-bullet (https://www.microsoft.com/en-us/p/brick-game-simulator/9nblggh4qfmw).
Реализован в 5 файлах: "Shoot-the-bullet.ino", "Field.cpp", "Field.h", "playerShip.cpp", "playerShip.h".
В "Shoot-the-bullet.ino" подключены небходимая библиотека(LCD5110_Graph.h), файлы(Field.h, playerShip.h), перефирия(LCD5110, JoystickShield), созданы объекты классов и методы считывания(input) и вывода(output) информации.
  В "setup()" открыты нужные выходы и входы.
  В "loop()" реализована основная логика программы.
  В "input()" в зависимости от нажатой кнопки на JoystickShield производим соответсвующие дествия.
  В "output()" в зависимости от состояния игры выводим соотвествующие элименты на LCD5110.
В "Field.cpp" и "Field.h" реализованы методы и функции для описания поля, падающих рядов и летящих снарядов, а также их взаиможействия между собой.
В "playerShip.cpp" и "playerShip.h" реализованы методы и функции для описания модели игрока и управления ею.
