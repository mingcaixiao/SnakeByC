//view.cpp

#include"view.h"
#include"control.h"

void CreateMap()//创建地图
{
	int i;
	for (i = 0; i<58; i += 2)//打印左右边框
	{
		PrintDia(i, 0);
		PrintDia(i, 26);
	}
	for (i = 1; i<26; i++)//打印上下边框
	{
		PrintDia(0, i);
		PrintDia(56, i);
	}
}


//打印方块
void PrintDia(int x,int y)
{
	Pos(x, y);
	printf("■");
}



void WelcomeToGame()//开始界面
{
	Pos(40, 12);
	printf("欢迎来到贪食蛇游戏！");
	Pos(40, 25);
	system("Pause");
	system("cls");
}

void EndGame()//结束游戏
{

	system("cls");
	Pos(24, 12);
	if (g_EndGameStatus == 1)
	{
		printf("对不起，您撞到墙了。游戏结束.");
	}
	else if (g_EndGameStatus == 2)
	{
		printf("对不起，您咬到自己了。游戏结束.");
		system("pause");
	}
	else if (g_EndGameStatus == 3)
	{
		printf("您的已经结束了游戏。");
		system("pause");
	}
	Pos(24, 13);
	printf("您的得分是%d\n", g_nScore);
	exit(0);
}

void GameInfo()
{
	Pos(64, 15);
	printf("不能穿墙，不能咬到自己\n");
	Pos(64, 16);
	printf("用A,W,S,D分别控制蛇的移动.");
	Pos(64, 18);
	printf("Q:退出游戏且存档.：P:暂停或恢复游戏.");
	Pos(64, 20);
	printf("G：读档");
}

void SelectLevel()//选择难度
{
	int i, lev;
	for (i = 0; i < 10; i++)
		printf(" ");
	for (i = 0; i < 50; i++)
		printf("*");
	printf("\n");
	for (i = 0; i < 10; i++)
		printf(" ");
	printf("*");
	for (i = 0; i < 48; i++)
		printf(" ");
	printf("*");
	printf("\n");
	for (i = 0; i < 10; i++)
		printf(" ");
	printf("*");
	printf("     请选择难度!                                *\n");
	for (i = 0; i < 10; i++)
		printf(" ");
	printf("*");
	printf("     1:简单  2:普通  3:困难                     *\n");
	for (i = 0; i < 10; i++)
		printf(" ");
	printf("*");
	for (i = 0; i < 48; i++)
		printf(" ");
	printf("*");
	printf("\n");
	for (i = 0; i < 10; i++)
		printf(" ");
	for (i = 0; i < 50; i++)
		printf("*");
	printf("\n");
	printf("Please select:");
	scanf_s("%d", &lev);
	switch (lev)
	{
	case 1: g_nSleepTime = 200; break;
	case 2: g_nSleepTime = 125; break;
	case 3: g_nSleepTime = 50; break;
	default: break;
	}
	system("cls");
}
