#include<iostream>
using namespace std;

void insert_sort(int arr[], int n)
{
	int temp;

	for (int i = 1,j; i < n; i++)
	{
		temp = arr[i];
		for ( j = i; j >= 1 && temp < arr[j - 1]; j--)
			arr[j] = arr[j - 1];
		arr[j] = temp;
	}
}

int main()
{
	int arr[] = { 2,3,21,53,25,4,5,12,1 };
	for (int i = 0; i < sizeof(arr) / 4; i++)
		cout << arr[i] << ' ';
	cout << endl;
	insert_sort(arr, sizeof(arr) / 4);
	for (int i = 0; i < sizeof(arr) / 4; i++)
		cout << arr[i] << ' ';
}