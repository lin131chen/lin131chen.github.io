#include <iostream>
#include <iomanip>
#include <fstream>
using namespace::std;

struct MemberRecord
{
	char email[40];
	char password[24];
	char IDNumber[12];
	char name[12];
	char phone[12];
};

struct Movie
{
	int movieCode;
	int prices[4]; // prices[0]:adult, prices[1]:concession, prices[2]:disability, prices[3]:elderly
	bool dates[9]; // dates[i] is true if and only if the movie is available on i-th date
	bool sessionTimes[17]; // sessionTimes[i] is true if and only if the movie is available on i-th session
	bool occupiedSeats[9][17][8][12]; // occupiedSeats[i][j] is the occupied Seats for all accounts
};                                           // at j-th session time on i-th date

struct BookingInfo
{
	char email[40];
	int movieCode;
	int dateCode;
	int sessionTimeCode;
	int numTickets[4]; // numTickets[0]: the number of adult tickets,
						 // numTickets[1]: the number of concession tickets,
						 // numTickets[2]: the number of disability tickets,
						 // numTickets[3]: the number of elderly tickets
	char seletedSeats[24][4]; // seleted seats for the user with the specified email
};

char hours[17][8] = { "09:00", "10:00", "11:00", "12:00", "13:00", "14:00", "15:00", "16:00", "17:00",
						  "18:00", "19:00", "20:00", "21:00", "22:00", "23:00", "00:00", "01:00" };

void loadMemberInfo(MemberRecord memberDetails[], int& numMembers);
void loadBookingHistories(BookingInfo bookingHistories[], int& numBookings);
void loadMovies(Movie movies[], int& numMovies);
void loadMovieNames(char movieNames[][60], int numMovies);
void loadAvailableDates(char availableDates[][12], int& numDates);

int inputAnInteger(int begin, int end);
void signIn(MemberRecord memberDetails[], int numMembers, Movie movies[], char movieNames[][60], int numMovies,
	BookingInfo bookingHistories[], int& numBookings, char availableDates[][12], int numDates);
bool illegal(char email[], char password[], MemberRecord memberDetails[], int numMembers, int& recordNumber);
void accountInfor(MemberRecord memberDetails[], int numMembers, int recordNumber);

void buyTickets(BookingInfo bookingHistories[], int& numBookings, Movie movies[], char movieNames[][60],
	int numMovies, char availableDates[][12], int numDates, char email[]);
void selectSeats(BookingInfo bookingHistories[], int numBookings, Movie movies[]);

void displaySessionTimes(Movie movies[], char movieNames[][60], int numMovies,
	char availableDates[][12], int numDates);
void display(Movie movies[], BookingInfo bookingHistory);
void displayBookingHistory(BookingInfo bookingHistories[], int numBookings, Movie movies[],
	char movieNames[][60], char availableDates[][12], char email[]);

void newMember(MemberRecord memberDetails[], int& numMembers);
bool existingID(char newIDNumber[], MemberRecord memberDetails[], int& numMembers);
bool existingEmail(char newEmail[], MemberRecord memberDetails[], int& numMembers);

void saveMemberInfo(MemberRecord memberDetails[], int numMembers);
void saveMovies(Movie movies[], int numMovies);
void saveBookingHistories(BookingInfo bookingHistories[], int numBookings);

