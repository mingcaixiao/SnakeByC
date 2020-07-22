//control.cpp

#include "control.h"
#include "view.h"
#include <stdio.h>
#include<conio.h>

//ȫ�ֱ���//
int g_nScore = 0, g_nAdd = 10;//�ܵ÷���ÿ�γ�ʳ��÷֡�
int g_nStatus, g_nSleepTime = 200;//ÿ�����е�ʱ����
tagSnake *g_pHead , *g_pFood;//��ͷָ�룬ʳ��ָ��

int g_EndGameStatus = 0; //��Ϸ�����������1��ײ��ǽ��2��ҧ���Լ���3�������˳���Ϸ��



void Pos(int x, int y)//���ù��λ��
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

int BiteSelf()//�ж��Ƿ�ҧ�����Լ�
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


void IsCanCrossWall()//���ܴ�ǽ
{
	if (g_pHead->x == 0 || g_pHead->x == 56 || g_pHead->y == 0 || g_pHead->y == 26)
	{
		g_EndGameStatus = 1;
		EndGame();
	}
}


void Pause()//��ͣ
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

//����
void Up()
{
	tagSnake * pNext;
	IsCanCrossWall();
	pNext = (tagSnake*)malloc(sizeof(tagSnake));
	pNext->x = g_pHead->x;
	pNext->y = g_pHead->y - 1;
	IsHaveFood(pNext);
	
}
void Down()//����
{
	tagSnake * pNext;
	IsCanCrossWall();
	pNext = (tagSnake*)malloc(sizeof(tagSnake));
	pNext->x = g_pHead->x;
	pNext->y = g_pHead->y + 1;
	IsHaveFood(pNext);
}

void Left()//����
{
	tagSnake * pNext;
	IsCanCrossWall();
	pNext = (tagSnake*)malloc(sizeof(tagSnake));
	pNext->x = g_pHead->x - 2;
	pNext->y = g_pHead->y;
	IsHaveFood(pNext);
	
}

void Right()//����
{
	tagSnake * pNext;
	IsCanCrossWall();
	pNext = (tagSnake*)malloc(sizeof(tagSnake));
	pNext->x = g_pHead->x + 2;
	pNext->y = g_pHead->y;
	IsHaveFood(pNext);
}

void IsHaveFood(tagSnake *pNext)//�ж��Ƿ�Ե�ʳ��
{
	if (pNext->x == g_pFood->x && pNext->y == g_pFood->y)//�Ե�ʳ��
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
	else //û�гԵ�ʳ��
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
void SnakeMove()//��ǰ��,��U,��D,��L,��R
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
	if (BiteSelf() == 1) //�ж��Ƿ��ҧ���Լ�
	{
		g_EndGameStatus = 2;
		EndGame();
	}
}



void CreateFood()//�������ʳ��
{
	srand((unsigned)time(NULL));
	tagSnake *pFood1,*pTra;
	pFood1 = (tagSnake*)malloc(sizeof(tagSnake));
	while ((pFood1->x % 2) != 0) //��֤��Ϊż����ʹ��ʳ��������ͷ����
	{
		pFood1->x = rand() % 52 + 2;
	}
	pFood1->y = rand() % 24 + 1;
	pTra = g_pHead;
	while (pTra->next!= NULL)
	{
		if (pTra->x == pFood1->x && pTra->y == pFood1->y) //�ж������Ƿ���ʳ���غ�
		{
			free(pFood1);
			CreateFood();
		}
		pTra = pTra->next;
	}
	PrintDia(pFood1->x, pFood1->y);
	g_pFood = pFood1;
}

void InitSnake()//��ʼ������
{
	g_pHead=(tagSnake*)malloc(sizeof(tagSnake));
	g_pHead->next = NULL;
	g_pHead->x = 24;
	g_pHead->y = 5;
	PrintDia(g_pHead->x, g_pHead->y);
}

//�浵
void SaveGame()
{
	tagSnake *pTra = g_pHead;
	FILE *pFile = fopen("data.txt","wb");

	//д�ߵĳ���
	int nCount = g_nScore / 10 + 1;
	fwrite(&nCount, 4, 1, pFile);
	
	//д��������
	for (int i = 0; i < nCount; i++)
	{
		fwrite(&pTra->x, 4, 1, pFile);
		fwrite(&pTra->y, 4, 1, pFile);
		pTra = pTra->next;
	}
	//дʳ��
	fwrite(&g_pFood->x, 4, 1, pFile);
	fwrite(&g_pFood->y, 4, 1, pFile);
	//д״̬
	fwrite(&g_nStatus, 4, 1, pFile);
	//д����
	fwrite(&g_nScore, 4, 1, pFile);
	fclose(pFile);
}

//����
void LoadGame()
{
	tagSnake *pTail=g_pHead;

	FILE *pFile = fopen("data.txt", "rb");
	
	int nCount = 0;
	//������
	fread(&nCount, 4, 1, pFile);

	//������
	for (int i = 0; i < nCount; i++)
	{
		tagSnake* pNewNode = (tagSnake*)malloc(sizeof(tagSnake));
		fread(&pNewNode->x, 4, 1, pFile);
		fread(&pNewNode->y, 4, 1, pFile);
		

		if (i==0)//β�巨�ָ�����
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
	
	//��ʳ��
	fread(&g_pFood->x, 4, 1, pFile);
	fread(&g_pFood->y, 4, 1, pFile);

    //��״̬
	fread(&g_nStatus, 4, 1, pFile);

	//������
	fread(&g_nScore, 4, 1, pFile);
}
