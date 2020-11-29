#include<iostream>
using namespace std;

void swap(int tree[], int a, int b)
{
	int temp = tree[a];
	tree[a] = tree[b];
	tree[b] = temp;
}

void heapify(int tree[], int n, int i)
{
	if (i >= n)
		return;
	int c1 = 2 * i + 1;
	int c2 = 2 * i + 2;
	int max = i;//�����±�
	if (c1<n && tree[c1]>tree[max])
		max = c1;

	if (c2<n && tree[c2]>tree[max])
		max = c2;
	//����max�������ڵ���±�
	if (max != i)//˵���ӽڵ�ȸ��ڵ��
	{
		swap(tree, max, i);
		heapify(tree, n, max);
		//��������heapify
	}
}

void build_heap(int tree[], int n)
{
	int last_node = n - 1;
	int parent = (last_node - 1) / 2;
	int i;
	for (i = parent; i >= 0; i--)
		heapify(tree, n, i);
}

void heapsort(int tree[], int n)
{
	build_heap(tree, n);
	int i;
	for (int i = n - 1; i >= 0; i--)
	{
		swap(tree, i, 0);
		heapify(tree, i, 0);
	}
}

int main()
{
	int arr[] = { 3,54,564,24,66,2,34,46,77,40 };
	int n = sizeof(arr) / 4;
	for (int i = 0; i < n; i++)
		cout << arr[i] << ' ';
	cout << endl;
	heapsort(arr, n);
	for (int i = 0; i < n; i++)
		cout << arr[i] << ' ';
}