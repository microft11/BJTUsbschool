#include"gragh.h"

CPlaygragh::CPlaygragh(const double len, const double w)
    : m_length(len), m_width(w)
{
}
	
double CPlaygragh::full_area(double ext) const
{
	return m_length * (m_width + 2 * ext) + 
	    PI * (m_width / 2 + ext) * (m_width / 2 + ext); 
}

double CPlaygragh::inner_area() const
{
	return m_length * m_width;
}
