#include <iostream>
#include <iomanip>
#include "account.h"
#include "deposit.h"
#include "information.h"
#include "withdraw.h"
using namespace::std;

int inputAnInteger(int begin, int end);
int  entermenu();
int enterwithdraw();
int main()
{
	cout << "Welcome!" << endl;
	Member user1(12345, 54321, 1000.0, 1200.0);
	Member user2(98765, 56789, 200.0, 200.0);
	Member* user = &user1;
	int pass = true;
	while (pass == true)
	{
		int number;
		int password;
		cout << "Please enter your account number: ";
		cin >> number;
		cout << endl;
		cout << "Enter your PIN : ";
		cin >> password;
		cin.ignore();
		if (user1.legal(number, password) == true)
		{
			user = &user1;
			pass = false;
		}
		else if (user2.legal(number, password) == true)
		{
			user = &user2;
			pass = false;
		}

	}

	while (true)
	{
		int menuChoice=entermenu();
		int withdrawChoice;
		imformation a;
		withdraw b;
		deposit c;
		int availminus;
		int availplus;
		int totalminus;
		switch (menuChoice)
		{

		case 1:
			a.print(user->availablenum, user->totalnum);
			break;

		case 2:
			withdrawChoice=enterwithdraw();
			if (withdrawChoice == 6)
			{
				break;
			}
			//avail = user->availablenum;
			availminus=b.minusavailable(user->availablenum, withdrawChoice);
			totalminus=b.minustotla(user->totalnum, b.number);
			if ((b.minusavailable(user->availablenum, withdrawChoice))==-1)
			{
				cout << "unenough\n\n" ;
				break;
			}
			user->availablenum = availminus;
			user->totalnum = totalminus;
			cout << "\nPlease take your cash from the cash dispenser.\n";
			break;

		case 3:
			double cent;
			cout << "Please enter a deposit amount in CENTS (or 0 to cancel):";
			cin >> cent;
			if (cent == 0)
			{
				cin.ignore();
				break;
			}
			cout << "Please insert a deposit envelope containing $ " << cent / 100 << " in the deposit slot." << endl;
			availplus=c.plus(user->totalnum, cent / 100);
			user->totalnum = availplus;
			cout << "Your envelope has been received.\nNOTE: The money deposited will not be available until we\nverify the amount of any enclosed cash, and any enclosed checks clear.\n\n";
			cin.ignore();
			break;

		case 4:
			cout << "Exiting the system...\n\n";
			cout << "Thank you!Goodbye!\n\n";
			system("pause");
			return 0;
		}

	}
}



int inputAnInteger(int begin, int end)
{
	char y[100];
	cin.getline(y, 100);
	if (y[0] == '\0' || strlen(y) > 2)
	{
		return -1;
	}
	for (int i = 0; y[i] != '\0'; i++)
	{
		if (!isdigit(y[i]))
		{
			return-1;
		}
	}
	int num = atoi(y);
	if (num >= begin && num <= end)
	{
		return num;
	}
	else
	{
		return -1;
	}

}

int entermenu()
{
	int menuChoice;
	do
	{
		cout << "\nMain menu:\n";
		cout << "1 - View my balance\n";
		cout << "2 - Withdraw cash\n";
		cout << "3 - Deposit funds\n";
		cout << "4 - Exit\n";
		cout << "Enter a choice : ";
	} while ((menuChoice = inputAnInteger(1, 4)) == -1);

	return menuChoice;
}

int enterwithdraw()
{
	int withdrawChoice;
	withdraw withdraw;
	do
	{
		cout << "\nWithdrawal options:" << endl;
		cout << "1 - $20\n";
		cout << "2 - $40\n";
		cout << "3 - $60\n" ;
		cout << "4 - $100\n" ;
		cout << "5 - $200\n" ;
		cout << "6 - Cancel transaction\n" ;
		cout << "Choose a withdrawal option(1 - 6) : ";
	} while ((withdrawChoice = inputAnInteger(1, 6)) == -1);
	withdraw.number = withdrawChoice;
	return withdrawChoice;
}
