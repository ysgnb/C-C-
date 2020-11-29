#include<iostream>
using namespace std;
class employee
{
public:
	char name[20];
	char id[20];
	employee(char name[], char id[]);
	~employee();
};
class manager :public employee
{
private:
	int salary;//月薪
};
class technician :public employee
{
private:
	int wage;//时薪
	int hours;//月工作时数
};