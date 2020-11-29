#include<iostream>
#include<string>
using namespace std;
int main()
{
	int n;
	cin >> n;
	string country[100];
	for (int i = 0; i < n; i++)
		cin >> country[i];
	for(int i=0;i<n-1;i++)
		for (int j = i; j < n - 1 - i; j++)
			if (country[i] >= country[i + 1])
				country[i].swap(country[i + 1]);

	int p = -1;
	for (int i = 0; i < n; i++)
	{
		if (country[i] != "China")
			cout << country[i]<<endl;
		else p = i;
	}
	if (p != -1)
		cout << country[p];

	return 0;
}