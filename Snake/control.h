//control.h

#pragma once
#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<stdlib.h>



#define U 1
#define D 2
#define L 3 
#define R 4 //蛇的状态，U：上 ；D：下；L:左 R：右

struct tagSnake//蛇身的一个节点
{
	int x;
	int y;
	struct tagSnake *next;
};

extern int g_nScore, g_nAdd;
extern int g_nStatus, g_nSleepTime;
extern tagSnake *g_pHead, *g_pFood;
//extern tagSnake *pTra;
extern int g_EndGameStatus; 

void Pos(int x, int y);

int BiteSelf();

void CreateFood();

void IsCanCrossWall();

void SnakeMove();

void Pause();

void Up();

void Down();

void Left();

void Right();

void IsHaveFood(tagSnake *pNext);

void CreateFood();

void GameStart();

void SaveGame();

void LoadGame();

void InitSnake();

