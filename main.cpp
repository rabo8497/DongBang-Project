#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <string>
#include <conio.h>
#include "logManager.h"
#include "books/Comment.h"
#include "books/Book.h"
#include "books/BookManager.h"
#include "items/ItemManager.h"
#include "items/Account.h"
#include "items/Calendar.h"
#include "users/User.h"
#include "users/UserManager.h"
#include "styles/colors.h"

using namespace std;

const string version = "0.0.1";
const int totalWidth = 40;
const int choiceInterval = 2;
const bool ISSCREEN = false;

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
    cout << " > ";
    cin >> answer;
    return answer;
}
void signUpPage(UserManager &um_reference, bool isScreen = ISSCREEN)
{
    string studentnumber;
    string nickname;
    // string password;
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

    string password;
    if (isScreen)
    {
        char ch;
        while (true)
        {
            ch = getch();
            if (ch == '\r')
            {
                break;
            }
            password += ch;
            cout << "*";
        }
    }
    else
    {
        cin >> password;
    }
    cout << endl;
    int studentnumberInteger = stoi(studentnumber);
    um_reference.signUp(studentnumberInteger, nickname, password, false, false);
}
void logInPage(UserManager &um_reference, bool isScreen = ISSCREEN)
{
    string nickname;
    cout << endl
         << "enter your nickname : ";
    cin >> nickname;
    cout << "enter your password : ";
    string password;
    if (isScreen)
    {
        char ch;
        while (true)
        {
            ch = getch();
            if (ch == '\r')
            {
                break;
            }
            password += ch;
            cout << "*";
        }
    }
    else
    {
        cin >> password;
    }
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
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "4) logout"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "0) exit"
         << "|" << endl;
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;
    cout << setfill(' ');
    cout << " > ";
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
    cout << " > ";
    cin >> answer;
    cout << endl;
    return answer;
}
int bookSearchPage(BookManager &bm_reference, vector<vector<string>> search, int listpage, bool manage)
{
    int answer;
    const int totalWidth = 78;
    bm_reference.booklist(listpage, search);
    if (!manage)
    {
        cout << setfill(' ');
        cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "1) search by keyword"
             << "|" << endl;
        cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "2) book borrow"
             << "|" << endl;
        cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "3) Check book information"
             << "|" << endl;
        cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "4) next page"
             << "|" << endl;
        cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "5) previous page"
             << "|" << endl;
        cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "0) back"
             << "|" << endl;
        cout << left << setfill('-') << setw(totalWidth - 1) << "" << endl;
        cout << setfill(' ');
    }
    else
    {
        cout << setfill(' ');
        cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "1) search by keyword"
             << "|" << endl;
        cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "2) add new book"
             << "|" << endl;
        cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "3) edit book count"
             << "|" << endl;
        cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "4) edit book availability"
             << "|" << endl;
        cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "5) next page"
             << "|" << endl;
        cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "6) previous page"
             << "|" << endl;
        cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 2) << left << "0) back"
             << "|" << endl;
        cout << left << setfill('-') << setw(totalWidth - 1) << "" << endl;
        cout << setfill(' ');
    }
    cout << " > ";
    cin >> answer;
    cout << endl;
    return answer;
}
int bookInfoPage(BookManager &bm_reference, UserManager &um_reference, int booknumber, int &commPage)
{
    int answer;
    int totalWidth = 78;
    bm_reference.load(booknumber);
    bm_reference.getBook().BookInfo();
    if (!bm_reference.getBook().getComment().print_comments(um_reference, commPage))
    {
        if (commPage == 0)
            commPage += 1;
        else
            commPage -= 1;
        bm_reference.getBook().getComment().print_comments(um_reference, commPage);
    }

    cout << setfill(' ');
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "1) Add new comment"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "2) Delete my comment"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "3) next comment page"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "4) previous comment page"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "0) back"
         << "|" << endl;
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;
    cout << " > ";
    cin >> answer;
    cout << endl;
    return answer;
}
int bookLendPage(UserManager &um_reference, BookManager &bm_reference)
{
    int booknumber;
    vector<vector<string>> lendlist;
    if (um_reference.getLoginedUser().getLendBookNum() == 0)
    {
        cout << "You lended no book" << endl;
        return -1;
    }
    lendlist = bm_reference.lendlist(um_reference.getLoginedUser());
    bm_reference.booklist(1, lendlist);
    cout << "enter the book number( back : 0 ) : ";
    cin >> booknumber;
    return booknumber;
}
int bookManagePage()
{
    int answer;

    cout << left << setfill('-') << setw(totalWidth) << "" << endl;
    cout << setfill(' ');
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "1) Add new book"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "2) Edit book count"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "3) Edit book availability"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "0) back"
         << "|" << endl;
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;
    cout << " > ";
    cin >> answer;
    cout << endl;
    return answer;
}
void bookAddPage(BookManager &bm_reference)
{
    string BName, BSeries, BAuthor, BPub, BDate;
    int BCount;
    cout << "Enter the book name : ";
    cin.ignore();
    getline(cin, BName);
    cout << "Enter the book series : ";
    getline(cin, BSeries);
    cout << "Enter the Author name : ";
    getline(cin, BAuthor);
    cout << "Enter the Publisher : ";
    getline(cin, BPub);
    cout << "Enter the published date : ";
    getline(cin, BDate);
    cout << "Enter the book count : ";
    cin >> BCount;

    bm_reference.bookadd(BName, BSeries, BAuthor, BPub, BDate, BCount, true);
}
void bookLendPageFunction(UserManager &um_reference, BookManager &bm_reference, LogManager &lm_reference, int booknumber, int &page)
{
    vector<vector<string>> lendlist;
    if (um_reference.getLoginedUser().getLendBookNum() == 0)
    {
        page = 1;
        return;
    }
    lendlist = bm_reference.lendlist(um_reference.getLoginedUser());
    if (booknumber > lendlist.size())
    {
        cout << RED << "wrong value. choose other number." << RESET << endl;
        return;
    }
    bm_reference.load(stoi(lendlist[booknumber - 1][4]));
    lm_reference.BookReturn(um_reference.getLoginedUser(), bm_reference.getBook());
    bm_reference.bookreturn(um_reference.getLoginedUser(), stoi(lendlist[booknumber - 1][4]), stoi(lendlist[booknumber - 1][1]));
    um_reference.modifyFile();
}
int accountOnOffPage(UserManager &um_reference, ItemManager &im_reference)
{
    int answer;
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;
    cout << setfill(' ');
    im_reference.showList(um_reference.getLoginedUser(), ACCOUNT, true);
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;
    cout << setfill(' ');
    cout << " select account (back : 0) > ";
    cin >> answer;
    return answer;
}
int devicePage(UserManager &um_refernce, ItemManager &im_reference)
{
    cout << setw(totalWidth) << setfill('-') << "" << setfill(' ') << endl;
    im_reference.showList(um_refernce.getLoginedUser(), DEVICE, true);
    cout << setw(totalWidth) << setfill('-') << "" << setfill(' ') << endl;

    int input;
    string ibuffer;
    while (true)
    {
        cout << " select device (back : 0) > ";

        cin >> ibuffer;
        if (!isdigit(ibuffer[0]))
        {
            std::cout << RED << "ERROR : " << RESET << " Your finger is lame" << std::endl;
            continue;
        }
        else
        {
            input = (int)stoi(ibuffer);
            break;
        }
    }
    return input;
}

