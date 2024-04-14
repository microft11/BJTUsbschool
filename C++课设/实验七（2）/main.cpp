#include <iostream>

using namespace std;

class Shape{
	protected:
		double m_x, m_y;
	public:
		Shape(double x, double y);
		double GetArea();
};

Shape::Shape(double x, double y)
{
	m_x = x;
	m_y = y;
}

double Shape::GetArea()
{
	return 0.0;
}

class Circle : public Shape
{
	public:
		static double PI;
		Circle(double r);
		double GetArea();
		double GetRadius();
};

double Circle::PI = 3.14;

Circle::Circle(double r) : Shape(m_x, m_y)
{
	m_x = m_y = r;
}

double Circle::GetArea()
{
	return m_x * m_y * PI;
}

double Circle::GetRadius()
{
	return m_x;
}

class Rectangle : public Shape
{
	public:
		Rectangle(double l, double w);
		double GetArea();
		double GetLength();
		double GetWidth();
};

Rectangle::Rectangle(double l, double w) : Shape(m_x, m_y)
{
	m_x = l;
	m_y = w;
}

double Rectangle::GetArea()
{
	return m_x * m_y;
}

double Rectangle::GetLength()
{
	return m_x;
}

double Rectangle::GetWidth()
{
	return m_y;
}


int main()
{
	Circle c(1);
	cout<< "Բ�İ뾶Ϊ��" << c.GetRadius() <<endl;
	c.GetArea();
	cout<< "Բ�����Ϊ��" << c.GetArea() <<endl;
	
	cout<< "--------------" <<endl;
	
	Rectangle r(3,4);
	cout<< "���εĳ���Ϊ��" << r.GetLength() <<endl;
	cout<< "���εĿ��Ϊ��" << r.GetWidth() <<endl;
	r.GetArea();
	cout<< "���ε����Ϊ��" << r.GetArea() <<endl;
	
	return 0;

}
