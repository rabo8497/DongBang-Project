#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <string>
#include <conio.h>
#include <memory>
#include "logManager.h"
#include "books/Comment.h"
#include "books/Book.h"
#include "books/BookManager.h"
#include "items/ItemManager.h"
#include "items/Account.h"
#include "items/Calendar.h"
#include "users/User.h"
#include "users/UserManager.h"
#include "messages/MessageManager.h"
#include "styles/colors.h"

using namespace std;

const string version = "0.0.1"; // Version number of the program
const int totalWidth = 40;      // Total width of the console output
const int choiceInterval = 2;   // Interval between menu choices
const bool ISSCREEN = false;    // Boolean flag to determine if the program is running in a console or a graphical user interface

// Function to convert a string to an integer
// Returns the converted integer if successful, otherwise returns -1
int convertStringToInt(const string &str)
{
    // Check if the string contains only digits
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return -1; // Return -1 if a non-digit character is found
        }
    }

    // Use string stream to convert the string to an integer
    istringstream iss(str);
    int num;
    if (!(iss >> num))
    {
        return -1; // Return -1 if the conversion fails
    }

    return num; // Return the converted integer
}

int firstPage()
{
    string answer;

    // Display a horizontal line using '-' characters
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;

    // Reset the fill character to the default space ' '
    cout << setfill(' ');

    // Display the menu options
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "1) login"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "2) signup"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "0) exit"
         << ""
         << "|" << endl;

    // Display another horizontal line using '-' characters
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;

    // Reset the fill character to the default space ' '
    cout << setfill(' ');

    cout << " > ";

    // Read user input and store it in the 'answer' variable
    cin >> answer;

    // Convert the user input from a string to an integer using the 'convertStringToInt' function
    return convertStringToInt(answer);
}

void signUpPage(UserManager &um_reference, bool isScreen = ISSCREEN)
{
    string studentnumber;
    string nickname;

    // Uncomment the line below if the 'password' variable is needed in the code
    // string password;

    cout << endl
         << "What is your student number? : ";
    cin >> studentnumber;

    // Check if the student number contains only digits
    for (char ch : studentnumber)
    {
        if (!std::isdigit(ch))
        {
            cout << RED << endl
                 << "Student number must be an integer." << RESET << endl
                 << endl;
            return;
        }
    }

    cout << "What is your user nickname? : ";
    cin >> nickname;

    cout << "What is your user password? : ";

    string password;

    if (isScreen)
    {
        char ch;
        while (true)
        {
            ch = getch();
            if (ch == '\r') // Break the loop when the user presses Enter
            {
                break;
            }
            password += ch;
            cout << "*"; // Display '*' instead of the actual password characters
        }
    }
    else
    {
        cin >> password;
    }

    cout << endl;

    int studentnumberInteger = stoi(studentnumber); // Convert the student number to an integer

    // Call the 'signUp' method of the 'UserManager' class with the provided information
    um_reference.signUp(studentnumberInteger, nickname, password, false, false);
}

void logInPage(UserManager &um_reference, bool isScreen = ISSCREEN)
{
    string nickname;
    cout << endl
         << "Enter your nickname: ";
    cin >> nickname;
    cout << "Enter your password: ";

    string password;

    if (isScreen)
    {
        char ch;
        while (true)
        {
            ch = getch();
            if (ch == '\r') // Break the loop when the user presses Enter
            {
                break;
            }
            password += ch;
            cout << "*"; // Display '*' instead of the actual password characters
        }
    }
    else
    {
        cin >> password;
    }

    cout << endl;

    // Call the 'signIn' method of the 'UserManager' class with the provided nickname and password
    um_reference.signIn(nickname, password);
}

int secondPage()
{
    string answer;

    // Display a horizontal line using '-' characters
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;

    // Reset the fill character to the default space ' '
    cout << setfill(' ');

    // Display the menu options
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "1) Book-related function"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "2) public account-related function"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "3) Reservation of Items"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "4) message-related"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "5) view my log"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "6) logout"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "0) exit"
         << "|" << endl;

    // Display another horizontal line using '-' characters
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;

    // Reset the fill character to the default space ' '
    cout << setfill(' ');

    cout << " > ";

    // Read user input and store it in the 'answer' variable
    cin >> answer;

    cout << endl;

    // Convert the user input from a string to an integer using the 'convertStringToInt' function
    return convertStringToInt(answer);
}