int main(int argc, char *argv[])
{

    LogManager LM;
    UserManager UM;
    BookManager BM;

    ItemManager IM;
    vector<vector<string>> search = BM.booksearch();
    int listpage = 1;
    int booknumber;
    int choice;
    int nowPage = 0;
    int commPage = 1;
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
                if (UM.getIsSignIn())
                {
                    LM.UserLogin(UM.getLoginedUser());
                }
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
            case 4:
                LM.UserLogout(UM.getLoginedUser());
                UM.signOut();
                break;
            case 0:
                LM.UserLogout(UM.getLoginedUser());
                UM.signOut();
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
                nowPage = 12;
                break;
            case 3:
                nowPage = 13;
                break;
            default:
                cout << RED << "wrong value. choose other number." << RESET << endl;
            }
        }
        else if (nowPage == 11)
        {
            bool manage = false;
            string keyword = "";
            choice = bookSearchPage(BM, search, listpage, manage);

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
                if (booknumber > search.size())
                {
                    cout << RED << "wrong value. choose other number." << RESET << endl;
                    break;
                }

                BM.load(stoi(search[booknumber - 1][1]));
                if (BM.getBook().getIsCanLend() && (UM.getLoginedUser().getLendBookNum() < UM.getLoginedUser().getLendBookMaxNum()))
                {
                    LM.BookLend(UM.getLoginedUser(), BM.getBook());
                }

                BM.booklend(UM.getLoginedUser(), stoi(search[booknumber - 1][1]));
                UM.modifyFile();
                break;
            case 3:
                cout << "enter the book number : ";
                cin >> booknumber;
                if (booknumber > search.size())
                {
                    cout << RED << "wrong value. choose other number." << RESET << endl;
                    break;
                }
                booknumber = stoi(search[booknumber - 1][1]);
                nowPage = 111;
                commPage = 1;
                break;

            case 4:
                if (listpage >= (search.size() - 1) / BM.getBookNumForPage() + 1)
                {
                    cout << RED << "you are watching last page." << RESET << endl;
                    break;
                }
                listpage++;
                break;
            case 5:
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
        else if (nowPage == 111)
        {
            string newComm = "";
            choice = bookInfoPage(BM, UM, booknumber, commPage);

            switch (choice)
            {

            case 0:
                nowPage = 11;
                listpage = 1;
                search = BM.booksearch();
                break;
            case 1:
                cout << "Enter the comment : ";
                cin.ignore();
                getline(cin, newComm);
                if (BM.getBook().getComment().write(UM.getLoginedUser(), newComm))
                    LM.BookComment(UM.getLoginedUser(), BM.getBook());
                break;
            case 2:
                BM.getBook().getComment().deleteFile(UM.getLoginedUser());
                LM.BookRemoveComment(UM.getLoginedUser(), BM.getBook());
                break;
            case 3:
                commPage += 1;
                break;
            case 4:
                commPage -= 1;
                break;
            default:
                cout << RED << "wrong value. choose other number." << RESET << endl;
            }
        }
        else if (nowPage == 12)
        {
            choice = bookLendPage(UM, BM);
            switch (choice)
            {
            case 0:
                nowPage = 1;
                search = BM.booksearch();
                break;
            case -1:
                nowPage = 1;
            default:
                bookLendPageFunction(UM, BM, LM, choice, nowPage);
            }
        }
        else if (nowPage == 13)
        {
            bool manage = true;
            int newCount;
            string keyword = "";
            string newAvail;
            choice = bookSearchPage(BM, search, listpage, manage);

            switch (choice)
            {
            case 0:
                nowPage = 1;
                search = BM.booksearch();
                break;
            case 1:
                cout << "enter the keyword :";
                cin >> keyword;
                search = BM.booksearch(keyword);
                listpage = 1;
                break;
            case 2:
                bookAddPage(BM);
                cout << endl;
                search = BM.booksearch();
                break;
            case 3:

                cout << "enter the book number : ";
                cin >> booknumber;
                cout << "enter the new book count : ";
                cin >> newCount;
                if (booknumber > search.size())
                {
                    cout << RED << "wrong value. choose other number." << RESET << endl;
                    break;
                }
                BM.load(stoi(search[booknumber - 1][1]));
                BM.getBook().setBCount(newCount);
                BM.modifyFile(BM.getBook());
                search = BM.booksearch();
                break;
            case 4:

                cout << "enter the book number : ";
                cin >> booknumber;
                cout << "enter the new book availability (T/F) : ";
                cin >> newAvail;
                if (booknumber > search.size())
                {
                    cout << RED << "wrong value. choose other number." << RESET << endl;
                    break;
                }
                BM.load(stoi(search[booknumber - 1][1]));

                if (newAvail == "T" || newAvail == "t")
                {
                    BM.getBook().setIsCanLend(true);
                }
                else if (newAvail == "F" || newAvail == "f")
                {
                    BM.getBook().setIsCanLend(false);
                }
                else
                {
                    cout << RED << "wrong value. choose other value." << RESET << endl;
                    break;
                }

                BM.modifyFile(BM.getBook());
                search = BM.booksearch();
                break;
            case 5:
                if (listpage >= search.size() / 5 + 1)
                {
                    cout << RED << "you are watching last page." << RESET << endl;
                    break;
                }
                listpage++;
                break;
            case 6:
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
        else if (nowPage == 2)
        {
            choice = accountOnOffPage(UM, IM);
            if (choice == 0)
            {
                nowPage = 0;
                continue;
            }
            else
            {
                Item *it = IM.getItem(choice);
                if (it == 0 || it->getType() != ACCOUNT)
                    continue;
                else
                {
                    Account *ac = dynamic_cast<Account *>(it);
                    //
                    if (ac->active() && ac->getcontrollerId() != UM.getLoginedUser().getId())
                    {
                        cerr << " ERROR : permission denied. " << endl;
                        continue;
                    }
                    ac->toggle(UM.getLoginedUser().getId());
                    LM.AccountStatusChange(UM.getLoginedUser(), ac);
                    IM.write();
                }
            }
        }
        else if (nowPage == 3)
        {
            int choice = devicePage(UM, IM);
            if (choice == 0)
                nowPage = 0;
            else
            {
                Device *de = dynamic_cast<Device *>(IM.getItem(choice));
                if (de == 0 || choice < 200)
                {
                    cerr << " I said," << RED << " NO ITEM FOUND! " << RESET << endl;
                    continue;
                }
                de->prompt(LM, UM.getLoginedUser());
            }
        }
    }
}
