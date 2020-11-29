#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h> //easyX,图形化编程
#include<conio.h>
#include<mmsystem.h>

#pragma comment(lib,"WINMM.LIB")

int size = 20;	//蛇头的大小，10像素*10像素
#define initLength 3//初始蛇身长度
int ScreenLength = 1080;
int ScreenWidth = 810;

/****************需要的结构体****************************/
//坐标属性
typedef struct
{
	int x, y;
}mypoint;

//新蛇
typedef struct newSnake
{
	newSnake* next, * front;
	mypoint xy;
	int derection;
	int length;
}newSnake;
//创建蛇头
newSnake* snakeHead = (newSnake*)malloc(sizeof(newSnake));
newSnake* p, * q;
//食物
typedef struct
{
	mypoint fdxy;	//坐标
	int flag;	//标记
	int score;	//得分
}food;
food Food;//对象实例化

//枚举方向
enum derection { up, down, left, right };
//枚举难度
enum mode { easy = 200, medium = 100, hard = 50, hell = 20 };
int Mode = easy;//初始难度

///////////////////函数功能实现///////////////////////
//初始化新蛇
int SnakeDie();
void newInitSnake()
{
	snakeHead->next = NULL;
	snakeHead->front = NULL;
	snakeHead->xy.x = (rand() % (ScreenLength / size)) * size-2*size ;
	snakeHead->xy.y = (rand() % (ScreenWidth / size)) * size-2*size;
	while (SnakeDie())
	{
		snakeHead->xy.x = (rand() % (ScreenLength / size)) * size - 2 * size;
		snakeHead->xy.y = (rand() % (ScreenWidth / size)) * size - 2 * size;
	}//如果生成超出边界，则重新生成

	snakeHead->derection = right;
	snakeHead->length = 1;
}

//新画蛇
void newDrawSnake()
{
	p = snakeHead;//p指向蛇头
	//绘制填充矩形
	for (int i = 0; i < snakeHead->length; i++)
	{
		//设置填充色
		setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
		//设置边界色
		setlinecolor(BLACK);//设为黑色
		//填充
		fillrectangle(p->xy.x, p->xy.y, p->xy.x + size, p->xy.y + size);
		p = p->next;
	}
}

//新动蛇
void newMoveSnake()
{
	p = snakeHead;
	q = p;
	while (q->next != NULL)
		q = q->next;//q指向尾结点

	if (snakeHead->length > 1)
	{
		//删除尾结点
		q->front->next = NULL;
		q->front = NULL;
		//将新建节点插入到头结点后面
		newSnake* s = (newSnake*)malloc(sizeof(newSnake));
		s->front = snakeHead;
		s->next = snakeHead->next;
		if(snakeHead->next!=NULL)//这里要注意NULL的情况，巨坑
			snakeHead->next->front = s;
		snakeHead->next = s;
		s->xy.x = snakeHead->xy.x;
		s->xy.y = snakeHead->xy.y;
	}
	//蛇头的移动
	switch (snakeHead->derection)
	{
	case up:
		snakeHead->xy.y -= size;
		break;
	case down:
		snakeHead->xy.y += size;
		break;
	case left:
		snakeHead->xy.x -= size;
		break;
	case right:
		snakeHead->xy.x += size;
		break;
	}
	newDrawSnake();

	//从暂停中恢复后，音乐跟着恢复
	mciSendString("resume k.mp3", 0, 0, 0);
	
}

//按键操作
void keyCin()
{
	char useKey = _getch();

	
	//空格暂停
	if (useKey == ' ')
	{
		//暂停游戏的同时暂停音乐播放
		mciSendString("pause k.mp3", 0, 0, 0);

		system("pause");
	}
	switch (useKey)
	{
		//挖坑双人模式
		/*if (double)
		{

		}*/
	case'W':
	case'w':
		if (snakeHead->derection != down)
			snakeHead->derection = up;
		break;
	case'S':
	case's':
		if (snakeHead->derection != up)
			snakeHead->derection = down;
		break;
	case'A':
	case'a':
		if (snakeHead->derection != right)
			snakeHead->derection = left;
		break;
	case'D':
	case'd':
		if (snakeHead->derection != left)
			snakeHead->derection = right;
		break;
	case'E':
	case'e':
		if(Mode>20)
			Mode -= 20;
		break;
	case'Q':
	case'q':
		Mode += 20;
	}
}

