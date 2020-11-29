#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<graphics.h> //easyX,ͼ�λ����
#include<conio.h>
#include<mmsystem.h>

#pragma comment(lib,"WINMM.LIB")

int size = 20;	//��ͷ�Ĵ�С��10����*10����
#define initLength 3//��ʼ������
int ScreenLength = 1080;
int ScreenWidth = 810;

/****************��Ҫ�Ľṹ��****************************/
//��������
typedef struct
{
	int x, y;
}mypoint;

//����
typedef struct newSnake
{
	newSnake* next, * front;
	mypoint xy;
	int derection;
	int length;
}newSnake;
//������ͷ
newSnake* snakeHead = (newSnake*)malloc(sizeof(newSnake));
newSnake* p, * q;
//ʳ��
typedef struct
{
	mypoint fdxy;	//����
	int flag;	//���
	int score;	//�÷�
}food;
food Food;//����ʵ����

//ö�ٷ���
enum derection { up, down, left, right };
//ö���Ѷ�
enum mode { easy = 200, medium = 100, hard = 50, hell = 20 };
int Mode = easy;//��ʼ�Ѷ�

///////////////////��������ʵ��///////////////////////
//��ʼ������
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
	}//������ɳ����߽磬����������

	snakeHead->derection = right;
	snakeHead->length = 1;
}

//�»���
void newDrawSnake()
{
	p = snakeHead;//pָ����ͷ
	//����������
	for (int i = 0; i < snakeHead->length; i++)
	{
		//�������ɫ
		setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
		//���ñ߽�ɫ
		setlinecolor(BLACK);//��Ϊ��ɫ
		//���
		fillrectangle(p->xy.x, p->xy.y, p->xy.x + size, p->xy.y + size);
		p = p->next;
	}
}

//�¶���
void newMoveSnake()
{
	p = snakeHead;
	q = p;
	while (q->next != NULL)
		q = q->next;//qָ��β���

	if (snakeHead->length > 1)
	{
		//ɾ��β���
		q->front->next = NULL;
		q->front = NULL;
		//���½��ڵ���뵽ͷ������
		newSnake* s = (newSnake*)malloc(sizeof(newSnake));
		s->front = snakeHead;
		s->next = snakeHead->next;
		if(snakeHead->next!=NULL)//����Ҫע��NULL��������޿�
			snakeHead->next->front = s;
		snakeHead->next = s;
		s->xy.x = snakeHead->xy.x;
		s->xy.y = snakeHead->xy.y;
	}
	//��ͷ���ƶ�
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

	//����ͣ�лָ������ָ��Żָ�
	mciSendString("resume k.mp3", 0, 0, 0);
	
}

