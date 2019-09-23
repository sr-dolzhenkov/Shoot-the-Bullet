#include <iostream>
#include <conio.h>
#include "Plane.h"
#include "Shell.h"
#include "Row.h"
#include "Reader.h"
// для поля 36x48
//блок 4x4
using namespace std;

int main() {

	char buttom;

	while (true) {
		if (kbhit()) {
			buttom = getch();
		}

	}
	system("pause");
	return 0;
}