//control.cpp

#include "control.h"
#include "view.h"
#include <stdio.h>
#include<conio.h>

//全局变量//
int g_nScore = 0, g_nAdd = 10;//总得分与每次吃食物得分。
int g_nStatus, g_nSleepTime = 200;//每次运行的时间间隔
tagSnake *g_pHead , *g_pFood;//蛇头指针，食物指针

int g_EndGameStatus = 0; //游戏结束的情况，1：撞到墙；2：咬到自己；3：主动退出游戏。



void Pos(int x, int y)//设置光标位置
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

int BiteSelf()//判断是否咬到了自己
{
	tagSnake *pSelf;
	pSelf = g_pHead->next;
	while (pSelf != NULL)
	{
		if (pSelf->x == g_pHead->x && pSelf->y == g_pHead->y)
		{
			return 1;
		}
		pSelf = pSelf->next;
	}
	return 0;
}


void IsCanCrossWall()//不能穿墙
{
	if (g_pHead->x == 0 || g_pHead->x == 56 || g_pHead->y == 0 || g_pHead->y == 26)
	{
		g_EndGameStatus = 1;
		EndGame();
	}
}


void Pause()//暂停
{
	while (1)
	{
		Sleep(300);
		if (_getch() == 'p')
		{
			break;
		}

	}
}

//向上
void Up()
{
	tagSnake * pNext;
	IsCanCrossWall();
	pNext = (tagSnake*)malloc(sizeof(tagSnake));
	pNext->x = g_pHead->x;
	pNext->y = g_pHead->y - 1;
	IsHaveFood(pNext);
	
}
void Down()//向下
{
	tagSnake * pNext;
	IsCanCrossWall();
	pNext = (tagSnake*)malloc(sizeof(tagSnake));
	pNext->x = g_pHead->x;
	pNext->y = g_pHead->y + 1;
	IsHaveFood(pNext);
}

void Left()//向左
{
	tagSnake * pNext;
	IsCanCrossWall();
	pNext = (tagSnake*)malloc(sizeof(tagSnake));
	pNext->x = g_pHead->x - 2;
	pNext->y = g_pHead->y;
	IsHaveFood(pNext);
	
}

void Right()//向右
{
	tagSnake * pNext;
	IsCanCrossWall();
	pNext = (tagSnake*)malloc(sizeof(tagSnake));
	pNext->x = g_pHead->x + 2;
	pNext->y = g_pHead->y;
	IsHaveFood(pNext);
}

void IsHaveFood(tagSnake *pNext)//判断是否吃到食物
{
	if (pNext->x == g_pFood->x && pNext->y == g_pFood->y)//吃到食物
	{
		tagSnake *pTra=g_pHead;
		pNext->next = g_pHead;
		g_pHead = pNext;
		while (pTra != NULL)
		{
			PrintDia(pTra->x, pTra->y);
			pTra = pTra->next;
		}
		g_nScore +=g_nAdd;
		CreateFood();
	}
	else //没有吃到食物
	{
		tagSnake *pTra;
		pNext->next = g_pHead;
		g_pHead = pNext;
		pTra = g_pHead;
		while (pTra!= NULL)
		{
			PrintDia(pTra->x, pTra->y);
			if (pTra->next == NULL)
			{
				break;
			}
			else if (pTra->next->next == NULL)
			{
				break;
			}
			pTra = pTra->next;
		}
		Pos(pTra->next->x, pTra->next->y);
		printf(" ");
		free(pTra->next);
		pTra->next = NULL;
	}
}
void SnakeMove()//蛇前进,上U,下D,左L,右R
{
	
	switch (g_nStatus)
	{
	case U:
		Up();
		break;
	case R:
		Right();
		break;
	case L:
		Left();
		break;
	case D:
		Down();
		break;		
	}
	if (BiteSelf() == 1) //判断是否会咬到自己
	{
		g_EndGameStatus = 2;
		EndGame();
	}
}



void CreateFood()//随机出现食物
{
	srand((unsigned)time(NULL));
	tagSnake *pFood1,*pTra;
	pFood1 = (tagSnake*)malloc(sizeof(tagSnake));
	while ((pFood1->x % 2) != 0) //保证其为偶数，使得食物能与蛇头对齐
	{
		pFood1->x = rand() % 52 + 2;
	}
	pFood1->y = rand() % 24 + 1;
	pTra = g_pHead;
	while (pTra->next!= NULL)
	{
		if (pTra->x == pFood1->x && pTra->y == pFood1->y) //判断蛇身是否与食物重合
		{
			free(pFood1);
			CreateFood();
		}
		pTra = pTra->next;
	}
	PrintDia(pFood1->x, pFood1->y);
	g_pFood = pFood1;
}

void InitSnake()//初始化蛇身
{
	g_pHead=(tagSnake*)malloc(sizeof(tagSnake));
	g_pHead->next = NULL;
	g_pHead->x = 24;
	g_pHead->y = 5;
	PrintDia(g_pHead->x, g_pHead->y);
}

//存档
void SaveGame()
{
	tagSnake *pTra = g_pHead;
	FILE *pFile = fopen("data.txt","wb");

	//写蛇的长度
	int nCount = g_nScore / 10 + 1;
	fwrite(&nCount, 4, 1, pFile);
	
	//写蛇身链表
	for (int i = 0; i < nCount; i++)
	{
		fwrite(&pTra->x, 4, 1, pFile);
		fwrite(&pTra->y, 4, 1, pFile);
		pTra = pTra->next;
	}
	//写食物
	fwrite(&g_pFood->x, 4, 1, pFile);
	fwrite(&g_pFood->y, 4, 1, pFile);
	//写状态
	fwrite(&g_nStatus, 4, 1, pFile);
	//写分数
	fwrite(&g_nScore, 4, 1, pFile);
	fclose(pFile);
}

//读档
void LoadGame()
{
	tagSnake *pTail=g_pHead;

	FILE *pFile = fopen("data.txt", "rb");
	
	int nCount = 0;
	//读长度
	fread(&nCount, 4, 1, pFile);

	//读蛇身
	for (int i = 0; i < nCount; i++)
	{
		tagSnake* pNewNode = (tagSnake*)malloc(sizeof(tagSnake));
		fread(&pNewNode->x, 4, 1, pFile);
		fread(&pNewNode->y, 4, 1, pFile);
		

		if (i==0)//尾插法恢复蛇身
		{
			g_pHead = pNewNode;
			pTail = g_pHead;
		}
		else
		{
			pTail->next = pNewNode;
			pTail = pNewNode;
		}
		pTail->next = NULL;
	}
	
	//读食物
	fread(&g_pFood->x, 4, 1, pFile);
	fread(&g_pFood->y, 4, 1, pFile);

    //读状态
	fread(&g_nStatus, 4, 1, pFile);

	//读分数
	fread(&g_nScore, 4, 1, pFile);
}
