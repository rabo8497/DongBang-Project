#ifndef LOGMANAGER_H
#define LOGMANAGER_H

#include "fileHandler.h"
#include "./users/User.h"
#include "./books/Book.h"
#include "./items/Account.h"
#include "./items/Device.h"
#include <string>
#include <fstream>
#include <chrono>
#include <iomanip>
#include <sstream>

class LogManager : public FileHandler
{
public:
    LogManager() : FileHandler(".\\dataBase\\log.txt", 1) {}

    // Function to get the current date and time
    std::string currentDateTime()
    {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X");
        return ss.str();
    }

    // Function to write a log message to the log file
    void write(const std::string &message)
    {
        std::ofstream file(saveLocation, std::ios_base::app); // 'app' mode allows appending to the end of the file
        if (file.is_open())
        {
            file << "[" << currentDateTime() << "] " << message;
            file.close();
        }
    }

    // Log events related to user login
    void UserLogin(const User &loginUser)
    {
        std::string username = loginUser.getNickName();
        write("User: " + username + " logged in.\n");
    }

    // Log events related to user logout
    void UserLogout(const User &loginUser)
    {
        std::string username = loginUser.getNickName();
        write("User: " + username + " logged out.\n");
    }

    // Log events related to borrowing a book
    void BookLend(const User &loginUser, const Book &lendBook)
    {
        std::string username = loginUser.getNickName();
        std::string bookTitle = lendBook.getBName();
        write("User: " + username + " borrowed the book: " + bookTitle + ".\n");
    }

    // Log events related to returning a borrowed book
    void BookReturn(const User &loginUser, const Book &lendBook)
    {
        std::string username = loginUser.getNickName();
        std::string bookTitle = lendBook.getBName();
        write("User: " + username + " returned the book: " + bookTitle + ".\n");
    }

    // Log events related to writing a comment on a book
    void BookComment(const User &loginUser, const Book &lendBook)
    {
        std::string username = loginUser.getNickName();
        std::string bookTitle = lendBook.getBName();
        write("User: " + username + " wrote a comment in book: " + bookTitle + ".\n");
    }

    // Log events related to removing a comment from a book
    void BookRemoveComment(const User &loginUser, const Book &lendBook)
    {
        std::string username = loginUser.getNickName();
        std::string bookTitle = lendBook.getBName();
        write("User: " + username + " deleted a comment in book: " + bookTitle + ".\n");
    }

    // Log events related to changing the status of an account
    void AccountStatusChange(const User &loginUser, Account *account)
    {
        std::string username = loginUser.getNickName();
        std::string accountName = account->getName();
        std::string accountType = account->getAccountType();
        bool isOn = account->active();
        if (isOn)
        {
            write("User: " + username + " activated the " + accountType + " account: " + accountName + "\n");
        }
        else
        {
            write("User: " + username + " deactivated the " + accountType + " account: " + accountName + "\n");
        }
    }

    // Log events related to reserving a device
    void DeviceReserve(const User &loginUser, std::string deviceName)
    {
        std::string username = loginUser.getNickName();
        write("User: " + username + " reserved the device: " + deviceName + ".\n");
    }

    // Log events related to canceling a device reservation
    void DeviceCancelReserve(const User &loginUser, std::string deviceName)
    {
        std::string username = loginUser.getNickName();
        write("User: " + username + " canceled the reservation of the device: " + deviceName + ".\n");
    }

    // Log events related to sending a message
    void SendMessage(const User &loginUser)
    {
        std::string username = loginUser.getNickName();
        write("User: " + username + " sent a message.\n");
    }

    // Log events related to receiving a message
    void getMessage(const std::string username)
    {
        write("User: " + username + " received a message.\n");
    }

    // Function to print the log messages for a specific user
    void printLog(const User &loginUser)
    {
        std::string username = loginUser.getNickName();
        std::string search = "User: " + username;
        std::ifstream file(saveLocation);

        if (!file)
        {
            std::cout << "Unable to open file: " << saveLocation << "\n";
            return;
        }

        std::string line;
        while (std::getline(file, line))
        {
            if (line.find(search) != std::string::npos)
            {
                std::cout << line << "\n";
            }
        }
        std::cout << "(0: back) >> ";
        std::cin.ignore();
        std::getline(std::cin, search);
    }
};

#endif
