#include <iostream>
#include <iomanip>
#include <fstream>
#include <ctime>
#include <vector>
#include <string>
using namespace::std;

struct Date
{
   int year = 2000;
   int month = 0;
   int day = 0;
};

struct Reservation
{
   char phoneNumber[ 12 ] = ""; // phone number
   char name[ 8 ] = "";         // name
   Date date = Date();          // reservation date
   int time = 0;                // reservation time¡G1 for 11:30, 2 for 13:30,
                                //                   3 for 17:45, 4 for 19:45
   int partySize = 0;           // the number of customers for a reservation
   int menu = 0;                // 1 for NT$ 1080, 2 for NT$ 1680, 3 for NT$ 2280
};

struct AvailSeats
{
   Date date = Date(); // a date
   int numAvailSeats[ 5 ] = {};
}; // numAvailSeats[ 1 ]: the number of seats available for lunch #1 (11:30 ~ 13:30)
   // numAvailSeats[ 2 ]: the number of seats available for lunch #2 (13:30 ~ 15:30)
   // numAvailSeats[ 3 ]: the number of seats available for dinner #1 (17:45 ~ 19:45)
   // numAvailSeats[ 4 ]: the number of seats available for dinner #2 (19:45 ~ 21:45)

const int totalNumSeats = 15;

// array of days per month
int days[ 13 ] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// loads reservations from the file Reservations.dat
void loadReservations( vector< Reservation > &reservations );

// loads availSeats from the file AvailSeats.dat
void loadAvailSeats( vector< AvailSeats > &availSeats );

// initialize availSeats
void initializeAvailSeats( vector< AvailSeats > &availSeats );

// returns true if and only if date1 is earlier than date2
bool earlier( const Date &date1, const Date &date2 );

// returns date1 - date2, i.e., the number of days between date1 and date2
int difference( const Date &date1, const Date &date2 );

// input an integer in the range [ begin, end ]
int inputAnInteger( int begin, int end );

// make a reservation
void makeReservation( vector< Reservation > &reservations,
                      vector< AvailSeats > &availSeats );

// compute the current date
void computeCurrentDate( Date &currentDate );

// returns true if and only if the specified year is a leap year
bool leapYear( int year );

// input reservation date
void inputDate( vector< AvailSeats > &availSeats, Date &date,
                const Date &currentDate, int partySize );

// returns currentDate + numDays
Date addition( const Date &currentDate, int numDays );

// returns true if and only if there are at least n seats available for date,
// where n = requiredSeats
bool hasAvailableSeats( const vector< AvailSeats > &availSeats, const Date date,
                        int requiredSeats );

// returns true if availSeats[ i ].numAvailSeats[ timeCode ] >= requiredSeats,
// where availSeats[ i ].date == date
bool hasAvailableSeats( const vector< AvailSeats > &availSeats, const Date date,
                        int timeCode, int requiredSeats );

// returns a nonnegative integer i if availSeats[ i ].date == date,
// returns -1 otherwise.
int findAvailSeat( const vector< AvailSeats > &availSeats, Date date );

// choose a reservation time
void inputTimeCode( const vector< AvailSeats > &availSeats, const Date date,
                    int &timeCode, int partySize );

// displays partySize, date and time in reservation
void displayReservationInfo( const Reservation &reservation );

// availSeats[ i ].numAvailSeats[ timeCode ] -= requiredSeats,
// where availSeats[ i ].date == date
void decreaseAvailSeats( vector< AvailSeats > &availSeats, const Date date,
                         int timeCode, int requiredSeats );

// input a phoneNumber,
// then displays partySize, date and time in all reservations for phoneNumber
void viewReservation( const vector< Reservation > &reservations );

// returns true if and only if there is an i such that
// reservations[ i ].phoneNumber == phoneNumber
bool exist( const vector< Reservation > &reservations, char phoneNumber[] );

// displays partySize, date and time in all reservations for phoneNumber
void displayReservationInfo( const vector< Reservation > &reservations,
                             char phoneNumber[] );

// stores reservations into the file Reservations.dat
void storeReservations( vector< Reservation > &reservations );

// stores availSeats into the file AvailSeats.dat
void storeAvailSeats( vector< AvailSeats > &availSeats );