//新初始化食物
void newInitFood()
{
	Food.fdxy.x = (rand() % (ScreenLength / size)) * size;
	Food.fdxy.y = (rand() % (ScreenWidth / size)) * size;

	Food.flag = 1;//食物存在
	//食物不能出现在蛇身上
	p = snakeHead;
	for (int i = 0; i < snakeHead->length; i++)
	{
		if (Food.fdxy.x == p->xy.x && Food.fdxy.y == p->xy.y)
		{
			Food.fdxy.x = (rand() % (ScreenLength / size)) * size;
			Food.fdxy.y = (rand() % (ScreenWidth / size)) * size;
		}
		p = p->next;
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
	fillrectangle(Food.fdxy.x, Food.fdxy.y, Food.fdxy.x + size, Food.fdxy.y + size);
}

//音效设置
int choose = -1;
void SoundEffect()
{	
	choose  %= 7;

	switch (choose)
	{
	case 0:
		mciSendString(_T("open 00.wav type MPEGVideo "), NULL, 0, 0);
		mciSendString(_T("play 00.wav "), NULL, 0, 0);
		break;
	case 1:
		mciSendString(_T("open 11.wav type MPEGVideo alias bgm"), NULL, 0, 0);
		mciSendString(_T("play 11.wav  "), NULL, 0, 0);

		break;
	case 2:
		mciSendString(_T("open 22.wav type MPEGVideo alias bgm"), NULL, 0, 0);
		mciSendString(_T("play 22.wav "), NULL, 0, 0);

		break;
	case 3:
		mciSendString(_T("open 33.wav type MPEGVideo alias bgm"), NULL, 0, 0);
		mciSendString(_T("play 33.wav "), NULL, 0, 0);

		break;
	case 4:
		mciSendString(_T("open 44.wav type MPEGVideo alias bgm"), NULL, 0, 0);
		mciSendString(_T("play 44.wav "), NULL, 0, 0);
		break;
	case 5:
		mciSendString(_T("open 55.wav type MPEGVideo alias bgm"), NULL, 0, 0);
		mciSendString(_T("play 55.wav "), NULL, 0, 0);
		break;
	case 6:
		mciSendString(_T("open 66.wav type MPEGVideo alias bgm"), NULL, 0, 0);
		mciSendString(_T("play 66.wav "), NULL, 0, 0);
		break;
	
	default:
		break;
	}
}

//吃食物
void eatFood()
{
	if (snakeHead->xy.x == Food.fdxy.x && snakeHead->xy.y == Food.fdxy.y)
	{
		Food.flag = 0;
		snakeHead->length++;
		Food.score += 1;
		choose++;
		SoundEffect();
		//新增节点
		p = snakeHead;
		q = p;
		while (q->next != NULL)
			q = q->next;//q指向尾结点
		newSnake* s = (newSnake*)malloc(sizeof(newSnake));
		q->next = s;
		s->front = q;
		s->next = NULL;//这里采用尾插法

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
	outtextxy(ScreenLength - 200, 50, score);//改成多字符集可避免报错
}

//死亡判定
HWND hwnd = NULL;
int  SnakeDie()
{
	//出界死亡
	if (snakeHead->xy.x >= ScreenLength || snakeHead->xy.x < 0 || snakeHead->xy.y < 0 || snakeHead->xy.y >= ScreenWidth)
	{
		mciSendString("close k.mp3", 0, 0, 0);
		mciSendString("open x.mp3", 0, 0, 0);
		mciSendString("seek x.mp3 to 131500", 0, 0, 0);
		mciSendString("play x.mp3 ", 0, 0, 0);
		MessageBox(hwnd, "不要停下来啊！", "GameOver", MB_SYSTEMMODAL);
		return 1;
	}
	//自杀
	p = snakeHead->next;
	for (int i = 1; i < snakeHead->length; i++)
	{
		if (snakeHead->xy.x == p->xy.x && snakeHead->xy.y == p->xy.y)
		{
			mciSendString("close k.mp3", 0, 0, 0);
			mciSendString("open x.mp3", 0, 0, 0);
			mciSendString("seek x.mp3 to 131500", 0, 0, 0);
			mciSendString("play x.mp3 ", 0, 0, 0);
			MessageBox(hwnd, "不要停下来啊！", "GameOver", MB_SYSTEMMODAL);
			return 1;
		}
		p = p->next;
	}
	return 0;
}

//游戏菜单
void printsnake();
void welcometogame();
void menu()
{
	printsnake();
	welcometogame();
	//难度设置
	printf("输入数字选择游戏难度\n");
	printf("1：easy		2：medium		3：hard		 4：hell\n");
	int a;
	scanf("%d", &a);
	switch (a)
	{
	case 1:
		Mode = easy;
		break;
	case 2:
		Mode = medium;
		break;
	case 3:
		Mode = hard;
		break;
	case 4:
		Mode = hell;
		break;
	}
	//窗口大小设置
	printf("输入数字选择窗体大小\n");
	printf("1:800*600		2：1080*810		3：1200*900\n");
	scanf("%d", &a);
	switch (a)
	{
	case 1:
		ScreenLength = 800;
		ScreenWidth = 600;
		break;
	case 2:
		ScreenLength = 1080;
		ScreenWidth = 810;
		break;
	case 3:
		ScreenLength = 1200;
		ScreenWidth = 700;
		break;
	}
	//蛇头大小设置
	printf("输入数字选择蛇头大小\n");
	printf("1:10		2：15		3：20\n");
	scanf("%d", &a);
	switch (a)
	{
	case 1:
		size = 10;
		break;
	case 2:
		size = 15;
		break;
	case 3:
		size = 20;
		break;
	}
}

//菜单图案
int color(int c)  //改变颜色
{
	SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), c);
	return 0;
}
void gotoxy(int x, int y)  //设置光标位置
{
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_ERROR_HANDLE), c);
}
void printsnake()
{
	gotoxy(35, 1);
	color(6);
	printf("/^\\/^\\");

	gotoxy(34, 2);
	printf("|_| O|");

	gotoxy(33, 2);
	color(2);
	printf("_");

	gotoxy(25, 3);
	color(12);
	printf("\\/");

	gotoxy(31, 3);
	color(2);
	printf("/");

	gotoxy(37, 3);
	color(6);
	printf("\\_/");

	gotoxy(41, 3);
	color(10);
	printf("\\");

	gotoxy(26, 4);
	color(12);
	printf("\\____");

	gotoxy(32, 4);
	printf("__________/");

	gotoxy(31, 4);
	color(2);
	printf("|");

	gotoxy(43, 4);
	color(10);
	printf("\\");

	gotoxy(32, 5);
	color(2);
	printf("\\_____");

	gotoxy(44, 5);
	color(10);
	printf("\\");

	gotoxy(39, 6);
	printf("|    |             \\");

	gotoxy(38, 7);
	printf("/   /                \\");

	gotoxy(37, 8);
	printf("/  /                \\ \\");

	gotoxy(35, 9);
	printf("/  /                    \\ \\");

	gotoxy(34, 10);
	printf("/  /                        \\ \\");

	gotoxy(33, 11);
	printf("/  /          __---__     \\  \\");

	gotoxy(32, 12);
	printf("/  /        _-~     ~-_    \\  \\");

	gotoxy(31, 13);
	printf("             _-~    _--_  ~-_   -/  \ ");

	gotoxy(32, 14);
	printf("\\       ~-____-~   _-~    ~-_    ~-_-~    \\  \\");

	gotoxy(33, 15);
	printf("~-_         _-~    ~-_     _-~");

	gotoxy(35, 16);
	printf("~--______-~         ~-___-~");
}
void explanation()
{
	int i, j = 1;
	system("cls");//清屏
	color(13);
	gotoxy(44, 3);
	printf("游戏说明");
	color(2);
	for (i = 6; i <= 22; i++)
	{
		for (j = 20; j <= 75; j++)
		{
			gotoxy(j, i);
			if (i == 6 || i == 22)
				printf("=");
			else if (j == 20 || j == 75)
				printf("||");
		}
	}
	color(3);
	gotoxy(30, 8);
	printf("tip1:不能穿墙，不能咬到自己");
	color(10);
	gotoxy(30, 11);
	printf("tip2:用WSAD分别控制蛇的移动");
	color(14);
	gotoxy(30, 14);
	printf("tip3:E为加速，Q为减速");
	color(11);
	gotoxy(30, 17);
	printf("tip4：空格暂停，再按其他键继续");
	_getch();
	system("cls");
	printsnake();
	menu();
}
void welcometogame()
{
	int n;
	int i, j = 1;
	gotoxy(43, 18);
	color(11);
	printf("贪吃蛇游戏");
	color(14);
	for (i = 20; i < 26; i++)
	{
		for (j = 27; j <= 74; j++)
		{
			gotoxy(j, i);
			if (i == 20 || i == 26)
			{
				printf("-");
			}
			else if (j == 27 || j == 74)
			{
				printf("|");
			}
		}
	}
	color(12);
	gotoxy(35, 22);
	printf("1.开始游戏");
	gotoxy(55, 22);
	printf("2.游戏说明");
	gotoxy(35, 24);
	printf("3.退出游戏");
	gotoxy(29, 27);
	color(3);
	printf("请选择【1 2 3】：[ ]\b\b");
	color(14);
	scanf("%d", &n);
	switch (n)
	{
	case 1:
		break;
	case 2:
		explanation();
	case 3:
		exit(0);
		break;
	default:
		color(12);
		gotoxy(40, 28);
		printf("请输入1--3之间的数");
		_getch();
		system("cls");
		printsnake();
		welcometogame();
	}
}


