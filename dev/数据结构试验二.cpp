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
{//��λ������n��Ԫ�ص�ֵ��������ͷ�ڵ�ĵ�����L
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
	LinkList pa = La->next;//paָ���1��LaԪ��
	LinkList pb = Lb->next;//pbָ���1��LbԪ��
	LinkList pc;
	pc = La;
	Lc = pc;//La��ͷ�ڵ���ΪLc��ͷ�ڵ�
	while (pb && pc)//��ΪNULL
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


