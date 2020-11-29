#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<graphics.h> //easyX,图形化编程
#include<conio.h>

#define size 10	//蛇头的大小，10像素*10像素

/****************需要的结构体****************************/
//坐标属性
typedef struct 
{
	int x, y;
}mypoint;

//蛇
typedef struct snake
{
	mypoint xy[100];//坐标,最多长到100节
	int derection;//方向
	int length;	  //长度
}snake;

//食物
typedef struct
{
	mypoint fdxy;	//坐标
	int flag;	//标记
	int score;	//得分
}food;

//枚举方向
enum derection{up,down,left,right};

///////////////////函数功能实现///////////////////////

//初始化蛇
void initSnake(snake Snake)
{
	//初始三节
	Snake.xy[2].x = 0;
	Snake.xy[2].y = 0;//尾巴

	Snake.xy[1].x = 10;
	Snake.xy[1].y = 0;//中间

	Snake.xy[0].x = 20;
	Snake.xy[0].y = 0;//头
	//其实我有点想搞初始只有一个头的，然后位置随机，
	//方向随机。先放着，等做完再优化

	//初始方向
	Snake.derection = right;//一开始先默认向右吧
	Snake.length = 3;//一开始是三节的
}

//画蛇
void drawSnake(snake Snake)
{
	//绘制填充矩形
	for (int i = 0; i < Snake.length; i++)
	{
		//设置填充色
		setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
		//设置边界色
		setlinecolor(BLACK);//设为黑色
		//填充
		fillrectangle(Snake.xy[i].x, Snake.xy[i].y, size, size);

	}
}
int main()
{
	initgraph(1080,720);//初始化图形环境
	setbkcolor(RGB(255,255,128));//背景色
	cleardevice();//清屏
	
	srand((unsigned)time(NULL));

	snake Snake;
	initSnake(Snake);
	drawSnake(Snake);


	_getch();//防止闪屏,是控制台的，与getchar()相似
	closegraph();
	return 0;
}
