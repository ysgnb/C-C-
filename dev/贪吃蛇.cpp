#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<graphics.h> //easyX,ͼ�λ����
#include<conio.h>

#define size 10	//��ͷ�Ĵ�С��10����*10����

/****************��Ҫ�Ľṹ��****************************/
//��������
typedef struct 
{
	int x, y;
}mypoint;

//��
typedef struct snake
{
	mypoint xy[100];//����,��೤��100��
	int derection;//����
	int length;	  //����
}snake;

//ʳ��
typedef struct
{
	mypoint fdxy;	//����
	int flag;	//���
	int score;	//�÷�
}food;

//ö�ٷ���
enum derection{up,down,left,right};

///////////////////��������ʵ��///////////////////////

//��ʼ����
void initSnake(snake Snake)
{
	//��ʼ����
	Snake.xy[2].x = 0;
	Snake.xy[2].y = 0;//β��

	Snake.xy[1].x = 10;
	Snake.xy[1].y = 0;//�м�

	Snake.xy[0].x = 20;
	Snake.xy[0].y = 0;//ͷ
	//��ʵ���е�����ʼֻ��һ��ͷ�ģ�Ȼ��λ�������
	//����������ȷ��ţ����������Ż�

	//��ʼ����
	Snake.derection = right;//һ��ʼ��Ĭ�����Ұ�
	Snake.length = 3;//һ��ʼ�����ڵ�
}

//����
void drawSnake(snake Snake)
{
	//����������
	for (int i = 0; i < Snake.length; i++)
	{
		//�������ɫ
		setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
		//���ñ߽�ɫ
		setlinecolor(BLACK);//��Ϊ��ɫ
		//���
		fillrectangle(Snake.xy[i].x, Snake.xy[i].y, size, size);

	}
}
int main()
{
	initgraph(1080,720);//��ʼ��ͼ�λ���
	setbkcolor(RGB(255,255,128));//����ɫ
	cleardevice();//����
	
	srand((unsigned)time(NULL));

	snake Snake;
	initSnake(Snake);
	drawSnake(Snake);


	_getch();//��ֹ����,�ǿ���̨�ģ���getchar()����
	closegraph();
	return 0;
}
