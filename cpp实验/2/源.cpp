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
	int salary;//��н
};
class technician :public employee
{
private:
	int wage;//ʱн
	int hours;//�¹���ʱ��
};