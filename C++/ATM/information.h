#ifndef INFORMATION_H
#define INFORMATION_H
#include <iostream>
using namespace std;

class imformation
{
public:
	void print(double available, double total)
	{
		cout << "\nBalance Information:\n";
		cout << " - Available balance: $" << fixed << setprecision(2) << available << endl;
		cout << " - Total balance:  $" << fixed << setprecision(2) << total << endl;
	}
};
#endif
