#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<graphics.h> //easyX,图形化编程
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"WINMM.LIB")
#define size 20	//蛇头的大小，10像素*10像素
#define initLength 3//初始蛇身长度
#define ScreenLength 1080
#define ScreenWidth 720
/****************需要的结构体****************************/
//坐标属性
typedef struct 
{
	int x, y;
}mypoint;

//蛇
typedef struct
{
	mypoint xy[100];//坐标,最多长到100节
	int derection;//方向
	int length;	  //长度
}snake;
snake Snake;

//食物
typedef struct
{
	mypoint fdxy;	//坐标
	int flag;	//标记
	int score;	//得分
}food;
food Food;//对象实例化

//枚举方向
enum derection{up,down,left,right};
//枚举难度
enum mode{easy=200,medium=100,hard=50,hell=20};

///////////////////函数功能实现///////////////////////

//初始化蛇
void initSnake()
{
	//初始三节
	Snake.xy[2].x = 0;
	Snake.xy[2].y = 0;//尾巴

	Snake.xy[1].x = Snake.xy[2].x+size;
	Snake.xy[1].y = 0;//中间

	Snake.xy[0].x = Snake.xy[1].x+size;
	Snake.xy[0].y = 0;//头
	//其实我有点想搞初始只有一个头的，然后位置随机，
	//方向随机。先放着，等做完再优化

	//初始方向
	Snake.derection = right;//一开始先默认向右吧
	Snake.length = 3;//一开始是三节的
}

//画蛇
void drawSnake()
{
	//绘制填充矩形
	for (int i = 0; i < Snake.length; i++)
	{
		//设置填充色
		setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
		//设置边界色
		setlinecolor(BLACK);//设为黑色
		//填充
		fillrectangle(Snake.xy[i].x, Snake.xy[i].y, Snake.xy[i].x + size, Snake.xy[i].y + size);

	}
}

//动蛇
void moveSnake()
{
	//从蛇尾往前移动
	for (int i = Snake.length - 1; i > 0; i--)//i!=0很重要，因为蛇头的方向是任意的
	{
		Snake.xy[i].x = Snake.xy[i - 1].x;
		Snake.xy[i].y = Snake.xy[i - 1].y;
	}
	//蛇头的移动
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

//按键操作
void keyCin()
{
	char useKey = _getch();

	//空格暂停
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

//初始化食物
void initFood()
{
	Food.fdxy.x = (rand() % (ScreenLength / size)) * size;
	Food.fdxy.y = (rand() % (ScreenWidth / size)) * size;

	Food.flag = 1;//食物存在
	//食物不能出现在蛇身上
	for (int i = 0; i < Snake.length; i++)
	{
		if (Food.fdxy.x == Snake.xy[i].x && Food.fdxy.y == Snake.xy[i].y)
		{
			Food.fdxy.x = (rand() % (ScreenLength / size)) * size;
			Food.fdxy.y = (rand() % (ScreenWidth / size)) * size;
		}
	}
}

//画食物
void drawFood()
{
	//设置填充色
	setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
	//设置边界色
	setlinecolor(BLACK);//设为黑色
	//填充
	fillrectangle(Food.fdxy.x, Food.fdxy.y, Food.fdxy.x+size, Food.fdxy.y+size);
}

//吃食物
void eatFood()
{
	if (Snake.xy[0].x == Food.fdxy.x && Snake.xy[0].y == Food.fdxy.y)
	{
		Food.flag = 0;
		Snake.length++;
		Food.score += 1;
	}
}

//显示分数
void showScore()
{
	//格式化打印
	char score[20] = "";
	sprintf_s(score, "Score: %d", Food.score);
	settextcolor(LIGHTBLUE);
	settextstyle(25, 0, "楷体");
	outtextxy(ScreenLength-200, 50, score);//改成多字符集可避免报错
}

//死亡判定
HWND hwnd = NULL;
int  SnakeDie()
{
	//出界死亡
	if (Snake.xy[0].x >= ScreenLength || Snake.xy[0].x < 0 || Snake.xy[0].y < 0 || Snake.xy[0].y>=ScreenWidth )
	{
		mciSendString("close k.mp3", 0, 0, 0);
		mciSendString("open x.mp3", 0, 0, 0);
		mciSendString("seek x.mp3 to 131500", 0, 0, 0);
		mciSendString("play x.mp3 ", 0, 0, 0);
		MessageBox(hwnd, "不要停下来啊！", "GameOver", MB_SYSTEMMODAL);
		return 1;
	}
	//自杀
	for (int i = 1; i < Snake.length; i++)
	{
		if (Snake.xy[i].x == Snake.xy[0].x && Snake.xy[i].y == Snake.xy[0].y)
		{
			mciSendString("close k.mp3", 0, 0, 0);
			mciSendString("open x.mp3", 0, 0, 0);
			mciSendString("seek x.mp3 to 131500", 0, 0, 0);
			mciSendString("play x.mp3 ", 0, 0, 0);
			MessageBox(hwnd, "不要停下来啊！", "GameOver", MB_SYSTEMMODAL);
			return 1;
		}
	}
	return 0;
}
int main()
{
	initgraph(1080,720);//初始化图形环境
	setbkcolor(RGB(255,255,128));//背景色
	cleardevice();//清屏
	
	mciSendString("open k.mp3", 0, 0, 0);
	mciSendString("setaudio k.mp3 volume to 40", 0, 0, 0);
	mciSendString("play k.mp3 repeat", 0, 0, 0);
	//这里可能会报错 要改一下东西

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

	_getch();//防止闪屏,是控制台的，与getchar()相似
	closegraph();
	return 0;
}