int bookRelatedPage(UserManager &um_reference)
{
    string answer;

    // Display a horizontal line using '-' characters
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;

    // Reset the fill character to the default space ' '
    cout << setfill(' ');

    // Display the menu options
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "1) book info"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "2) book return"
         << "|" << endl;

    // Check if the logged-in user is a manager and display the book management option if true
    if (um_reference.getLoginedUser().getIsManager())
    {
        cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "3) book management"
             << "|" << endl;
    }

    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "0) back"
         << "|" << endl;

    // Display another horizontal line using '-' characters
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;

    // Reset the fill character to the default space ' '
    cout << setfill(' ');

    cout << " > ";

    // Read user input and store it in the 'answer' variable
    cin >> answer;

    cout << endl;

    // Convert the user input from a string to an integer using the 'convertStringToInt' function
    return convertStringToInt(answer);
}

int bookSearchPage(BookManager &bm_reference, vector<vector<string>> search, int listpage, bool manage)
{
    string answer;
    const int totalWidth = 78;

    // Display the book list using the 'booklist' method of the 'BookManager' class
    bm_reference.booklist(listpage, search);

    // Check if 'manage' flag is false (user-related functions) or true (manager-related functions)
    if (!manage)
    {
        // Display user-related menu options
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
        // Display manager-related menu options
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

    // Read user input and store it in the 'answer' variable
    cin >> answer;

    cout << endl;

    // Convert the user input from a string to an integer using the 'convertStringToInt' function
    return convertStringToInt(answer);
}

int bookInfoPage(BookManager &bm_reference, UserManager &um_reference, int booknumber, int &commPage)
{
    string answer;
    int totalWidth = 78;

    // Load the book information using the 'load' method of the 'BookManager' class
    bm_reference.load(booknumber);

    // Display the book information using the 'BookInfo' method of the book object obtained from 'getBook' method
    bm_reference.getBook().BookInfo();

    // Check if the comments can be printed using the 'print_comments' method of the 'Comment' object obtained from the book object
    if (!bm_reference.getBook().getComment().print_comments(um_reference, commPage))
    {
        // If comments cannot be printed and commPage is 0, increment commPage by 1
        // Otherwise, decrement commPage by 1
        if (commPage == 0)
            commPage += 1;
        else
            commPage -= 1;

        // Retry printing comments with updated commPage value
        bm_reference.getBook().getComment().print_comments(um_reference, commPage);
    }

    // Display the menu options
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

    // Read user input and store it in the 'answer' variable
    cin >> answer;

    cout << endl;

    // Convert the user input from a string to an integer using the 'convertStringToInt' function
    return convertStringToInt(answer);
}

int messagePage()
{
    string answer;
    int totalWidth = 78;

    // Display the menu options for the messaging page
    cout << setfill(' ');
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "1) send message"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "2) view message"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "3) next message page"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "4) previous message page"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "0) back"
         << "|" << endl;
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;

    cout << " > ";

    // Read user input and store it in the 'answer' variable
    cin >> answer;
    cout << endl;

    // Convert the user input from a string to an integer using the 'convertStringToInt' function
    return convertStringToInt(answer);
}

int bookLendPage(UserManager &um_reference, BookManager &bm_reference)
{
    string booknumber;
    vector<vector<string>> lendlist;

    // Check if the logged-in user has no borrowed books
    if (um_reference.getLoginedUser().getLendBookNum() == 0)
    {
        cout << "You have not borrowed any books." << endl;
        return -1;
    }

    // Get the list of borrowed books using the 'lendlist' method of the 'BookManager' class
    lendlist = bm_reference.lendlist(um_reference.getLoginedUser());

    // Display the list of borrowed books using the 'booklist' method of the 'BookManager' class
    bm_reference.booklist(1, lendlist);

    cout << "Enter the book number (back: 0): ";

    // Read the user's input for the book number
    cin >> booknumber;

    // Convert the user's input from a string to an integer using the 'convertStringToInt' function
    return convertStringToInt(booknumber);
}

int bookManagePage()
{
    string answer;

    // Display a horizontal line using '-' characters
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;

    // Reset the fill character to the default space ' '
    cout << setfill(' ');

    // Display the menu options for book management
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "1) Add new book"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "2) Edit book count"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "3) Edit book availability"
         << "|" << endl;
    cout << setw(choiceInterval) << left << "|" << setw(totalWidth - choiceInterval - 1) << left << "0) back"
         << "|" << endl;

    // Display another horizontal line using '-' characters
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;

    cout << " > ";

    // Read user input and store it in the 'answer' variable
    cin >> answer;

    cout << endl;

    // Convert the user input from a string to an integer using the 'convertStringToInt' function
    return convertStringToInt(answer);
}

void bookAddPage(BookManager &bm_reference)
{
    string BName, BSeries, BAuthor, BPub, BDate;
    string BCount;

    // Prompt the user to enter the book details
    cout << "Enter the book name: ";
    cin.ignore();
    getline(cin, BName);
    cout << "Enter the book series: ";
    getline(cin, BSeries);
    cout << "Enter the author name: ";
    getline(cin, BAuthor);
    cout << "Enter the publisher: ";
    getline(cin, BPub);
    cout << "Enter the published date: ";
    getline(cin, BDate);
    cout << "Enter the book count: ";
    cin >> BCount;

    // Convert the book count from string to integer using the 'convertStringToInt' function
    int BcountInt = convertStringToInt(BCount);

    // Check if the conversion was unsuccessful (-1 indicates an invalid input), and set the book count to 0 in that case
    if (BcountInt == -1)
    {
        BcountInt = 0;
    }

    // Add the book to the book manager using the 'bookadd' method
    bm_reference.bookadd(BName, BSeries, BAuthor, BPub, BDate, BcountInt, true);
}

void bookLendPageFunction(UserManager &um_reference, BookManager &bm_reference, LogManager &lm_reference, int booknumber, int &page)
{
    vector<vector<string>> lendlist;

    // Check if the logged-in user has no borrowed books
    if (um_reference.getLoginedUser().getLendBookNum() == 0)
    {
        // Set the page value to 1 and return
        page = 1;
        return;
    }

    // Get the list of borrowed books using the 'lendlist' method of the 'BookManager' class
    lendlist = bm_reference.lendlist(um_reference.getLoginedUser());

    // Check if the booknumber is valid (within the range of lendlist)
    if (booknumber > lendlist.size())
    {
        // Display an error message and return
        cout << RED << "Invalid book number. Please choose another number." << RESET << endl;
        return;
    }

    // Load the book information using the 'load' method of the 'BookManager' class
    bm_reference.load(stoi(lendlist[booknumber - 1][4]));

    // Return the book using the 'BookReturn' method of the 'LogManager' class
    lm_reference.BookReturn(um_reference.getLoginedUser(), bm_reference.getBook());

    // Update the book status using the 'bookreturn' method of the 'BookManager' class
    bm_reference.bookreturn(um_reference.getLoginedUser(), stoi(lendlist[booknumber - 1][4]), stoi(lendlist[booknumber - 1][1]));

    // Modify the user file using the 'modifyFile' method of the 'UserManager' class
    um_reference.modifyFile();
}

int accountOnOffPage(UserManager &um_reference, ItemManager &im_reference)
{
    string answer;

    // Display a horizontal line using '-' characters
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;

    // Reset the fill character to the default space ' '
    cout << setfill(' ');

    // Show the list of accounts using the 'showList' method of the 'ItemManager' class
    im_reference.showList(um_reference.getLoginedUser(), ACCOUNT, true);

    // Display another horizontal line using '-' characters
    cout << left << setfill('-') << setw(totalWidth) << "" << endl;

    // Reset the fill character to the default space ' '
    cout << setfill(' ');

    // Prompt the user to select an account or go back
    cout << " Select account (back: 0) > ";

    // Read the user's input for the account selection from the standard input and store it in the 'answer' variable
    cin >> answer;

    // Convert the user's input from a string to an integer using the 'convertStringToInt' function
    return convertStringToInt(answer);
}

int devicePage(UserManager &um_reference, ItemManager &im_reference)
{
    // Display a horizontal line using '-' characters
    cout << setw(totalWidth) << setfill('-') << "" << setfill(' ') << endl;

    // Show the list of devices using the 'showList' method of the 'ItemManager' class
    im_reference.showList(um_reference.getLoginedUser(), DEVICE, true);

    // Display another horizontal line using '-' characters
    cout << setw(totalWidth) << setfill('-') << "" << setfill(' ') << endl;

    int input;
    string ibuffer;

    // Continue prompting the user until a valid input is entered
    while (true)
    {
        cout << " Select device (back: 0) > ";

        cin >> ibuffer;

        // Check if the first character of the input is not a digit
        if (!isdigit(ibuffer[0]))
        {
            cout << RED << "ERROR: " << RESET << "Wrong value. Please enter a valid number." << endl;
            continue;
        }
        else
        {
            // Convert the input from a string to an integer
            input = stoi(ibuffer);
            break;
        }
    }

    return input;
}

void sendMessageFunction(UserManager &um_reference, MessageManager &MM_, LogManager &LM_)
{
    string to_nickname;
    string title;
    string message;

    cout << endl;
    cout << "To: ";

    // Read the recipient's nickname from the user
    cin >> to_nickname;

    // Find the recipient's user ID from their nickname using the 'findIdFromItem' method of the 'UserManager' class
    int toId = um_reference.findIdFromItem(to_nickname);

    // Check if the recipient's nickname does not exist
    if (toId == -1)
    {
        cout << RED << "Nickname does not exist." << RESET << endl;
        return;
    }

    cout << "Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Your message: ";
    getline(cin, message);

    // Write the message using the 'write' method of the 'MessageManager' class, passing the recipient's user ID, title, and message as parameters
    if (!(MM_.write(toId, title, message)))
    {
        return;
    }

    cout << BLUE << "Successfully completed sending message!" << RESET << endl;

    // Log the message sending activity using the 'SendMessage' method of the 'LogManager' class, passing the logged-in user as a parameter
    LM_.SendMessage(um_reference.getLoginedUser());

    // Retrieve and log the received message using the 'getMessage' method of the 'LogManager' class, passing the recipient's nickname as a parameter
    LM_.getMessage(to_nickname);
}

int main(int argc, char *argv[])
{
    // Create instances of LogManager, UserManager, BookManager, ItemManager
    LogManager LM;
    UserManager UM;
    BookManager BM;
    ItemManager IM;

    // Declare a unique pointer for the MessageManager
    unique_ptr<MessageManager> MM;

    // Initialize other variables used throughout the program
    vector<vector<string>> search = BM.booksearch();
    int listpage = 1;
    int booknumber;
    string booknumberstr;
    int choice;
    int nowPage = 0;
    int commPage = 1;
    string bookNum;
    bool isProgramEnd = false;

    // Display colorful ASCII art text of project name
    std::cout << "\n";
    std::cout << GREEN << "   __" << MAGENTA << "______" << YELLOW << " ______" << RED << " ______ " << GREEN << "__   " << endl;
    std::cout << GREEN << "  / /" << MAGENTA << "|  _  \\" << YELLOW << "| ___ \\" << RED << "| ___ \\" << GREEN << "\\ \\  " << endl;
    std::cout << GREEN << " / / " << MAGENTA << "| | | |" << YELLOW << "| |_/ /" << RED << "| |_/ /" << GREEN << " \\ \\ " << endl;
    std::cout << GREEN << "< <  " << MAGENTA << "| | | |" << YELLOW << "| ___ \\" << RED << "|  __/ " << GREEN << "  > >" << endl;
    std::cout << GREEN << " \\ \\ " << MAGENTA << "| |/ / " << YELLOW << "| |_/ /" << RED << "| |    " << GREEN << " / / " << endl;
    std::cout << GREEN << "  \\_\\" << MAGENTA << "|___/  " << YELLOW << "\\____/ " << RED << "\\_|    " << GREEN << "/_/  " << endl;
    std::cout << "\n"
              << RESET;

    // Main program loop which continues until isProgramEnd is set to true
    while (!isProgramEnd)
    {
        // Check if a user is signed in
        if (!UM.getIsSignIn())
        {
            // Display first page if no user is signed in
            choice = firstPage();
            // Switch case for handling user choice
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
            case 0: // If choice is 0, set program end to true
                isProgramEnd = true;
                break;
            default:
                cout << RED << "wrong value. choose other number." << RESET << endl;
            }
        }
        else if (nowPage == 0) // User is signed in, perform user-specific actions
        {
            // Load the messages for the logged in user
            MM = std::make_unique<MessageManager>(UM.getLoginedUser().getId());
            MM->load();
            choice = secondPage();
            // Switch case for handling user choice on the second page
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
                commPage = 1;
                nowPage = 5;
                break;
            case 5:
                LM.printLog(UM.getLoginedUser());
                break;
            case 6:
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
        else if (nowPage == 1) // If the user selected the "Book Related" page
        {
            // Switch case for handling user choice on the book related page
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
        else if (nowPage == 11) // If the user is searching for a book
        {
            // Switch case for handling user choice on the book search page
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
                cin >> booknumberstr;
                booknumber = convertStringToInt(booknumberstr);
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
                cin >> booknumberstr;
                booknumber = convertStringToInt(booknumberstr);
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
        else if (nowPage == 111) // If the user is viewing book info
        {
            // Switch case for handling user choice on the book info page
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
        else if (nowPage == 12) // If the user is in the book lending page
        {
            // Switch case for handling user choice on the book lend page
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
        else if (nowPage == 13) // If the user is in the book managing page
        {
            // Switch case for handling user choice on the book manage page
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
                cin >> booknumberstr;
                booknumber = convertStringToInt(booknumberstr);
                cout << "enter the new book count : ";
                cin >> booknumberstr;
                newCount = convertStringToInt(booknumberstr);
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
                cin >> booknumberstr;
                booknumber = convertStringToInt(booknumberstr);
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
        else if (nowPage == 2) // If the user is on the account on/off page
        {
            // Switch case for handling user choice on the account on/off page
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
                        cout << " ERROR : permission denied. " << endl;
                        continue;
                    }
                    ac->toggle(UM.getLoginedUser().getId());
                    LM.AccountStatusChange(UM.getLoginedUser(), ac);
                    IM.write();
                }
            }
        }
        else if (nowPage == 3) // If the user is on the device page
        {
            // Switch case for handling user choice on the device page
            int choice = devicePage(UM, IM);
            if (choice == 0)
                nowPage = 0;
            else
            {
                Device *de = dynamic_cast<Device *>(IM.getItem(choice));
                if (de == 0 || choice < 200)
                {
                    cout << " I said," << RED << " NO ITEM FOUND! " << RESET << endl;
                    continue;
                }
                de->prompt(LM, UM.getLoginedUser());
            }
        }
        else if (nowPage == 5) // If the user is on the message page
        {
            // Print user messages
            MM->print_messages(UM, commPage);
            choice = messagePage();
            // Switch case for handling user choice on the message page
            switch (choice)
            {
            case 0:
                nowPage = 0;
                commPage = 0;
                break;
            case 1:
                sendMessageFunction(UM, *MM, LM);
                break;
            case 2:
                cout << "choose book number : ";
                cin >> bookNum;
                MM->open_message(UM, convertStringToInt(bookNum));
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
    }
    // Display goodbye message
    cout << " _____  _                    _          _ \n";
    cout << "|_   _|| |                  | |        | |\n";
    cout << "  | |  | |__    __ _  _ __  | | __ ___ | |\n";
    cout << "  | |  | '_ \\  / _` || '_ \\ | |/ // __|| |\n";
    cout << "  | |  | | | || (_| || | | ||   < \\__ \\|_|\n";
    cout << "  \\_/  |_| |_| \\__,_||_| |_||_|\\_\\|___/(_)\n";
}