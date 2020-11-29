#include <iostream>
using namespace std;


void mergeArray(int A[], int lo, int mid, int hi)
{
	int* temp = new int[hi - lo + 1];
	int i = lo, j = mid + 1;
	int k = 0;

	while (i <= mid && j <= hi)
	{
		if (A[i] <= A[j])temp[k++] = A[i++];
		else temp[k++] = A[j++];
	}
	while (i <= mid)temp[k++] = A[i++];
	while (j <= hi)temp[k++] = A[j++];

	for (int i = lo, k = 0; i <= hi; i++, k++)
		A[i] = temp[k];
	delete[]temp;
}

void mergeSort(int A[], int lo, int hi)
{
	if (lo >= hi)return;
	int mid = lo + (hi - lo) / 2;
	mergeSort(A, lo, mid);
	mergeSort(A, mid + 1, hi);
	mergeArray(A, lo, mid, hi);
	/*for (int i = lo; i <= hi; i++)
		cout << A[i] << ' ';
	cout << endl;*/
}
int A[1000];

int main()
{
	int i = 0;
	while (cin >> A[i++]);
	mergeSort(A, 0, 9);
	for (int i = 0; i <= 9; i++)cout << A[i] << ' ';
	return 0;
}