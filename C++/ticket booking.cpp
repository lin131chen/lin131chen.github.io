#include <iostream>
#include <fstream>
using namespace::std;

struct Member
{
   char email[ 40 ];
   char password[ 24 ];
   char IDNumber[ 12 ];
   char name[ 12 ];
   char phone[ 12 ];
};

void loadMemberInfo( ifstream &inMemberFile, Member memberDetails[], int &numMembers );

// input an integer from the keyboard, and
// returns the integer if it belongs to [ begin, end ], returns -1 otherwise.
int inputAnInteger( int begin, int end );

void login( Member memberDetails[], int numMembers );

// returns true if there is a member
// whose email and password are equal to the specified email and password, respectively
bool legal( char email[], char password[], Member memberDetails[], int numMembers, int &recordNumber );

void accountInfor(Member memberDetails[], int numMembers, int recordNumber);

void newMember( Member memberDetails[], int &numMembers );

// returns true if there is a member whose IDNumber is equal to newIDNumber
bool existingID( char newIDNumber[], Member memberDetails[], int &numMembers );

// returns true if there is a member whose email is equal to newEmail
bool existingEmail( char newEmail[], Member memberDetails[], int &numMembers );

void saveMemberInfo( ofstream &outMemberFile, Member memberDetails[], int numMembers );

