#include <iostream>
#include <cstring>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

// macros
#define BUFFER_SIZE 100

void clearScreen(void) {
    #ifdef _WIN32
        system("cls");
    #else   
        system("clear");
    #endif
}

// prototypes
void displayMenu();
void displayBar();
void write();
void read();
void deleteNote();
void setPassword();
void checkPassword(string);

// global variables
string pass_list, usr_data[BUFFER_SIZE], current_Time;
int looptime = 0;

int main()
{
    string inputChoice;
    displayMenu();
    do
    {
        // displaying options of note add write or delete
        displayBar();
        cin >> inputChoice;

        if (inputChoice == "0")
        {
            write();
        }
        else if (inputChoice == "1")
        {
            read();
        }
        else if (inputChoice == "2")
        {
            deleteNote();
        }
        else if (inputChoice == "-1")
        {
            cout << "\n\t HAVE A GOOD DAY :)" << endl;
        }
        else
        {
            cout << "\n( Enter  a valid number! )" << endl;
        }

    } while (inputChoice != "-1");
}

// functions
void setPassword()
{
    string pass, conf_pass;
    cout << "\n\n---------------------------------------------------------------------------\n  ==> Set a password\n  ==> To encrypt it from other users\n  ==> Set atleast 4 digit password\n\n---------------------------------------------------------------------------" << endl;
    cout << "First Create your Password!\nNew Password:     ";
    cin.ignore();
    getline(cin, pass);

    do
    {
        cout << "Confirm password: ";
        getline(cin, conf_pass);
    } while (conf_pass != pass);

    cout << "\n\t( Your password is successfully created! )" << endl;
    pass_list = pass; // password is copying password list
}

// this function is for confirming | checking a password in password list
void checkPassword(string pass)
{
    if (pass != pass_list)
    {
        cout << "\nTry again: ";
        cin >> pass;
        checkPassword(pass);
    }
    else
    {
        cout << "\n\t( Your password is Correct! )" << endl;
    }
}

// this function for displaying title
void displayMenu()
{
    cout << "----------------------------------------------------------------------------\n\t\t\tDIGITAL-DIARY-PROJECT\n----------------------------------------------------------------------------\n";
}

void displayBar()
{
    // displaying
    cout << "\n\nInput_Taking:\n\t\t0: for write your Diary\n\t\t1: for Read your Diary\n\t\t2: for delete your Diary\n\n(-1 for exit): ";
}

void write()
{
    string yesNo;
    time_t currentTime = time(nullptr);
    string timeString = ctime(&currentTime);
    current_Time = timeString;
    if (pass_list.empty())
    {
        setPassword();
        clearScreen();
        cout << "\n---------------------------- Write below --------------------------------\n"
             << endl
             << "[Enter '#' to exit!]"
             << "   Date & Time:  " << current_Time << endl;
        cin.ignore();
        string tempData;
        while (tempData != "#")
        {
            cin >> tempData;
            usr_data[looptime] = tempData;
            looptime++;
        }
        clearScreen();
        cout << "\n----------------------- Successfully Created! ----------------------------\n"
             << endl
             << endl;
    }
    else
    {
        cout << "\nThere is exisiting Data available!\nDo you want to delete that (y/n): ";
        cin >> yesNo;
        if (yesNo == "y" || yesNo == "Y")
        {
            pass_list.clear();
            write();
        }
        else if (yesNo == "n" || yesNo == "N")
        {
            return;
        }
        else
        {
            write();
        }
    }
}

// this function is for reading a note
void read()
{
    string password;
    if (!pass_list.empty())
    {
        cout << "\n\nEnter your password: ";
        cin >> password;
        checkPassword(password);
        cout << endl
             << "---------------------------- READ-YOUR-DIARY-BELOW ------------------------\n\n"
             << "Date & Time:  " << current_Time << endl;
        cin.ignore();
        for (int i = 0; i < looptime; i++)
        {
            if (usr_data[i] == "\n")
            {
                cout << endl;
            }
            else if (usr_data[i] == "\0")
            {
                cout << " ";
            }
            else
            {
                cout << usr_data[i] << " ";
            }
        }

        cout << "\n\n-------------------------------- [ :) ] -----------------------------------" << endl;
    }
    else
    {
        cout << endl
             << "\t( You haven't wrote any Diary! )\n\n";
    }
}

// this function is for deleting a note
void deleteNote()
{
    string password, conf_password;
    if (pass_list.empty())
    {
        cout << endl
             << "\t( You haven't wrote any Diary! )\n"
             << endl;
    }

    else
    {
        cout << "Confirm your password: ";
        cin >> password;
        if (password != pass_list)
        {
            deleteNote();
        }
        else
        {

            cout << "\nAre you sure (y/n)?: ";
            cin >> conf_password;
            if (conf_password == "y" || conf_password == "Y")
            {
                pass_list.clear();
                cout << "\n\t( Your Data has been Deleted! )" << endl;
            }
            else if (conf_password == "n" || conf_password == "N")
            {
                cout << "\n\t( Your Data is Safe & Secure! )" << endl;
            }
            else
            {
                cout << "\n\t( It seem's like you don't want to delete! )" << endl;
            }
        }
    }
}
