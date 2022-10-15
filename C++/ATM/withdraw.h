#ifndef WITHDRAW_H
#define WITHDRAW_H
#include <iostream>
using namespace std;

class withdraw
{
public:
	int number=0;
	int minusavailable(double available,  int num)
	{
		if (num == 1)
		{
			num = 20;
		}
		else if(num == 2)
		{
			num = 40;
		}
		else if (num == 3)
		{
			num = 60;
		}
		else if (num == 4)
		{
			num = 100;
		}
		else if (num == 5)
		{
			num = 200;
		}
		if (available < num)
		{
			return -1;
		}
		number = num;
		available -= num;
		return available;
	}

	int minustotla(double total, int num)
	{
		num = number;
		total -= num;
		return total;
	}

};
#endif
