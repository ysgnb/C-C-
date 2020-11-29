#include<iostream>
#include<stdlib.h>
#include<string>
using namespace std;
int main()
{
	string input;
	
	while (cin >> input)
	{
		if (input == "0")
			break;
		int len = input.length();
		int num = 11;
		while (num > 9)
		{
			num = 0;
			for (int i = 0; i < len; i++)
			{
				num += (int)input[i] - 48;
			}
			if (num <= 9)
				cout << num << endl;
			else
			{
				input = to_string(num);
				len = input.length();
			}
		}
	}
	return 0;
}
