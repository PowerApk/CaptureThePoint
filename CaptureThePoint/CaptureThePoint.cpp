#include "stdafx.h"
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <stdio.h>
#include <vector>
#include <time.h>

using namespace std;

#define ARRIBA     72   
#define IZQUIERDA  75
#define DERECHA    77
#define ABAJO      80
#define ESC        27
#define ENTER      13

#define ROWS		20
#define COLS		40

char tecla;
int x, y;
int xPoint, yPoint;
int dir = 0;
int backcolor = 0;
int countZero = 0;
int score = 0;

class Coordenada {

private:
	int coordY;
	int coordX;
public:
	Coordenada(int y, int x) {
		coordY = y;
		coordX = x;
	}
	int getY() {
		return coordY;
	}
	int getX() {
		return coordX;
	}
};

vector< Coordenada > pointSpace;
int mapa[ROWS][COLS] = {
	{ 1,6,6,6,6,6,6,6,2,1,6,6,6,6,6,6,6,6,1,6,6,2,6,6,6,6,6,6,2,6,6,6,6,6,6,6,6,6,6,2 },
	{ 5,0,0,0,0,0,0,0,3,4,0,0,0,0,0,0,0,0,3,6,6,4,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,5 },
	{ 5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,6,6,0,0,0,0,0,0,0,0,5 },
	{ 5,0,0,0,0,0,0,0,1,2,0,0,0,0,0,0,0,0,1,6,6,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5 },
	{ 5,0,1,6,6,6,6,6,3,4,6,6,6,6,6,6,6,6,3,6,6,4,6,6,6,6,1,2,0,0,1,6,6,6,6,6,6,2,0,5 },
	{ 5,0,5,9,9,9,9,9,1,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,5,3,2,1,3,6,6,6,6,6,6,4,0,5 },
	{ 5,0,3,6,6,6,6,6,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,3,4,0,0,0,0,0,0,0,5,0,5 },
	{ 5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,5,0,5 },
	{ 5,0,0,0,0,0,0,0,1,2,0,0,0,0,0,0,0,0,5,0,6,2,0,0,0,0,0,0,1,2,0,0,0,0,0,0,0,5,0,5 },
	{ 5,6,6,6,6,6,6,6,4,3,6,6,6,6,6,6,6,6,5,0,0,5,6,6,6,6,6,6,4,3,6,6,6,6,6,6,6,2,0,5 },
	{ 5,6,6,6,6,6,6,6,2,1,6,6,6,6,6,6,6,6,5,0,6,4,6,6,6,6,6,6,2,1,6,6,6,6,6,6,6,4,0,5 },
	{ 5,0,0,0,0,0,0,0,3,4,0,0,0,0,0,0,0,0,5,0,0,5,0,0,0,0,0,0,3,4,0,0,0,0,0,0,0,5,0,5 },
	{ 5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,5 },
	{ 5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,6,6,2,0,0,0,0,0,0,1,2,0,0,0,0,0,0,0,5,0,5 },
	{ 3,6,6,6,6,6,6,6,2,0,1,6,6,6,6,6,6,6,3,6,6,4,6,6,6,6,6,6,4,3,6,6,6,6,6,6,6,2,0,5 },
	{ 1,6,6,6,6,6,6,6,4,0,3,6,6,6,6,6,6,6,6,2,1,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,4,0,5 },
	{ 5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5 },
	{ 5,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5 },
	{ 5,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,2,0,0,0,0,0,0,0,0,0,5 },
	{ 3,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,4,3,6,6,6,6,6,6,6,6,6,4 }
};

void setCColor(int color) {
	static HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color | (backcolor * 0x10 + 0x100));
}

void gotoxy(int x, int y)
{
	HANDLE hCon;
	COORD dwPos;

	dwPos.X = x;
	dwPos.Y = y;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hCon, dwPos);
}

void drawMap() {
	for (int j = 0; j < ROWS; j++) {
		for (int i = 0; i < COLS; i++) {
			gotoxy(i, j);
			if (mapa[j][i] == 1) { printf("%c", 201); }
			if (mapa[j][i] == 2) { printf("%c", 187); }
			if (mapa[j][i] == 3) { printf("%c", 200); }
			if (mapa[j][i] == 4) { printf("%c", 188); }
			if (mapa[j][i] == 5) { printf("%c", 186); }
			if (mapa[j][i] == 6) { printf("%c", 205); }
			if (mapa[j][i] == 0) {
				countZero++;
				pointSpace.push_back(Coordenada(j, i));
			}
		}
	}
}

void move() {
	tecla = _getch();
	switch (tecla) {
	case ARRIBA:
		dir = 1;
		if (mapa[y - 1][x] == 0) {
			gotoxy(x, y);
			printf(" ");
			gotoxy(x, y - 1);
			printf("X");
			y -= 1;
		}
		break;
	case ABAJO:
		dir = 2;
		if (mapa[y + 1][x] == 0) {
			gotoxy(x, y);
			printf(" ");
			gotoxy(x, y + 1);
			printf("X");
			y += 1;
		}
		break;
	case DERECHA:
		dir = 3;
		if (mapa[y][x + 1] == 0) {
			gotoxy(x, y);
			printf(" ");
			gotoxy(x + 1, y);
			printf("X");
			x += 1;
		}
		break;
	case IZQUIERDA:
		dir = 4;
		if (mapa[y][x - 1] == 0) {
			gotoxy(x, y);
			printf(" ");
			gotoxy(x - 1, y);
			printf("X");
			x -= 1;
		}
		break;
	}
}

void drawPoint() {
	int positionPoint = rand() % (pointSpace.size());
	gotoxy(5, 22);
	printf("Count de 0: %d", countZero);
	gotoxy(5, 23);
	printf("Count de random: %d", positionPoint);
	gotoxy(pointSpace[positionPoint].getX(), pointSpace[positionPoint].getY());
	printf("*");
	xPoint = pointSpace[positionPoint].getX();
	yPoint = pointSpace[positionPoint].getY();
}

void checkPoint() {
	if (x == xPoint && y == yPoint) {
		drawPoint();
		score += 100;
	}
	gotoxy(30, 22);
	printf("Actual x: %d", x);
	gotoxy(30, 23);
	printf("Actual y: %d", y);
	gotoxy(30, 24);
	printf("Actual x: %d", xPoint);
	gotoxy(30, 25);
	printf("Actual y: %d", yPoint);
}

int main() {
	setCColor(0x00C);
	drawMap();
	drawPoint();
	x = 2;
	y = 2;
	srand(time(0));
	gotoxy(x, y);
	printf("x");
	while (true) {
		move();
		checkPoint();
		gotoxy(5, 26);
		printf("Score: %d", score);
	}
	return 0;
}