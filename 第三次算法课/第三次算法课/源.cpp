#include<iostream>
#include<stack>

using namespace std;

int main()
{
	char list[36];
	for (int i = 0; i < 36; i++)
	{
		if (i <= 9)list[i] = i + '0';
		else list[i] = i + 7+'0';
	}
	stack<char>a;
	int x, n, i=16;
	cin >> n;
	while (n > 0)
	{
		cin >> x;
		while (x != 0)
		{
			
			a.push(list[x%i]);
			x/= i;
		}
		while (!a.empty())
		{
			cout << a.top();
			a.pop();
		}
		cout << endl;
		n--;
	}
	return 0;
}