# ifndef _GRAGH_H_
# define _GRAGH_H_

#include<iostream>
#include<math.h>
using namespace std;

#define PI 3.14159

class CPlaygragh
{
	public:
		CPlaygragh(const double len, const double w);
		double full_area(const double ext = 0) const;
		double inner_area() const;
	private:
		double m_length;
		double m_width;
};

#endif
