#ifndef deposit_H
#define deposit_H
#include <iostream>
using namespace std;

class deposit
{
public:
	int plus(double total, double num)
	{
		total += num;
		return total;
	}
};

#endif deposit_H