int main()
{
   cout << "Welcome to Zuo Zhe Zuo Sushi Wo Shou Si\n";

   vector< Reservation > reservations; // vector of all reservations
   vector< AvailSeats > availSeats;    // Vector of available seats

   loadReservations( reservations );
   initializeAvailSeats( availSeats );

   int choice;
   while( true )
   {
      cout << "\nEnter Your Choice\n"
         << "1. Make Reservation\n"
         << "2. Reservation Enquiry\n"
         << "3. End Program\n";

      do cout << "? ";
      while( ( choice = inputAnInteger( 1, 3 ) ) == -1 );

      switch( choice )
      {
      case 1:
         makeReservation( reservations, availSeats );
         break;
      case 2:
         viewReservation( reservations );
         break;
      case 3:
         cout << "\nThank you. Goodbye.\n\n";
         storeReservations( reservations );
         storeAvailSeats( availSeats );
         system( "pause" );
         return 0;
      default:
         cerr << "Incorrect Choice!\n";
         break;
      }
   }

   system( "pause" );
}

void loadReservations( vector< Reservation > &reservations )
{
	ifstream inReFile;
	inReFile.open("Reservations.dat", ios::binary);
	if (!inReFile)
	{
		cout << "File could not be opened1" << endl;
		system("pause");
		exit(1);
	}
	Reservation reservation;//added
	while (inReFile.read(reinterpret_cast<char*>(&reservation), sizeof(Reservation)))//modify
	{
		reservations.push_back(reservation);//modify
	}

}

void loadAvailSeats( vector< AvailSeats > &availSeats )
{
	ifstream inAvaFile;
	inAvaFile.open("AvailSeats.dat", ios::binary);
	if (!inAvaFile)
	{
		cout << "File coule not be opened2" <<endl;
		system("pause");
		exit(1);
	}
	AvailSeats availSeat;//added
	while ((inAvaFile.read(reinterpret_cast<char*>(&availSeat), sizeof(AvailSeats))))//modify
	{
		availSeats.push_back(availSeat);//modify
	}
}

void initializeAvailSeats( vector< AvailSeats > &availSeats )
{
   Date currentDate;
   AvailSeats add;
   computeCurrentDate( currentDate );

   loadAvailSeats( availSeats );

   Date date;
   if( availSeats.size() == 0 )
   {
	   //addition(currentDate, 30);
	   for (int i = 0; i <= 30; i++)
	   {
		   //addition(currentDate, 30);
		   availSeats.push_back(add);
		   availSeats[i].date= addition(currentDate, i);//modify
		   for (int k = 1; k <= 4; k++)//added
		   {
			   availSeats[i].numAvailSeats[k] = totalNumSeats;
		   }
	   }
   }
   else
   {
      if( earlier( availSeats[ availSeats.size() - 1 ].date, currentDate ) )
      {

		  int D=difference(availSeats[availSeats.size() - 1].date, currentDate);
		  for (int i = 0; i <= 30; i++)
		  {
			  availSeats[i].date = addition(currentDate, i);//modify
			  for (int k = 1; k <= 4; k++)//added
			  {
				  availSeats[i].numAvailSeats[k] = totalNumSeats;
			  }
		  }
      }
      else if( earlier( availSeats[ 0 ].date, currentDate ) )
      {
		  int j=difference(availSeats[0].date, currentDate);
		  int i = 1;
		  for (; i <= 30-j; i++)
		  {
			  availSeats[i].date= availSeats[i + j].date ;
			  /*for (int k = 1; k <= 4; k++)//added
			  {
				  availSeats[i].numAvailSeats[k] = totalNumSeats;
			  }*/
		  }
		  for (int k=i;k<=j;k++)//modify
		  {
			  //addition(currentDate, 30);
			  availSeats[i].date = addition(currentDate, k);//modify
			  for (int m = 1; m <= 4; m++)//added
			  {
				  availSeats[k].numAvailSeats[m] = totalNumSeats;
			  }
		  }
      }
   }
}

bool earlier( const Date &date1, const Date &date2 )
{
	if (date1.year < date2.year)
	{
		return true;
	}
	else if (date1.year == date2.year)//added
	{
		if (date1.month < date2.month)
		{
			return true;
		}
		else if (date1.month == date2.month)//added
		{
			if (date1.day < date2.day)
			{
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
}

int difference( const Date &date1, const Date &date2 )
{
	
	int left1 = days[date1.month] - date1.day;
	int betweenmon1=0;//modify
	int betweenmon2=0;//modify
	if (date1.year == date2.year)
	{
		if (date2.month !=date1.month)//added
		{
			for (int i = date1.month; i < date2.month; i++)
			{
				betweenmon1 = days[i + 1];
			}
			return left1 + betweenmon1 + date2.day;
		}
		else
		{
			return date2.day - date1.day;
		}
	}
	int betweenyear;
	 if (date1.year != date2.year)
	{
		for (int i = date1.month; i < 12; i++)
		{
			betweenmon1 += days[i + 1];
		}
		for (int k = 1; k < date2.month;k++)
		{
			betweenmon2 += days[k];
		}
		betweenyear = (date2.year - date1.year) * 365;
		return left1 + betweenmon1 +betweenyear+ betweenmon2+date2.day;
	}
}

int inputAnInteger( int begin, int end )
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
			return -1;
		}
	}
	int num = atoi(y);
	if (num >= begin && num <= end)
	{
		return num;
	}
	else
		return -1;

}

