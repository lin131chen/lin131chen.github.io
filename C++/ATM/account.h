#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
using namespace std;
class Member
{
public:
	int account;
	int pin;
	double availablenum;
	double totalnum;
	Member(int user, int password, double available, double total)
	{
		account = user;
		pin = password;
		availablenum = available;
		totalnum = total;
	};
    bool legal(int cinuser, int cinpassword)
	{
		if (cinuser == account && cinpassword == pin)
		{
			return true;
		}
		return false;
	};
};
#endif
