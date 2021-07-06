#include <stdio.h>
#include<graphics.h>
#include<iostream>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")
using namespace std;
#define SNAKE_NUM 500
struct Snake {
	int size;
	int dir;//蛇的方向
	int speed;
	POINT coor[SNAKE_NUM];

}snake;
struct Food {
	int x;
	int y;
	int r;
	bool flag;
	DWORD color;
}food;
enum DIR {
	 UP,DOWN,LEFT,RIGHT 
};
// 图形窗口
void GameInit() {
	mciSendString("open ./bgMusic.mp3 alias BGM", 0, 0, 0);
	mciSendString("play BGM repeat", 0, 0, 0);
	initgraph(640, 480, SHOWCONSOLE);
	//GetTickCount  获取系统开机到现在的毫秒数
	srand(GetTickCount());
	snake.size = 3;
	snake.speed = 10;
	snake.dir;
	for (int i = snake.size - 1; i >= 0; i--) {
		snake.coor[i].x = 10*(snake.size - i)+20;
		snake.coor[i].y = 10;
		//printf("s%d,%d", snake.coor[i].x, snake.coor[i].y);
	}
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 255, rand() % 255, rand() % 255);
	food.r = rand() % 10 + 5;
	food.flag = true;
}
void GameDraw() {
	BeginBatchDraw();
	setbkcolor(RGB(28, 115, 119));
	cleardevice();
	setfillcolor(RED);
	for (int i = 0; i < snake.size; i++) {
		solidcircle(snake.coor[i].x, snake.coor[i].y, 5);
	}
	if (food.flag) {
		solidcircle(food.x, food.y, food.r);
	}
	EndBatchDraw();
}
void snakeMove() {
	for (int i = snake.size - 1; i > 0; i--) {
		snake.coor[i] = snake.coor[i - 1];
	}
	switch (snake.dir) {
	case UP:
		snake.coor[0].y -= snake.speed;
		if (snake.coor[0].y <= 10) {
			snake.coor[0].y = 480;
		}
		break;
	case DOWN:
		snake.coor[0].y += snake.speed;
		if (snake.coor[0].y >= 480) {
			snake.coor[0].y = 10;
		}
		break;
	case LEFT:
		snake.coor[0].x -= snake.speed;
		if (snake.coor[0].x <= 10) {
			snake.coor[0].x = 640;
		}
		break;
	case RIGHT:
		snake.coor[0].x += snake.speed;
		if (snake.coor[0].x >= 640) {
			snake.coor[0].x = 10;
		}
		break;
	}
}
void keyControl() {
	//键盘方向键 72 75 77  80
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
		case 'W':
		case 72:
			if (snake.dir != DOWN) {
				snake.dir = UP;
			}
			
			break;
		case 'a':
		case 'A':
		case 75:
			if (snake.dir != RIGHT) {
				snake.dir = LEFT;
			}
			break;
		case 'S':
		case 's':
		case 80:
			if (snake.dir != UP) {
				snake.dir = DOWN;
			}
			break;
		case 'd':
		case 'D':
		case 77:
			if (snake.dir != LEFT) {
				snake.dir = RIGHT;
			}
			break;
		case ' ':
			while (1) {
				if (_getch() == ' ') {
					return;
				}
			}

		}
	}
	
}
void earFood() {
	//if (food.flag && sqrt((snake.coor[0].x - food.x) ^ 2 + (snake.coor[0].y - food.y) ^ 2) <= food.r + 5) {
	if (food.flag && snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r &&
		snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r) {
		food.flag = false;
		snake.size++;
	}
	if (!food.flag) {
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 255, rand() % 255, rand() % 255);
		food.r = rand() % 10 + 5;
		food.flag = true;
	}
}

int main() {
	//init 初始化 图像窗口
	GameInit();
	while (1) {
		
		snakeMove();
		GameDraw();
		keyControl();
		earFood();
		Sleep(200);
	}
	
	return 0;

}