void makeReservation( vector< Reservation > &reservations,
                      vector< AvailSeats > &availSeats )
{
   Reservation newReservation;
   cout << endl;
   do cout << "Enter the party size (1~6): ";
   while( ( newReservation.partySize = inputAnInteger( 1, 6 ) ) == -1 );

   Date currentDate;
   computeCurrentDate( currentDate );

   inputDate( availSeats, newReservation.date, currentDate,
                          newReservation.partySize );

   inputTimeCode( availSeats, newReservation.date, newReservation.time,
                  newReservation.partySize );

   cout << "\nEnter name: ";
   cin >> newReservation.name;

   cout << "\nEnter phone Number: ";
   cin >> newReservation.phoneNumber;
   cin.ignore();

   cout << "\nChoose a menu:\n";
   cout << "1. NT$ 1080\n";
   cout << "2. NT$ 1680\n";
   cout << "3. NT$ 2280\n";

   do cout << "? ";
   while( ( newReservation.menu = inputAnInteger( 1, 3 ) ) == -1 );

   cout << endl;
   displayReservationInfo( newReservation );

   cout << "\nReservation Completed.\n";

   reservations.push_back( newReservation );

   decreaseAvailSeats( availSeats, newReservation.date, newReservation.time,
                       newReservation.partySize );
}