int main()
{
	MemberRecord memberDetails[100] = {};
	int numMembers = 0;
	loadMemberInfo(memberDetails, numMembers);

	BookingInfo bookingHistories[1000] = {};
	int numBookings = 0;
	loadBookingHistories(bookingHistories, numBookings);

	Movie movies[30] = {};
	int numMovies = 0;
	loadMovies(movies, numMovies);

	char movieNames[30][60] = {};
	loadMovieNames(movieNames, numMovies);

	char availableDates[10][12];
	int numDates;
	loadAvailableDates(availableDates, numDates);

	cout << "Welcome to Vieshow Cinemas Taipei QSquare system\n";

	int choice;

	while (true)
	{
		cout << "\n1. Sign In\n";
		cout << "2. New Member\n";
		cout << "3. End\n";

		do cout << "\nEnter your choice (1~3): ";
		while ((choice = inputAnInteger(1, 3)) == -1);
		cout << endl;

		switch (choice)
		{
		case 1:
			signIn(memberDetails, numMembers, movies, movieNames, numMovies,
				bookingHistories, numBookings, availableDates, numDates);
			break;

		case 2:
			newMember(memberDetails, numMembers);
			break;

		case 3:
			saveMemberInfo(memberDetails, numMembers);
			saveMovies(movies, numMovies);
			saveBookingHistories(bookingHistories, numBookings);
			cout << "Thank you...\n\n";
			system("pause");
			return 0;

		default:
			cout << "Input Error!\n\n";
			break;
		}
	}

	system("pause");
}
void loadMemberInfo(MemberRecord memberDetails[], int& numMembers)
{
	ifstream inMemberfile;
	inMemberfile.open("Member Info.dat", ios::binary);
	if (!inMemberfile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}
	while (inMemberfile.read(reinterpret_cast<char*>(&memberDetails[numMembers]), sizeof(MemberRecord)))
	{
		numMembers++;
	}

	inMemberfile.close();
}
void loadBookingHistories(BookingInfo bookingHistories[], int& numBookings)
{
	ifstream inBookfile;
	inBookfile.open("Booking Histories.dat", ios::binary);
	if (!inBookfile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}
	numBookings = 0;
	while (inBookfile.read(reinterpret_cast<char*>(&bookingHistories[numBookings]), sizeof(BookingInfo)))
	{
		numBookings++;
	}
	inBookfile.close();
}
void loadMovies(Movie movies[], int& numMovies)
{
	ifstream inMoviefile;
	inMoviefile.open("Movies.dat", ios::binary);
	if (!inMoviefile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);

	}
	while (inMoviefile.read(reinterpret_cast<char*>(&movies[numMovies]), sizeof(Movie)))
	{
		numMovies++;
	}
	inMoviefile.close();
}
void loadMovieNames(char movieNames[][60], int numMovies)
{
	ifstream inMovieNamefile("Movie Names.txt", ios::in);
	if (!inMovieNamefile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}
	for (int i = 0; i < numMovies; i++)
	{
		inMovieNamefile.getline(movieNames[i], 60);
	}
	inMovieNamefile.close();
}

void loadAvailableDates(char availableDates[][12], int& numDates)
{
	ifstream inAvailablefile("Available Dates.txt", ios::in);
	if (!inAvailablefile)
	{
		cout << "File could not be opened" << endl;
		system("pause");
		exit(1);
	}
	numDates = 0;
	while (inAvailablefile.getline(availableDates[numDates], 12))
	{
		numDates++;
	}
	inAvailablefile.close();
}
int inputAnInteger(int begin, int end)
{
	char y[100];
	cin.getline(y, 100);
	for (int i = 0; y[i] != '\0'; i++)
	{
		if (!isdigit(y[i]) || strlen(y) > 2)
		{
			return -1;
		}
	}
	if (y[0] == '\0')
	{
		return -1;
	}
	int num = atoi(y);
	if (num >= begin && num <= end)
	{
		return num;
	}
	else
		return -1;
}
void signIn(MemberRecord memberDetails[], int numMembers, Movie movies[], char movieNames[][60], int numMovies,
	BookingInfo bookingHistories[], int& numBookings, char availableDates[][12], int numDates)
{
	char email[40];
	char password[24];
	cout << "Enter email address:";
	cin >> email;
	cout << "Enter password :";
	cin >> password;
	int recordNumber;
	if (illegal(email, password, memberDetails, numMembers, recordNumber) == true)
	{
		return;
	}
	int choice;
	while (true)
	{
		cout << "\n1. Account Information\n";
		cout << "2. Buy Ticket\n";
		cout << "3. My Booking\n";
		cout << "4. Sign out\n";

		do cout << "\nEnter your choice (1~4): ";
		while ((choice = inputAnInteger(1, 4)) == -1);
		cout << endl;
		switch (choice)
		{
		case 1:
			accountInfor(memberDetails, numMembers, recordNumber);
			break;

		case 2:
			buyTickets(bookingHistories, numBookings, movies, movieNames, numMovies, availableDates, numDates, email);
			break;

		case 3:
			displayBookingHistory(bookingHistories, numBookings, movies, movieNames, availableDates, email);
			break;
		case 4:
			return;

		default:
			cout << "Input Error!\n\n";
			break;
		}
	}

}
bool illegal(char email[], char password[], MemberRecord memberDetails[], int numMembers, int& recordNumber)
{
	for (recordNumber = 0; recordNumber < numMembers; recordNumber++)
	{
		if (strcmp(email, memberDetails[recordNumber].email) == 0 && strcmp(password, memberDetails[recordNumber].password) == 0)
		{
			cin.ignore();
			return false;

		}
	}
	cout << "Sorry, unrecognized email or password." << endl;
	cin.ignore();
	return true;
}
void accountInfor(MemberRecord memberDetails[], int numMembers, int recordNumber)
{
	cout << "Name: " << memberDetails[recordNumber].name << endl;
	cout << "Email Address: " << memberDetails[recordNumber].email << endl;
	cout << "Phone Number: " << memberDetails[recordNumber].phone << endl;
	cout << "ID Number: " << memberDetails[recordNumber].IDNumber << endl;
	cout << "Password: " << memberDetails[recordNumber].password << endl;
	cout << endl;
	cout << "Which one do you want to modify(0 ¡V not modify) ?";
	cout << endl;
	int choice;
	while (true)
	{
		choice = inputAnInteger(0, 5);

		switch (choice)
		{
		case 0:
			break;
		case 1:
			cout << "Name:";
			cin >> memberDetails[recordNumber].name;
			cin.ignore();
			break;

		case 2:
			cout << "Email Address:";
			cin >> memberDetails[recordNumber].email;
			cin.ignore();
			break;

		case 3:
			cout << "Phone Number:";
			cin >> memberDetails[recordNumber].phone;
			cin.ignore();
			break;
		case 4:
			cout << "ID Number:";
			cin >> memberDetails[recordNumber].IDNumber;
			cin.ignore();
			break;

		case 5:
			cout << "Password:";
			cin >> memberDetails[recordNumber].password;
			cin.ignore();
			break;
		default:
			cout << "Input Error!\n\n";
			cin.ignore();
			break;
		}
		return;
	}
}

