#include <iostream>
#include "Book.h"
#include "Comment.h"

Book::Book() {}

// Constructor that initializes the Book object with provided values
Book::Book(int buid, std::string bookName, std::string bookSeries, std::string bookAuthor, std::string bookPub, std::string bookDate, int bookCount, bool isCanLend)
    : buid(buid), bookName(bookName), bookSeries(bookSeries), bookAuthor(bookAuthor), bookPub(bookPub), bookDate(bookDate), bookCount(bookCount), isCanLend(isCanLend) {}

// Getter for the Book UID
int Book::getBuid() const
{
  return buid;
}

// Getter for the Book name
std::string Book::getBName() const
{
  return bookName;
}

// Getter for the Book count
int Book::getBCount() const
{
  return bookCount;
}

// Getter for the Book series
std::string Book::getBSeries() const
{
  return bookSeries;
}

// Getter for the Book author
std::string Book::getBAuthor() const
{
  return bookAuthor;
}

// Getter for the Book publisher
std::string Book::getBPub() const
{
  return bookPub;
}

// Getter for the Book published date
std::string Book::getBDate() const
{
  return bookDate;
}

// Getter for whether the Book can be lent or not
bool Book::getIsCanLend()
{
  if (bookCount == 0)
  {
    isCanLend = false;
    return isCanLend;
  }
  else
  {
    return isCanLend;
  }
}

// Setter for the Book count
void Book::setBCount(int newBCount)
{
  if (newBCount < 0)
  {
    std::cout << RED << "Book count can't be a negative number!" << RESET << std::endl;
    return;
  }
  bookCount = newBCount;
}

// Setter for whether the Book can be lent or not
void Book::setIsCanLend(bool newIsCanLend)
{
  isCanLend = newIsCanLend;
}

// Print the information of the Book
void Book::BookInfo()
{
  int totalWidth = 78;
  int choiceInterval = 2;

  // Print a horizontal line to separate sections
  std::cout << std::left << std::setfill('-') << std::setw((totalWidth - 6) / 2) << "";
  std::cout << "<Info>";
  std::cout << std::right << std::setfill('-') << std::setw((totalWidth - 6) / 2) << "" << std::endl;

  std::cout << std::setfill(' ');

  // Print the Book UID
  std::cout << std::setw(choiceInterval) << std::left << "|"
            << "Book UID : " << std::setw(totalWidth - choiceInterval - 12) << std::left << buid << "|" << std::endl;

  // Print the Book name
  std::cout << std::setw(choiceInterval) << std::left << "|"
            << "Name : " << std::setw(totalWidth - choiceInterval - 8) << std::left << bookName << "|" << std::endl;

  // Print the Book series
  std::cout << std::setw(choiceInterval) << std::left << "|"
            << "Series : " << std::setw(totalWidth - choiceInterval - 10) << std::left << bookSeries << "|" << std::endl;

  // Print the Book author
  std::cout << std::setw(choiceInterval) << std::left << "|"
            << "Author : " << std::setw(totalWidth - choiceInterval - 10) << std::left << bookAuthor << "|" << std::endl;

  // Print the Book published date
  std::cout << std::setw(choiceInterval) << std::left << "|"
            << "Published Date : " << std::setw(totalWidth - choiceInterval - 18) << std::left << bookDate << "|" << std::endl;

  // Print the Book publisher
  std::cout << std::setw(choiceInterval) << std::left << "|"
            << "Publisher : " << std::setw(totalWidth - choiceInterval - 13) << std::left << bookPub << "|" << std::endl;

  // Print the Book count
  std::cout << std::setw(choiceInterval) << std::left << "|"
            << "Count : " << std::setw(totalWidth - choiceInterval - 9) << std::left << bookCount << "|" << std::endl;

  // Print a horizontal line to separate sections
  std::cout << std::left << std::setfill('-') << std::setw(totalWidth) << "" << std::endl;
  std::cout << std::setfill(' ');
}

// Getter for the comments for the Book
Comment Book::getComment()
{
  Comment cm(buid);
  cm.load();
  return cm;
}
