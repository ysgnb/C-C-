#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<graphics.h> //easyX,ͼ�λ����
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
#define size 20	//��ͷ�Ĵ�С��10����*10����
#define initLength 3//��ʼ������
#define ScreenLength 1080
#define ScreenWidth 720
/****************��Ҫ�Ľṹ��****************************/
//��������
typedef struct 
{
	int x, y;
}mypoint;

//��
typedef struct
{
	mypoint xy[100];//����,��೤��100��
	int derection;//����
	int length;	  //����
}snake;
snake Snake;

//ʳ��
typedef struct
{
	mypoint fdxy;	//����
	int flag;	//���
	int score;	//�÷�
}food;
food Food;//����ʵ����

//ö�ٷ���
enum derection{up,down,left,right};
//ö���Ѷ�
enum mode{easy=200,medium=100,hard=50,hell=20};

///////////////////��������ʵ��///////////////////////

//��ʼ����
void initSnake()
{
	//��ʼ����
	Snake.xy[2].x = 0;
	Snake.xy[2].y = 0;//β��

	Snake.xy[1].x = Snake.xy[2].x+size;
	Snake.xy[1].y = 0;//�м�

	Snake.xy[0].x = Snake.xy[1].x+size;
	Snake.xy[0].y = 0;//ͷ
	//��ʵ���е�����ʼֻ��һ��ͷ�ģ�Ȼ��λ�������
	//����������ȷ��ţ����������Ż�

	//��ʼ����
	Snake.derection = right;//һ��ʼ��Ĭ�����Ұ�
	Snake.length = 3;//һ��ʼ�����ڵ�
}

//����
void drawSnake()
{
	//����������
	for (int i = 0; i < Snake.length; i++)
	{
		//�������ɫ
		setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
		//���ñ߽�ɫ
		setlinecolor(BLACK);//��Ϊ��ɫ
		//���
		fillrectangle(Snake.xy[i].x, Snake.xy[i].y, Snake.xy[i].x + size, Snake.xy[i].y + size);

	}
}

//����
void moveSnake()
{
	//����β��ǰ�ƶ�
	for (int i = Snake.length - 1; i > 0; i--)//i!=0����Ҫ����Ϊ��ͷ�ķ����������
	{
		Snake.xy[i].x = Snake.xy[i - 1].x;
		Snake.xy[i].y = Snake.xy[i - 1].y;
	}
	//��ͷ���ƶ�
	switch (Snake.derection)
	{
	case up:
		Snake.xy[0].y -= size;
		break;
	case down:
		Snake.xy[0].y += size;
		break;
	case left:
		Snake.xy[0].x -= size;
		break;
	case right:
		Snake.xy[0].x += size;
		break;
	}
}

//��������
void keyCin()
{
	char useKey = _getch();

	//�ո���ͣ
	if (useKey == ' ')
		system("pause");

	switch (useKey)
	{
	case'W':
	case'w':
		if(Snake.derection!=down)
			Snake.derection = up;
		break;
	case'S':
	case's':
		if (Snake.derection != up)
			Snake.derection = down;
		break;
	case'A':
	case'a':
		if (Snake.derection != right)
			Snake.derection = left ;
		break;
	case'D':
	case'd':
		if (Snake.derection != left )
			Snake.derection = right ;
		break;
	}
}

//��ʼ��ʳ��
void initFood()
{
	Food.fdxy.x = (rand() % (ScreenLength / size)) * size;
	Food.fdxy.y = (rand() % (ScreenWidth / size)) * size;

	Food.flag = 1;//ʳ�����
	//ʳ�ﲻ�ܳ�����������
	for (int i = 0; i < Snake.length; i++)
	{
		if (Food.fdxy.x == Snake.xy[i].x && Food.fdxy.y == Snake.xy[i].y)
		{
			Food.fdxy.x = (rand() % (ScreenLength / size)) * size;
			Food.fdxy.y = (rand() % (ScreenWidth / size)) * size;
		}
	}
}

//��ʳ��
void drawFood()
{
	//�������ɫ
	setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
	//���ñ߽�ɫ
	setlinecolor(BLACK);//��Ϊ��ɫ
	//���
	fillrectangle(Food.fdxy.x, Food.fdxy.y, Food.fdxy.x+size, Food.fdxy.y+size);
}

//��ʳ��
void eatFood()
{
	if (Snake.xy[0].x == Food.fdxy.x && Snake.xy[0].y == Food.fdxy.y)
	{
		Food.flag = 0;
		Snake.length++;
		Food.score += 1;
	}
}

//��ʾ����
void showScore()
{
	//��ʽ����ӡ
	char score[20] = "";
	sprintf_s(score, "Score: %d", Food.score);
	settextcolor(LIGHTBLUE);
	settextstyle(25, 0, "����");
	outtextxy(ScreenLength-200, 50, score);//�ĳɶ��ַ����ɱ��ⱨ��
}

//�����ж�
HWND hwnd = NULL;
int  SnakeDie()
{
	//��������
	if (Snake.xy[0].x >= ScreenLength || Snake.xy[0].x < 0 || Snake.xy[0].y < 0 || Snake.xy[0].y>=ScreenWidth )
	{
		mciSendString("close k.mp3", 0, 0, 0);
		mciSendString("open x.mp3", 0, 0, 0);
		mciSendString("seek x.mp3 to 131500", 0, 0, 0);
		mciSendString("play x.mp3 ", 0, 0, 0);
		MessageBox(hwnd, "��Ҫͣ��������", "GameOver", MB_SYSTEMMODAL);
		return 1;
	}
	//��ɱ
	for (int i = 1; i < Snake.length; i++)
	{
		if (Snake.xy[i].x == Snake.xy[0].x && Snake.xy[i].y == Snake.xy[0].y)
		{
			mciSendString("close k.mp3", 0, 0, 0);
			mciSendString("open x.mp3", 0, 0, 0);
			mciSendString("seek x.mp3 to 131500", 0, 0, 0);
			mciSendString("play x.mp3 ", 0, 0, 0);
			MessageBox(hwnd, "��Ҫͣ��������", "GameOver", MB_SYSTEMMODAL);
			return 1;
		}
	}
	return 0;
}
int main()
{
	initgraph(1080,720);//��ʼ��ͼ�λ���
	setbkcolor(RGB(255,255,128));//����ɫ
	cleardevice();//����
	
	mciSendString("open k.mp3", 0, 0, 0);
	mciSendString("setaudio k.mp3 volume to 40", 0, 0, 0);
	mciSendString("play k.mp3 repeat", 0, 0, 0);
	//������ܻᱨ�� Ҫ��һ�¶���

	srand((unsigned)time(NULL));

	initSnake();
	drawSnake();
	
	int mode = medium;
	while (1)
	{
		cleardevice();
		moveSnake();
		drawSnake();

		if (Food.flag == 0)
			initFood();

		if (_kbhit())
			keyCin();

		if (SnakeDie())			
			break;
		
		drawFood();
		eatFood();
		showScore();
		Sleep(mode);
	}

	_getch();//��ֹ����,�ǿ���̨�ģ���getchar()����
	closegraph();
	return 0;
}