void computeCurrentDate( Date &currentDate )
{
	int remainingSeconds = static_cast<int>(time(0)) + 8 * 60 * 60;

	currentDate.year = 1970;

	int secondsPerYear = 365 * 24 * 60 * 60;
	if (leapYear(currentDate.year))
		secondsPerYear += 24 * 60 * 60;

	while (remainingSeconds >= secondsPerYear)
	{
		remainingSeconds -= secondsPerYear;
		currentDate.year++;

		secondsPerYear = 365 * 24 * 60 * 60;
		if (leapYear(currentDate.year))
			secondsPerYear += 24 * 60 * 60;
	}

	int days[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (leapYear(currentDate.year))
		days[2] = 29;

	currentDate.month = 1;
	while (remainingSeconds >= days[currentDate.month] * 24 * 60 * 60)
	{
		remainingSeconds -= days[currentDate.month] * 24 * 60 * 60;
		currentDate.month++;
	}

	currentDate.day = remainingSeconds / (24 * 60 * 60)+1;
}

bool leapYear( int year )
{
   return ( year % 400 == 0 || ( year % 4 == 0 && year % 100 != 0 ) );
}

void inputDate( vector< AvailSeats > &availSeats, Date &date,
                const Date &currentDate, int partySize )
{
	cout << "Choose a date " << endl;
	

	for (int i = 1; i <= 30; i++)
	{
		if (hasAvailableSeats(availSeats, availSeats[i].date, partySize) == true)
		{
			cout << i  << ". " << availSeats[i].date.year << "/";
			if (availSeats[i].date.month < 10)//added
				cout << '0';
			cout << availSeats[i].date.month << "/";
			if (availSeats[i].date.day < 10)//added
				cout << '0';
			cout << availSeats[i].date.day << " ";
		}
	}
	cout << endl;
	int choice1;
	do
	{
		cout << "?";
	} while ((choice1 = inputAnInteger(1, 30)) == -1|| (hasAvailableSeats(availSeats, availSeats[choice1].date, partySize) == false));//modify
	date.day = availSeats[choice1].date.day;//added
	date.month = availSeats[choice1].date.month;//added
	date.year = availSeats[choice1].date.year;//added
}

Date addition(const Date& currentDate, int numDays)
{
	Date date;
	if (currentDate.day + numDays > days[currentDate.month])
	{
		date.month = currentDate.month + 1;//mpdify
		if (date.month > 12)//modify
		{

			date.year = currentDate.year + 1;
			date.month = 1;
		}
		date.day = currentDate.day + numDays - days[currentDate.month];//modify
		date.year = currentDate.year;//added

	}
	else
	{
		date.year = currentDate.year;//added
		date.month = currentDate.month;//added
		date.day += currentDate.day + numDays;//modify
	}

	return date;
}

bool hasAvailableSeats( const vector< AvailSeats > &availSeats, const Date date,
                        int requiredSeats )
{
	int day = findAvailSeat(availSeats, date);
	if (availSeats[day].numAvailSeats[1]>= requiredSeats|| availSeats[day].numAvailSeats[2] >= requiredSeats || availSeats[day].numAvailSeats[3] >= requiredSeats||availSeats[day].numAvailSeats[4] >= requiredSeats)//modify
	{
		return true;
	}
	return false;

}

bool hasAvailableSeats( const vector< AvailSeats > &availSeats, const Date date,
                        int timeCode, int requiredSeats )
{
	int day = findAvailSeat(availSeats, date);
	if (availSeats[day].numAvailSeats[timeCode]  >= requiredSeats)
	{
		return true;
	}
	else
		return false;

}

int findAvailSeat( const vector< AvailSeats > &availSeats, Date date )
{
	
	for (int i = 1; i <=30; i++)//modify
	{
		if ( (availSeats[i].date.day== date.day) && (availSeats[i].date.month == date.month)&& (availSeats[i].date.year == date.year))
		{
			return i;
		}
	}
	return-1;
}

void inputTimeCode( const vector< AvailSeats > &availSeats, const Date date,
                    int &timeCode, int partySize )
{
	cout << "Choose a time:" << endl;
	char times[5][8] = { "", "11:30", "13:30", "17:45", "19:45" };
	for (int i = 1; i <= 4; i++)
	{
		if (hasAvailableSeats(availSeats, date, i, partySize) == true)//modify
		{
			cout << i << ". " << times[i] << endl;
		}

	}
	int choice2;
	do cout << "?";
	while ((choice2 =inputAnInteger(1, 4))== -1|| (hasAvailableSeats(availSeats,date,choice2, partySize))==false);//modify
	timeCode = choice2;//added
}

void displayReservationInfo( const Reservation &reservation )
{
   cout << reservation.partySize << " guests  ";

   cout << reservation.date.year << "/";

   if( reservation.date.month < 10 )
      cout << '0';
   cout << reservation.date.month << "/";

   if( reservation.date.day < 10 )
      cout << '0';
   cout << reservation.date.day;

   char times[ 5 ][ 8 ] = { "", "11:30", "13:30", "17:45", "19:45" };
   cout << "  " << times[ reservation.time ] << endl;
}

void decreaseAvailSeats( vector< AvailSeats > &availSeats, const Date date,
                         int timeCode, int requiredSeats )
{
   int pos = findAvailSeat( availSeats, date );
   if( pos >= 0 ) // found
      availSeats[ pos ].numAvailSeats[ timeCode ] -= requiredSeats;
}

void viewReservation( const vector< Reservation > &reservations )
{
   if( reservations.size() == 0 )
   {
      cout << "\nNo reservations!\n";
      return;
   }

   char phoneNumber[ 12 ];
   cout << "\nEnter phone Number: ";
   cin >> phoneNumber;
   cin.ignore();

   if( !exist( reservations, phoneNumber ) )
   {
      cout << "\nYou have no reservations!\n";
      return;
   }

   displayReservationInfo( reservations, phoneNumber );
}

bool exist( const vector< Reservation > &reservations, char phoneNumber[] )
{
	for (int i = 0; i < reservations.size(); i++)//modify
	{
		if (strcmp(phoneNumber, reservations[i].phoneNumber)==0)
		{
			return true;
		}
	}
	return false;
		
}

void displayReservationInfo( const vector< Reservation > &reservations,
                             char phoneNumber[] )
{
   cout << endl;
   int count = 0;
   for( size_t i = 0; i < reservations.size(); ++i )
      if( strcmp( reservations[ i ].phoneNumber, phoneNumber ) == 0 )
      {
         cout << setw( 2 ) << ++count << ". ";
         displayReservationInfo( reservations[ i ] );
      }
}

void storeReservations( vector< Reservation > &reservations )
{
	ofstream outReFile;
	outReFile.open("Reservations.dat", ios::binary);
	if (!outReFile)
	{
		cout << "File coule not be opened" << endl;
		system("pause");
		exit(1);
	}
	for (int i = 0; i < reservations.size(); i++)
	{
		outReFile.write(reinterpret_cast<const char*>(&reservations[i]), sizeof(Reservation));
	}
	outReFile.close();

}

void storeAvailSeats( vector< AvailSeats > &availSeats )
{
	ofstream outAvaFile;
	outAvaFile.open("AvailSeats.dat", ios::binary);
	if (!outAvaFile)
	{
		cout << "File coule not be opened" << endl;
		system("pause");
		exit(1);
	}

	for (int i = 0; i < availSeats.size(); i++)
	{
		outAvaFile.write(reinterpret_cast<const char*>(&availSeats[i]), sizeof(AvailSeats));
	}
	outAvaFile.close();

}