//��������
void keyCin()
{
	char useKey = _getch();

	
	//�ո���ͣ
	if (useKey == ' ')
	{
		//��ͣ��Ϸ��ͬʱ��ͣ���ֲ���
		mciSendString("pause k.mp3", 0, 0, 0);

		system("pause");
	}
	switch (useKey)
	{
		//�ڿ�˫��ģʽ
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

//�³�ʼ��ʳ��
void newInitFood()
{
	Food.fdxy.x = (rand() % (ScreenLength / size)) * size;
	Food.fdxy.y = (rand() % (ScreenWidth / size)) * size;

	Food.flag = 1;//ʳ�����
	//ʳ�ﲻ�ܳ�����������
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

//��ʳ��
void drawFood()
{
	//�������ɫ
	setfillcolor(RGB(rand() % 255, rand() % 255, rand() % 255));
	//���ñ߽�ɫ
	setlinecolor(BLACK);//��Ϊ��ɫ
	//���
	fillrectangle(Food.fdxy.x, Food.fdxy.y, Food.fdxy.x + size, Food.fdxy.y + size);
}

//��Ч����
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

//��ʳ��
void eatFood()
{
	if (snakeHead->xy.x == Food.fdxy.x && snakeHead->xy.y == Food.fdxy.y)
	{
		Food.flag = 0;
		snakeHead->length++;
		Food.score += 1;
		choose++;
		SoundEffect();
		//�����ڵ�
		p = snakeHead;
		q = p;
		while (q->next != NULL)
			q = q->next;//qָ��β���
		newSnake* s = (newSnake*)malloc(sizeof(newSnake));
		q->next = s;
		s->front = q;
		s->next = NULL;//�������β�巨

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
	outtextxy(ScreenLength - 200, 50, score);//�ĳɶ��ַ����ɱ��ⱨ��
}

//�����ж�
HWND hwnd = NULL;
int  SnakeDie()
{
	//��������
	if (snakeHead->xy.x >= ScreenLength || snakeHead->xy.x < 0 || snakeHead->xy.y < 0 || snakeHead->xy.y >= ScreenWidth)
	{
		mciSendString("close k.mp3", 0, 0, 0);
		mciSendString("open x.mp3", 0, 0, 0);
		mciSendString("seek x.mp3 to 131500", 0, 0, 0);
		mciSendString("play x.mp3 ", 0, 0, 0);
		MessageBox(hwnd, "��Ҫͣ��������", "GameOver", MB_SYSTEMMODAL);
		return 1;
	}
	//��ɱ
	p = snakeHead->next;
	for (int i = 1; i < snakeHead->length; i++)
	{
		if (snakeHead->xy.x == p->xy.x && snakeHead->xy.y == p->xy.y)
		{
			mciSendString("close k.mp3", 0, 0, 0);
			mciSendString("open x.mp3", 0, 0, 0);
			mciSendString("seek x.mp3 to 131500", 0, 0, 0);
			mciSendString("play x.mp3 ", 0, 0, 0);
			MessageBox(hwnd, "��Ҫͣ��������", "GameOver", MB_SYSTEMMODAL);
			return 1;
		}
		p = p->next;
	}
	return 0;
}

//��Ϸ�˵�
void printsnake();
void welcometogame();
void menu()
{
	printsnake();
	welcometogame();
	//�Ѷ�����
	printf("��������ѡ����Ϸ�Ѷ�\n");
	printf("1��easy		2��medium		3��hard		 4��hell\n");
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
	//���ڴ�С����
	printf("��������ѡ�����С\n");
	printf("1:800*600		2��1080*810		3��1200*900\n");
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
	//��ͷ��С����
	printf("��������ѡ����ͷ��С\n");
	printf("1:10		2��15		3��20\n");
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

//�˵�ͼ��
int color(int c)  //�ı���ɫ
{
	SetConsoleTextAttribute(GetStdHandle(STD_ERROR_HANDLE), c);
	return 0;
}
void gotoxy(int x, int y)  //���ù��λ��
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
	system("cls");//����
	color(13);
	gotoxy(44, 3);
	printf("��Ϸ˵��");
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
	printf("tip1:���ܴ�ǽ������ҧ���Լ�");
	color(10);
	gotoxy(30, 11);
	printf("tip2:��WSAD�ֱ�����ߵ��ƶ�");
	color(14);
	gotoxy(30, 14);
	printf("tip3:EΪ���٣�QΪ����");
	color(11);
	gotoxy(30, 17);
	printf("tip4���ո���ͣ���ٰ�����������");
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
	printf("̰������Ϸ");
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
	printf("1.��ʼ��Ϸ");
	gotoxy(55, 22);
	printf("2.��Ϸ˵��");
	gotoxy(35, 24);
	printf("3.�˳���Ϸ");
	gotoxy(29, 27);
	color(3);
	printf("��ѡ��1 2 3����[ ]\b\b");
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
		printf("������1--3֮�����");
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
	initgraph(ScreenLength, ScreenWidth);//��ʼ��ͼ�λ���
	setbkcolor(RGB(255, 255, 128));//����ɫ
	cleardevice();//����

	mciSendString("open k.mp3", 0, 0, 0);
	mciSendString("setaudio k.mp3 volume to 60", 0, 0, 0);
	mciSendString("play k.mp3 repeat", 0, 0, 0);
	//������ܻᱨ�� Ҫ��һ�¶���

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
			Mode--;//��̬�Ѷ�����
		}
		if (_kbhit())
			keyCin();//��������

		if (SnakeDie())
			break;

		drawFood();
		eatFood();

		showScore();
		Sleep(Mode);
	}

	_getch();//��ֹ����,�ǿ���̨�ģ���getchar()����
	closegraph();
	return 0;
}


//�Ż��˱߽������ж�
//������̬�Ѷ�ģʽ
//���������Ż����ߵĳ��ȣ���ȡ��̬����ʽ����ͬ������ľ�̬
//��ͣʱ�����ֺ���Ϸͬʱ��ͣ
//��������Ϸ��Ч
//��������Ϸ�˵�
