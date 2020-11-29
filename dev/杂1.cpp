#include <iostream>
#include<stdio.h> 
using namespace std;
void b();
void a()
{
	printf("hello");
	b();
}


void b()
{
	printf("world");
}
int main()
{
	a();
	return 0; 
 } 