int main()
{
	menu();
	Sleep(200);
	initgraph(ScreenLength, ScreenWidth);//初始化图形环境
	setbkcolor(RGB(255, 255, 128));//背景色
	cleardevice();//清屏

	mciSendString("open k.mp3", 0, 0, 0);
	mciSendString("setaudio k.mp3 volume to 60", 0, 0, 0);
	mciSendString("play k.mp3 repeat", 0, 0, 0);
	//这里可能会报错 要改一下东西

	srand((unsigned)time(NULL));


	newInitSnake();
	newDrawSnake();

	
	while (1)
	{
		cleardevice();

		newMoveSnake();
		//newDrawSnake();

		if (Food.flag == 0)
		{
			newInitFood();
			Mode--;//动态难度设置
		}
		if (_kbhit())
			keyCin();//键盘输入

		if (SnakeDie())
			break;

		drawFood();
		eatFood();

		showScore();
		Sleep(Mode);
	}

	_getch();//防止闪屏,是控制台的，与getchar()相似
	closegraph();
	return 0;
}


//优化了边界死亡判定
//新增动态难度模式
//采用链表优化了蛇的长度，采取动态的形式，不同于数组的静态
//暂停时，音乐和游戏同时暂停
//增加了游戏音效
//增加了游戏菜单
