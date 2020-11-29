#include<iostream>
using namespace std;
class point
{
public:
	point(int xx = 0, int yy = 0)
	{
		x = xx;
		y = yy;
	}
	point(point& p);
	int getx() { return x; }
	int gety() { return y; }

	point& operator++();//前置++
	point operator++(int);//后置++
	point& operator--();//前置--
	point operator--(int);//后置--
	void show()
	{
		cout << "(" << x << "," << y << ")" << endl;
	}
private:
	int x, y;
};
point::point(point& p)
{
	x = p.x;
	y = p.y;
}
point&point::operator++()
{
	x++;
	y++;
	return *this;
}
point point::operator++(int)
{
	point old = *this;
	++(*this);
	return old;
}
point& point::operator--()
{
	x--;
	y--;
	return *this;
}
point point::operator--(int)
{
	point old = *this;
	--(*this);
	return old;
}
int main()
{
	point a(0, 0);
	a.show();
	(a++).show();
	a.show();
	(++a).show();
	a.show();
	(a--).show();
	a.show();
	(--a).show();
	a.show();

	return 0;
}