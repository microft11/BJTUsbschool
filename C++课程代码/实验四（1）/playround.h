#ifndef _PLAYGROUND_H_
#define _PLAYGROUND_H_
#include"gragh.h"

class CPlayground
{
public:
	CPlayground(CPlaygragh & g, double lane, double cost1 = 100.0, double cost2 = 80.0);
	double computer_cost() const;
private:
	CPlaygragh g;
	const double LANE;
	const double COST1;
	const double COST2;
};

#endif
