#include <iostream>
using namespace std;

void Quicksort(int arry[], int L, int R)
{
	if (L >= R)
		return;
	int left = L, right = R;
	int pivot/*中心轴*/ = arry[left];
	//每次都选最左边作为中心轴

	while (left < right)
	{
		while (left<right && arry[right] >= pivot)
			right--;
		if (left < right)
			arry[left] = arry[right];

		while (left < right && arry[left] <= pivot)
			left++;
		if (left < right)
			arry[right] = arry[left];

		if (left >= right)
			arry[left] = pivot;
	}
	Quicksort(arry, L, right - 1);
	Quicksort(arry, right + 1, R);
}

int main()
{
	int arry[10];
	for (int i = 0; i <= 9; i++)
		cin >> arry[i];
	Quicksort(arry, 0, 9);
	for (int i = 0; i <= 9; i++)
		cout << arry[i]<<' ';
	return 0;
}