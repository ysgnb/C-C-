#include<iostream>
#include<queue>
#include<string>

using namespace std;

typedef struct infor
{
	string name;
	float score;
	bool operator < (const infor& a)const
	{
		return a.score < score;
	}
};
int main()
{
	infor s1, s2, s3;
	s1.name = "aaa";
	s1.score = 10;
	s2.name = "bbb";
	s2.score = 30;
	s3.name = "ccc";
	s3.score = 20;
	priority_queue<infor> stu;
	stu.push(s1);
	stu.push(s2);
	stu.push(s3);
	for (int i = 1; i <= 3; i++)
	{
		cout << stu.top().score << endl;
		stu.pop();
	}

	return 0;
}