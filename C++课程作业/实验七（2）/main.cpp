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
	cout<< "圆的半径为：" << c.GetRadius() <<endl;
	c.GetArea();
	cout<< "圆的面积为：" << c.GetArea() <<endl;
	
	cout<< "--------------" <<endl;
	
	Rectangle r(3,4);
	cout<< "矩形的长度为：" << r.GetLength() <<endl;
	cout<< "矩形的宽度为：" << r.GetWidth() <<endl;
	r.GetArea();
	cout<< "矩形的面积为：" << r.GetArea() <<endl;
	
	return 0;

}
