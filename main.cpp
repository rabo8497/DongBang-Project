#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <string>
#include "items/ItemManager.h"
#include "items/Account.h"
#include "items/Calendar.h"
#include "users/User.h"
#include "users/UserManager.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

using namespace std;

const string version = "0.0.1";
const int totalWidth = 40;
const int choiceInterval = 2;

int firstPage() {
    int answer;
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;
    cout << setfill(' ');
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth-choiceInterval-1) << left << "1) login" << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth-choiceInterval-1) << left << "2) signup" << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth-choiceInterval-1) << left << "3) exit" << "" << "|" << endl;
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;
    cout << setfill(' ');
    cout << "You : ";
    cin >> answer;
    return answer;
}
void signUpPage(UserManager& um_reference) {
    int studentnumber;
    string nickname;
    string password;
    cout << endl << "what is your student number? : ";
    cin >> studentnumber;
    cout << "what is your user nickname? : ";
    cin >> nickname;
    cout << "what is your user password? : ";
    cin >> password;
    cout << endl;
    um_reference.signUp(studentnumber, nickname, password, false, false);
}
void logInPage(UserManager& um_reference) {
    string nickname;
    string password;
    cout << endl << "enter your nickname : ";
    cin >> nickname;
    cout << "enter your password : ";
    cin >> password;
    cout << endl;
    um_reference.signIn(nickname, password);
}
int secondPage() {
    int answer;
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;
    cout << setfill(' ');
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth-choiceInterval-1) << left << "1) Book-related function" << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth-choiceInterval-1) << left << "2) public account-related function" << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth-choiceInterval-1) << left << "3) Reservation of Items" << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth-choiceInterval-1) << left << "4) back" << "|" << endl;
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;
    cout << setfill(' ');
    cout << "You : ";
    cin >> answer;
    return answer;
}

int main(int argc, char *argv[])
{
    UserManager UM;
    int choice;
    bool isProgramEnd = false;
    while (!isProgramEnd) {
        if (!UM.getIsSignIn()) {
            choice = firstPage();
            switch (choice)
            {
                case 1 :
                    logInPage(UM);
                    break;
                case 2 :
                    signUpPage(UM);
                    break;
                case 3 :
                    isProgramEnd = true;
                    break;
                default :
                    cout << RED << "wrong value. choose other number." << RESET << endl;
            }
        }
    }
}
