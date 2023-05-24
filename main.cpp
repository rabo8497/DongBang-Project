#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <string>
#include "books/Book.h"
#include "books/BookManager.h"
#include "items/ItemManager.h"
#include "items/Account.h"
#include "items/Calendar.h"
#include "users/User.h"
#include "users/UserManager.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

using namespace std;

const string version = "0.0.1";
const int totalWidth = 40;
const int choiceInterval = 2;

int firstPage()
{
    int answer;
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;
    cout << setfill(' ');
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "1) login"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "2) signup"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "0) exit"
         << ""
         << "|" << endl;
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;
    cout << setfill(' ');
    cout << "You : ";
    cin >> answer;
    return answer;
}
void signUpPage(UserManager &um_reference)
{
    string studentnumber;
    string nickname;
    string password;
    cout << endl
         << "what is your student number? : ";
    cin >> studentnumber;
    for (char ch : studentnumber)
    {
        if (!std::isdigit(ch))
        {
            cerr << RED << endl
                 << "student number must be integer" << RESET << endl
                 << endl;
            return;
        }
    }
    cout << "what is your user nickname? : ";
    cin >> nickname;
    cout << "what is your user password? : ";
    cin >> password;
    cout << endl;
    int studentnumberInteger = stoi(studentnumber);
    um_reference.signUp(studentnumberInteger, nickname, password, false, false);
}
void logInPage(UserManager &um_reference)
{
    string nickname;
    string password;
    cout << endl
         << "enter your nickname : ";
    cin >> nickname;
    cout << "enter your password : ";
    cin >> password;
    cout << endl;
    um_reference.signIn(nickname, password);
}
int secondPage()
{
    int answer;
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;
    cout << setfill(' ');
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "1) Book-related function"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "2) public account-related function"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "3) Reservation of Items"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "0) exit"
         << "|" << endl;
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;
    cout << setfill(' ');
    cout << "You : ";
    cin >> answer;
    cout << endl;
    return answer;
}
int bookRelatedPage(UserManager &um_reference)
{
    int answer;
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;
    cout << setfill(' ');
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "1) book info"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "2) book return"
         << "|" << endl;
    if (um_reference.getLoginedUser().getIsManager())
        cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "3) book management"
             << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "0) back"
         << "|" << endl;
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;
    cout << setfill(' ');
    cout << "You : ";
    cin >> answer;
    cout << endl;
    return answer;
}
int bookInfoPage(BookManager &bm_reference, vector<vector<string>> search, int listpage)
{
    int answer;
    const int totalWidth = 78;
    bm_reference.booklist(listpage, search);
    cout << setfill(' ');
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "1) search by keyword"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "2) book borrow"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "3) next page"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "4) previous page"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "0) back"
         << "|" << endl;
    cout << left << setfill('-') << setw(totalWidth - 1) << "" << endl;
    cout << setfill(' ');
    cout << "You : ";
    cin >> answer;
    cout << endl;
    return answer;
}

int main(int argc, char *argv[])
{
    UserManager UM;
    BookManager BM;
    vector<vector<string>> search = BM.booksearch();
    int listpage = 1;
    int choice;
    int nowPage = 0;
    bool isProgramEnd = false;
    while (!isProgramEnd)
    {
        if (!UM.getIsSignIn())
        {
            choice = firstPage();
            switch (choice)
            {
            case 1:
                logInPage(UM);
                break;
            case 2:
                signUpPage(UM);
                break;
            case 0:
                isProgramEnd = true;
                break;
            default:
                cout << RED << "wrong value. choose other number." << RESET << endl;
            }
        }
        else if (nowPage == 0)
        {
            choice = secondPage();
            switch (choice)
            {
            case 1:
                nowPage = 1;
                break;
            case 2:
                nowPage = 2;
                break;
            case 3:
                nowPage = 3;
                break;
            case 0:
                isProgramEnd = true;
                break;
            default:
                cout << RED << "wrong value. choose other number." << RESET << endl;
            }
        }
        else if (nowPage == 1)
        {
            choice = bookRelatedPage(UM);
            switch (choice)
            {
            case 0:
                nowPage = 0;
                break;
            case 1:
                nowPage = 11;
                break;
            case 2:
                
            default:
                cout << RED << "wrong value. choose other number." << RESET << endl;
            }
        }
        else if (nowPage == 11)
        {
            string keyword = "";
            int booknumber;
            choice = bookInfoPage(BM, search, listpage);

            switch (choice)
            {
            case 0:
                nowPage = 1;
                listpage = 1;
                search = BM.booksearch();
                break;
            case 1:
                cout << "enter the keyword :";
                cin >> keyword;
                search = BM.booksearch(keyword);
                listpage = 1;
                break;
            case 2:
                cout << "enter the book number : ";
                cin >> booknumber;
                BM.booklend(UM.getLoginedUser(), stoi(search[booknumber - 1][1]));
                UM.modifyFile();
                break;
            case 3:
                if (listpage >= search.size() / 5 + 1)
                {
                    cout << RED << "you are watching last page." << RESET << endl;
                    break;
                }
                listpage++;
                break;
            case 4:
                if (listpage == 1)
                {
                    cout << RED << "you are watching 1st page." << RESET << endl;
                    break;
                }
                listpage--;
                break;
            default:
                cout << RED << "wrong value. choose other number." << RESET << endl;
            }
        }
    }
}
