//Snake.cpp

#include"control.h"
#include"view.h"
#include<stdio.h>
#include<time.h>
#include<windows.h>
#include<conio.h>

int main()
{
	//初始化游戏
	system("mode con cols=100 lines=30");
	WelcomeToGame();
	SelectLevel();
	CreateMap();
	InitSnake();
	CreateFood();

	GameInfo();
	g_nStatus = R;
	while (1)
	{
		char chInput=0;
		Pos(64, 10);
		printf("得分：%d ", g_nScore);
		Pos(64, 11);
		printf("每个食物得分：%d分", g_nAdd);
		if (_kbhit() != 0)
		{
			chInput = _getch();
		}
		switch(chInput)
		{
		case'a':
			if (g_nStatus != R)
			{
				g_nStatus = L;
			}
			break;
		case'w':
			if (g_nStatus != D)
			{
				g_nStatus = U;
			}
			break;
		case's':
			if (g_nStatus != U)
			{
				g_nStatus = D;
			}
			break;
		case'd':
			if (g_nStatus != L)
			{
				g_nStatus = R;
			}
			break;
		case'q':
			SaveGame();
			g_EndGameStatus = 3;
			break;
		case'p':
			Pause();
			break;
		case'g':
			system("cls");
			LoadGame();
			CreateMap();
			PrintDia(g_pFood->x, g_pFood->y);
			GameInfo();
			break;
		}
		Sleep(g_nSleepTime);
		SnakeMove();
		if (g_EndGameStatus == 3)
		{
			break;
		}
	}
	EndGame();
	return 0;
}