void buyTickets(BookingInfo bookingHistories[], int& numBookings, Movie movies[], char movieNames[][60],
	int numMovies, char availableDates[][12], int numDates, char email[])
{
	displaySessionTimes(movies, movieNames, numMovies, availableDates, numDates);
	while (true)
	{
		cout << "Enter movie code(0 - 11) :";
		int choice1;
		choice1 = inputAnInteger(0, 11);
		cout << endl;
		switch (choice1)
		{
		case -1:
			break;
		default:
			int k = 0;
			for (; k < numMovies; k++)
			{
				if (choice1 == movies[k].movieCode)
				{
					break;

				}
			}
			while (true)
			{
				cout << "Enter date code (0 - 8):";
				int choice2;
				choice2 = inputAnInteger(0, 8);
				cout << endl;
				switch (choice2)
				{
				case -1:
					break;
				default:
					if (movies[choice1].dates[choice2] == 0)
					{
						continue;
					}
					while (true)
					{
						cout << "Enter session time code (0 - 16):";
						int choice3;
						choice3 = inputAnInteger(0, 16);
						cout << endl;
						switch (choice3)
						{
						case -1:
							break;
						default:
							if (movies[choice1].sessionTimes[choice3] == 0)
							{
								continue;
							}
							else
							{
								cout << "Movie:" << movieNames[choice1] << endl;
								cout << "Date:" << availableDates[choice2] << endl;
								cout << "Show time:" << hours[choice3] << endl;

							}
							cout << "Price:" << "Adult-" << movies[choice1].prices[0] << ", " << "Concession-" << movies[choice1].prices[1] << ", " << "Disability-" << movies[choice1].prices[2] << ", " << "Elderly-" << movies[choice1].prices[3] << endl;
						reinput:
							{
								while (true)
								{
									cout << endl;
									cout << "Enter the number of adult tickets(0 - 6) :";
									int choice4;
									choice4 = inputAnInteger(0, 6);
									cout << endl;
									switch (choice4)
									{
									case -1:
										break;
									default:
										while (true)
										{
											cout << endl;
											cout << "Enter the number of concession tickets(0 - 6): ";
											int choice5;
											choice5 = inputAnInteger(0, 6);
											cout << endl;
											switch (choice5)
											{
											case -1:
												break;
											default:
												while (true)
												{
													cout << endl;
													cout << "Enter the number of  disability tickets(0 - 6): ";
													int choice6;
													choice6 = inputAnInteger(0, 6);
													cout << endl;
													switch (choice6)
													{
													case-1:
														break;
													default:
														while (true)
														{
															cout << endl;
															cout << "Enter the number of elderly tickets (0 - 6): ";
															int choice7;
															choice7 = inputAnInteger(0, 6);
															cout << endl;
															switch (choice7)
															{
															case-1:
																break;
															default:
																bookingHistories[numBookings].numTickets[0] = choice4;
																bookingHistories[numBookings].numTickets[1] = choice5;
																bookingHistories[numBookings].numTickets[2] = choice6;
																bookingHistories[numBookings].numTickets[3] = choice7;
																if (bookingHistories[numBookings].numTickets[0] + bookingHistories[numBookings].numTickets[1] + bookingHistories[numBookings].numTickets[2] + bookingHistories[numBookings].numTickets[3] == 0)
																{
																	goto reinput;
																}
																bookingHistories[numBookings].movieCode = choice1;
																bookingHistories[numBookings].dateCode = choice2;
																bookingHistories[numBookings].sessionTimeCode = choice3;
																strcpy_s(bookingHistories[numBookings].email, email);
																display(movies, bookingHistories[numBookings]);
																selectSeats(bookingHistories, numBookings, movies);
																numBookings++;
																return;

															}
														}
													}
												}

											}
										}
									}
								}
							}

						}
					}
				}
			}
		}
	}
}
void selectSeats(BookingInfo bookingHistories[], int numBookings, Movie movies[])
{
	cout << "  A B C D E F G H I J K L" << endl;
	for (int i = 0; i <= 7; i++)
	{
		cout << i << " ";
		for (int k = 0; k <= 11; k++)
		{
			cout << movies[bookingHistories[numBookings].movieCode].occupiedSeats[bookingHistories[numBookings].dateCode][bookingHistories[numBookings].sessionTimeCode][i][k] << " ";
		}
		cout << endl;
	}
	cout << endl;
	int total = bookingHistories[numBookings].numTickets[0] + bookingHistories[numBookings].numTickets[1] + bookingHistories[numBookings].numTickets[2] + bookingHistories[numBookings].numTickets[3];
	cout << "Select " << total << " seats(e.g. 0A) :" << endl;
	int i = 0;
	while (i < total)
	{
		cout << "?";
		char x[3];
		cin >> x;
		int y[3];
		y[0] = x[0] - '0';
		y[1] = x[1] - 'A';
		if ((y[0] >= 0 && y[0] <= 7) && (y[1] >= 0 && y[1] <= 11)&& movies[bookingHistories[numBookings].movieCode].occupiedSeats[bookingHistories[numBookings].dateCode][bookingHistories[numBookings].sessionTimeCode][y[0]][y[1]]==0)
		{
			movies[bookingHistories[numBookings].movieCode].occupiedSeats[bookingHistories[numBookings].dateCode][bookingHistories[numBookings].sessionTimeCode][y[0]][y[1]] = 1;
			bookingHistories[numBookings].seletedSeats[i][0] = x[0];
			bookingHistories[numBookings].seletedSeats[i][1] = x[1];
			i++;
		}
		else
		{
			cout << endl;
			cout << "This seat bas been occupied.Please select another seat."<<endl;
			continue;
		}

	}
	cin.ignore();
}
void displaySessionTimes(Movie movies[], char movieNames[][60], int numMovies,
	char availableDates[][12], int numDates)
{
	for (int i = 0; i < numMovies; i++)
	{
		cout << i << "." << "Movie :" << movieNames[i] << endl;
		cout << "   " << "Date :  ";
		int k = 0;
		while (k < numDates)
		{
			if (movies[i].dates[k] == 0)
			{
				k++;
			}
			else
			{
				cout << k << "." << availableDates[k] << ",   ";
				k++;
			}
		}
		cout << endl;
		cout << "   " << "Session Time : ";
		int j = 0;
		while (j <= 17)
		{
			if (movies[i].sessionTimes[j] == 0)
			{
				j++;
			}
			else
			{
				cout << j << "." << hours[j] << ",  ";
				j++;
			}
		}
		cout << endl;
		cout << endl;
	}
}
void display(Movie movies[], BookingInfo bookingHistory)
{
	int a, b, c, d;
	a = bookingHistory.numTickets[0] * movies[bookingHistory.movieCode].prices[0];
	b = bookingHistory.numTickets[1] * movies[bookingHistory.movieCode].prices[1];
	c = bookingHistory.numTickets[2] * movies[bookingHistory.movieCode].prices[2];
	d = bookingHistory.numTickets[3] * movies[bookingHistory.movieCode].prices[3];
	cout << "             No. of Tickets  Price  Subtotal" << endl;
	if (bookingHistory.numTickets[0] != 0)
	{
		cout << "Adult  tickets            " << bookingHistory.numTickets[0] << "    " << movies[bookingHistory.movieCode].prices[0] << "       " << a << endl;
	}

	if (bookingHistory.numTickets[1] != 0)
	{
		cout << "concession tickets        " << bookingHistory.numTickets[1] << "    " << movies[bookingHistory.movieCode].prices[1] << "       " << b << endl;
	}
	if (bookingHistory.numTickets[2] != 0)
	{
		cout << "Disability ticket         " << bookingHistory.numTickets[2] << "    " << movies[bookingHistory.movieCode].prices[2] << "       " << c << endl;
	}
	if (bookingHistory.numTickets[3] != 0)
	{
		cout << "elderly tickets           " << bookingHistory.numTickets[3] << "    " << movies[bookingHistory.movieCode].prices[3] << "       " << d << endl;
	}
	cout << endl;
	cout << "Total Amount For Tickets : " << a + b + c + d << endl;
}
void displayBookingHistory(BookingInfo bookingHistories[], int numBookings, Movie movies[],
	char movieNames[][60], char availableDates[][12], char email[])
{
	for (int k = 0; k < numBookings; k++)
	{

		if (strcmp(email, bookingHistories[k].email) == 0)
		{

			cout << "Booking History:" << endl;
			cout << "Movie: " << movieNames[bookingHistories[k].movieCode] << endl;
			cout << "Date: " << availableDates[bookingHistories[k].dateCode] << endl;
			cout << "Show Time: " << hours[bookingHistories[k].sessionTimeCode] << endl;
			cout << "Seats: ";
			for (int i = 0; i < bookingHistories[k].numTickets[0] + bookingHistories[k].numTickets[1] + bookingHistories[k].numTickets[2] + bookingHistories[k].numTickets[3]; i++)
			{
				cout << bookingHistories[k].seletedSeats[i] << " ";
			}
			cout << endl;

		}
		else
		{
			cout << "No bookings!" << endl;
			return;
		}
	}
}
void newMember(MemberRecord memberDetails[], int& numMembers)
{
	char email[40];
	char password[24];
	char IDNumber[12];
	char name[12];
	char phone[12];
	cout << "Enter your ID number :";
	cin >> IDNumber;
	if (existingID(IDNumber, memberDetails, numMembers) == true)
	{
		cout << "An account already exists with the ID number!" << endl;
		return;
	}
	for (int i = 0; IDNumber[i] != '\0'; i++)
	{
		memberDetails[numMembers].IDNumber[i] = IDNumber[i];
	}
	cout << "Enter an email address :";
	cin >> email;
	if (existingEmail(email, memberDetails, numMembers) == true)
	{
		cout << "An account already exists with the e-mail!" << endl;
		return;
	}
	for (int i = 0; email[i] != '\0'; i++)
	{
		memberDetails[numMembers].email[i] = email[i];
	}
	cout << "Enter your name :";
	cin >> memberDetails[numMembers].name;
	cout << "Enter a password :";
	cin >> memberDetails[numMembers].password;
	cout << "Enter your phone number :";
	cin >> memberDetails[numMembers].phone;
	cout << endl;
	cout << "succseeful!" << endl << endl;
	numMembers++;
	cin.ignore();
}
bool existingID(char newIDNumber[], MemberRecord memberDetails[], int& numMembers)
{
	for (int i = 0; i < numMembers; i++)
	{
		if (strcmp(newIDNumber, memberDetails[i].IDNumber) == 0)
		{
			cin.ignore();
			return true;
		}
	}
	return false;

}
bool existingEmail(char newEmail[], MemberRecord memberDetails[], int& numMembers)
{
	for (int i = 0; i < numMembers; i++)
	{
		if (strcmp(newEmail, memberDetails[i].email) == 0)
		{
			cin.ignore();
			return true;
		}
	}
	return false;

}
void saveMemberInfo(MemberRecord memberDetails[], int numMembers)
{
	ofstream outMemberfile;
	outMemberfile.open("Member Info.dat", ios::binary);
	if (!outMemberfile)
	{
		cout << "File could not be opened" << endl;
	}
	for (int i = 0; i < numMembers; i++)
	{
		outMemberfile.write(reinterpret_cast<const char*>(&memberDetails[i]), sizeof(MemberRecord));
	}
	outMemberfile.close();
}
void saveMovies(Movie movies[], int numMovies)
{
	ofstream outMoviesfilel;
	outMoviesfilel.open("Movies.dat", ios::binary);
	if (!outMoviesfilel)
	{
		cout << "File could not be opened" << endl;
	}
	for (int i = 0; i < numMovies; i++)
	{
		outMoviesfilel.write(reinterpret_cast<const char*>(&movies[i]), sizeof(Movie));
	}
}
void saveBookingHistories(BookingInfo bookingHistories[], int numBookings)
{
	ofstream outBookingHfilel;
	outBookingHfilel.open("Booking Histories.dat", ios::binary);
	if (!outBookingHfilel)
	{
		cout << "File could not be opened" << endl;
	}
	for (int i = 0; i < numBookings; i++)
	{
		outBookingHfilel.write(reinterpret_cast<const char*>(&bookingHistories[i]), sizeof(BookingInfo));
	}
}