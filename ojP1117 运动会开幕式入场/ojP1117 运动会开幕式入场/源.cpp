#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
template <class T>//template与模板之间不能插入其他语句
T Min(T a, T b)
{
	if (a < b)
		return a;
	else return b;
}
int main()
{
	/*vector<float> v;
	float score,max=0.0;
	while (cin >> score && score > 0)
	{
		v.push_back(score);
		max = score > max ? score : max;
	}
	for (vector<float>::iterator it = v.begin(); it != v.end(); it++)
	{
		*it = *it / max * 100;
		cout << *it << endl;
	}*/

	/*typedef vector<string> Country;
	Country country;*/

	typedef struct Student
	{
		string id;
		string name;
		string major;
		int score;
	}student;
	vector<Student> stu;
	student s;
	while (cin>>s.id)
	{
		cin >> s.name;
		cin >> s.major;
		cin >> s.score;
		stu.push_back(s);
	}
	float max, average;
	max = average = 0;
	for (vector<Student>::iterator it = stu.begin(); it != stu.end(); it++)
	{
		max = max > it->score ? max : it->score;
		average += it->score;
	}
	average /= stu.size();
	cout << max << ' ' << average;
	return 0;
}