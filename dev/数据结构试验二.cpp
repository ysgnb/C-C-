#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

# define TRUE 1
# define ERROR 0
# define OK 1
# define OVERFLOW -2
# define FALSE 0

typedef struct LNode
{
	int data;
	LNode* next;
}LNode,*LinkList;

void CreatList_L(LinkList L, int n)
{//逆位序输入n个元素的值，建立带头节点的单链表L
	L = (LinkList)malloc(sizeof(LNode));
	L->next = NULL;
	for (int i = n; i > 0; i--)
	{
		LinkList p = (LinkList)malloc(sizeof(LNode));
		scanf("%d",&p->data);
		p->next = L->next;
		L->next = p;
	}
}

void MergeList_L(LinkList La,LinkList Lb,LinkList Lc)
{
	LinkList pa = La->next;//pa指向第1个La元素
	LinkList pb = Lb->next;//pb指向第1个Lb元素
	LinkList pc;
	pc = La;
	Lc = pc;//La的头节点作为Lc的头节点
	while (pb && pc)//不为NULL
	{
		if (pa->data <= pb->data)
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
		}
		else
		{
			pc->next = pb;
			pc = pb;
			pb = pb->next;
		}
	}
	pc->next = pa ? pa : pb;
	free(Lb);
}
int main()
{
	LinkList La, Lb, Lc;

	CreatList_L(La, 4);
	CreatList_L(Lb, 7);
	MergeList_L(La, Lb, Lc);
	return 0;
}