int main()
{
   Member memberDetails[ 100 ] = { "", "", "", "", "" };
   int numMembers = 0;

   ifstream inMemberFile;
   ofstream outMemberFile;

   loadMemberInfo( inMemberFile, memberDetails, numMembers );

   cout << "Welcome to Vieshow Cinemas member system\n\n";

   int choice;

   while( true )
   {
      cout << "Enter your choice:" << endl;
      cout << "1. Sign In\n";
      cout << "2. New Member\n";
      cout << "3. Sign Out\n? ";

      choice = inputAnInteger( 1, 3 );
      cout << endl;

      switch( choice )
      {
      case 1:
         login( memberDetails, numMembers );
         break;

      case 2:
         newMember( memberDetails, numMembers );
         break;

      case 3:
         saveMemberInfo( outMemberFile, memberDetails, numMembers );
         cout << "Thank you...\n\n";
         system( "pause" );
         return 0;

      default:
         cout << "Input Error!\n\n";
         break;
      }
   }

   system( "pause" );
}
int inputAnInteger(int begin, int end)
{
    int y;
    cin >> y;
    if (y >= begin && y <= end)
    {
        return y;
    }
    else
        return -1;
}
void loadMemberInfo(ifstream& inMemberFile, Member memberDetails[], int& numMembers)
{
    inMemberFile.open("MemberInfo.dat", ios::binary);
    if (!inMemberFile)
    {
        cout << "File could not be opened" << endl;
        system("pause");
        exit(1);
    }
    while (inMemberFile >> memberDetails[numMembers].name >> memberDetails[numMembers].email >> memberDetails[numMembers].phone >> memberDetails[numMembers].IDNumber >> memberDetails[numMembers].password)
    {
        numMembers++;
    }
   
    inMemberFile.close();
}
void login(Member memberDetails[], int numMembers)
{
    char email[40];
    char password[24];
    cout << "Enter email address:" ;
    cin >> email;
    cout << "Enter password:" ;
    cin >> password;
    int recordNumber;
    if (legal(email, password, memberDetails, numMembers, recordNumber) == false)
    {
        cout << "Sorry, unrecognized email or password." << endl;
        login(memberDetails, numMembers);
    }
    else
    {
        int choice;

        while (true)
        {
            cout << "Enter your choice:" << endl;
            cout << "1. Account Information\n";
            cout << "2. Buy Tickets\n";
            cout << "3. End\n? ";

            choice = inputAnInteger(1, 3);
            cout << endl;

            switch (choice)
            {
            case 1:
                accountInfor(memberDetails, numMembers, recordNumber);
                break;

            case 2:
                break;

            case 3:
                return;

            default:
                cout << "Input Error!\n\n";
                break;
            }
        }

        system("pause");
    }
    
}
bool legal(char email[], char password[], Member memberDetails[], int numMembers, int& recordNumber)
{
    for (recordNumber = 0; recordNumber < numMembers; recordNumber++)
    {
        if ((strcmp(memberDetails[recordNumber].email, email) == 0) && (strcmp(memberDetails[recordNumber].password, password) == 0))
        {
            return true;
        }
    }
    return false;
}
void accountInfor(Member memberDetails[], int numMembers, int recordNumber)
{
    cout << "1. Name: " << memberDetails[recordNumber].name << endl;
    cout << "2. Email Address:" << memberDetails[recordNumber].email << endl;
    cout << "3. Phone Number: " << memberDetails[recordNumber].phone << endl;
    cout << "4. ID Number: " << memberDetails[recordNumber].IDNumber << endl;
    cout << "5. Password: " << memberDetails[recordNumber].password << endl;
    cout << "Which one do you want to modify(0 ¡V not modify) ?" ;
    int choice;
    while (true)
    {
        choice = inputAnInteger(0, 5);

        switch (choice)
        {
        case 0:
            break;
        case 1:
            cout << "Name:" ;
            cin >> memberDetails[recordNumber].name;
            break;

        case 2:
            cout << "Email Address:" ;
            cin >> memberDetails[recordNumber].email;
            break;

        case 3:
            cout << "Phone Number:" ;
            cin >> memberDetails[recordNumber].phone;
            break;
        case 4:
            cout << "ID Number:" ;
            cin >> memberDetails[recordNumber].IDNumber;
            break;

        case 5:
            cout << "Password:" ;
            cin >> memberDetails[recordNumber].password;
            break;
        default:
            cout << "Input Error!\n\n";
            break;
        }
        return;
    }
    
}
void newMember(Member memberDetails[], int& numMembers)
{
    char IDNumber[12];
    char  email[40];
    cout << "Enter your ID number:" ;
    cin >> IDNumber;
    cout << "Enter your Email:" ;
    cin >> email;

    if (existingID(IDNumber, memberDetails, numMembers) == true)
    {
        cout << "An account already exists with the ID number!" << endl;
        return;
    }
    int i = 0;
    for (; IDNumber[i] != '\0'; i++)
    {
        memberDetails[numMembers].IDNumber[i] = IDNumber[i];
    }
    memberDetails[numMembers].IDNumber[i] = '\0';
    if (existingEmail(email, memberDetails, numMembers) == true)
    {
        cout << "An account already exists with the Email!" << endl;
        return;
    }
    for ( i = 0; IDNumber[i] != '\0'; i++)
    {
        memberDetails[numMembers].email[i] = email[i];
    }
    memberDetails[numMembers].email[i] = '\0';
    
    cout << "Enter your password:";
    cin >> memberDetails[numMembers].password;
    cout << "Enter your name:";
    cin >> memberDetails[numMembers].name;
    cout << "Enter your phone:";
    cin >> memberDetails[numMembers].phone;
    cout << "successful!!" << endl;
    numMembers++;
}
bool existingID(char newIDNumber[], Member memberDetails[], int& numMembers)
{
    for (int i = 0; i < numMembers; i++)
    {
        if (strcmp(memberDetails[numMembers].IDNumber, newIDNumber) == 0)
        {
            return true;
        }
    }
    return false;
    
}
bool existingEmail(char newEmail[], Member memberDetails[], int& numMembers)
{
    for (int i = 0; i < numMembers; i++)
    {
        if (strcmp(memberDetails[i].email, newEmail) == 0)
        {
            return true;
        }
    }
    return false;
}
void saveMemberInfo(ofstream& outMemberFile, Member memberDetails[], int numMembers)
{
    outMemberFile.open("MemberInfo.dat", ios::binary);
    if (!outMemberFile)
    {
        cout << "File could not be open" << endl;
        system("pause");
        exit(1);
    }
    for (int i = 0; i < numMembers; i++)
    {
        outMemberFile << memberDetails[i].name <<" "<< memberDetails[i].email <<" "<< memberDetails[i].phone <<" "<< memberDetails[i].IDNumber <<" "<< memberDetails[i].password;
    }
    outMemberFile.close();
}