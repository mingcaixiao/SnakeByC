//view.cpp

#include"view.h"
#include"control.h"

void CreateMap()//������ͼ
{
	int i;
	for (i = 0; i<58; i += 2)//��ӡ���ұ߿�
	{
		PrintDia(i, 0);
		PrintDia(i, 26);
	}
	for (i = 1; i<26; i++)//��ӡ���±߿�
	{
		PrintDia(0, i);
		PrintDia(56, i);
	}
}


//��ӡ����
void PrintDia(int x,int y)
{
	Pos(x, y);
	printf("��");
}



void WelcomeToGame()//��ʼ����
{
	Pos(40, 12);
	printf("��ӭ����̰ʳ����Ϸ��");
	Pos(40, 25);
	system("Pause");
	system("cls");
}

void EndGame()//������Ϸ
{

	system("cls");
	Pos(24, 12);
	if (g_EndGameStatus == 1)
	{
		printf("�Բ�����ײ��ǽ�ˡ���Ϸ����.");
	}
	else if (g_EndGameStatus == 2)
	{
		printf("�Բ�����ҧ���Լ��ˡ���Ϸ����.");
		system("pause");
	}
	else if (g_EndGameStatus == 3)
	{
		printf("�����Ѿ���������Ϸ��");
		system("pause");
	}
	Pos(24, 13);
	printf("���ĵ÷���%d\n", g_nScore);
	exit(0);
}

void GameInfo()
{
	Pos(64, 15);
	printf("���ܴ�ǽ������ҧ���Լ�\n");
	Pos(64, 16);
	printf("��A,W,S,D�ֱ�����ߵ��ƶ�.");
	Pos(64, 18);
	printf("Q:�˳���Ϸ�Ҵ浵.��P:��ͣ��ָ���Ϸ.");
	Pos(64, 20);
	printf("G������");
}

void SelectLevel()//ѡ���Ѷ�
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
	printf("     ��ѡ���Ѷ�!                                *\n");
	for (i = 0; i < 10; i++)
		printf(" ");
	printf("*");
	printf("     1:��  2:��ͨ  3:����                     *\n");
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
