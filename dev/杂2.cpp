#include <iostream>
#include<iomanip>
using namespace std;
class A
{
	public:
		int a;
		A(int i)
		{
			a=i;
		}
 } ;
 /*ostream& operator <<(ostream &out,const A &a)
 {
 	out<<"a="<<a.a<<endl;
 	return out;
 }*/
 void operator<< (const A &a)
 {
 	cout<<"a="<<a.a<<endl;
 }
 int main()
 {
 	A a(1);
	cout<<a; 
 	return 0;
 }
