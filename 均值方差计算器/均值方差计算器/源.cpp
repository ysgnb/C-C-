#include<iostream>
#include<math.h>
using namespace std;
int main()
{
	int n=1;
	while (n)//当输入n=0时，退出
	{
		cout << "输入数据的个数";
		cin >> n;
		if (!n)break;
		int* data = new int[n + 1];
		for (int i = 1; i <= n; i++)
			cin >> data[i];

		double mean = 0.0, variance = 0.0, mean2 = 0.0;
		for (int i = 1; i <= n; i++)
			mean += data[i];
		mean /= n;

		for (int i = 1; i <= n; i++)
			mean2 += data[i] * data[i];
		mean2 /= n;

		variance = mean2 - mean * mean;

		cout << "输入了" << n << "个数据" << endl;
		cout << "E(X)=" << mean << endl;
		cout << "D(X)=" << variance << endl;
		cout << "√D(X)=" << sqrt(variance) << endl<<endl;

	}
	return 0;
}