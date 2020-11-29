#include <iostream>
using namespace std;
int T = 0;
int d[4][2] = { {0,1},{1,0},{0,-1},{-1,0} };
//°´ÕÕÓÒÏÂ×óÉÏ
void dfs(int x, int y,char**map, int n,int m)
{
	if (map[x][y] == 'D')
	{
		
		return;
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			int a = x + d[i][0];
			int b = y + d[i][1];
			if (a < 0 || a >= n || b < 0 || b >= m
				||map[a][b]=='X')
				continue;
			
			T++;
			dfs(a, b, map,  n, m);
			
			T--;
		}
		return;
	}
}

int main()
{
	int n, m,t;
	n = m = t = -1;
	while (n != 0 && m != 0 && t != 0)
	{
		cin >> n >> m >> t;
		char** map = new char* [n];
		for(int i=0;i<n;i++)
			map[i] = new char[m];

		char** visit = new char* [n];
		for (int i = 0; i < n; i++)
			visit[i] = new char[m];

		
		for(int i=0;i<n;i++)
			for (int j = 0; j < m; j++)
				cin >> map[i][j];
		
		
		dfs(0, 0, map, n, m);
		cout << T;

	}
	return 0;
}