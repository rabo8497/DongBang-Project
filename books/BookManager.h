#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "../FileHandler.h"
#include "../users/User.h"
#include "../styles/colors.h"
#include "Book.h"

class BookManager : public FileHandler
{
public:
  BookManager();

  // Get the latest ID for lending operations
  int getLatestId_lend();

  // Write lending information to file
  void lendwrite(int, int);

  // Delete lending information from file
  void lenddelete(int);

  // Get a list of books that are currently lent by a user
  std::vector<std::vector<std::string>> lendlist(User &);

  // Display a list of books with detailed information
  void booklist(int, std::vector<std::vector<std::string>>);

  // Search for books based on user input
  std::vector<std::vector<std::string>> booksearch();

  // Search for books based on a specific query
  std::vector<std::vector<std::string>> booksearch(std::string);

  // Add a new book to the system
  void bookadd(std::string, std::string, std::string, std::string, std::string, int, bool);

  // Perform the book lending operation
  void booklend(User &, int);

  // Perform the book returning operation
  void bookreturn(User &, int, int);

  // Find the book ID from an bookName
  int findIdFromItem(std::string);

  // Load book information from file
  void load(int);

  // Write book information to file
  void write(Book);

  // Modify the book file with updated information
  void modifyFile(Book);

  // Get the number of books to display per page
  int getBookNumForPage();

  // Get the reference to the current book
  Book &getBook();

protected:
  int latestId;                  // Latest book ID
  int latestluid;                // Latest lending ID
  Book nowBook;                  // Current book object
  std::string saveLocation_lend; // File location for lending information
  int interval_lend;             // Interval for lending operations
  time_t timer;                  // Timer for timestamp
  struct tm *t;                  // Structure for time information
  std::string timeDate;          // String representation of time and date
  int bookNumForPage = 5;        // Number of books to display per page
  int maxLendDay = 7;            // Maximum lending days
};

#endif
