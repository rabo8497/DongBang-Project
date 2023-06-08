#include <iostream>
#include "Book.h"
#include "Comment.h"
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

Book::Book() {}

Book::Book(int buid, std::string bookName, std::string bookSeries, std::string bookAuthor, std::string bookPub, std::string bookDate, int bookCount, bool isCanLend) : buid(buid), bookName(bookName), bookSeries(bookSeries), bookAuthor(bookAuthor), bookPub(bookPub), bookDate(bookDate), bookCount(bookCount), isCanLend(isCanLend) {}

int Book::getBuid() const
{
  return buid;
}

std::string Book::getBName() const
{
  return bookName;
}

int Book::getBCount() const
{
  return bookCount;
}

std::string Book::getBSeries() const
{
  return bookSeries;
}

std::string Book::getBAuthor() const
{
  return bookAuthor;
}

std::string Book::getBPub() const
{
  return bookPub;
}

std::string Book::getBDate() const
{
  return bookDate;
}

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

void Book::setBCount(int newBCount)
{
  if (newBCount < 0)
  {
    std::cout << RED << "Book count can't be negative number!!" << RESET << std::endl;
    return;
  }
  bookCount = newBCount;
}

void Book::setIsCanLend(bool newIsCanLend)
{
  isCanLend = newIsCanLend;
}

void Book::BookInfo()
{
  int totalWidth = 78;
  int choiceInterval = 2;

  std::cout << std::left << std::setfill('-') << std::setw((totalWidth - 6) / 2) << "";
  std::cout << "<Info>";
  std::cout << std::right << std::setfill('-') << std::setw((totalWidth - 6) / 2) << "" << std::endl;

  std::cout << std::setfill(' ');
  std::cout << std::setw(choiceInterval) << std::left << "|"
            << "Book UID : " << std::setw(totalWidth - choiceInterval - 12) << std::left << buid << "|" << std::endl;
  std::cout << std::setw(choiceInterval) << std::left << "|"
            << "Name : " << std::setw(totalWidth - choiceInterval - 8) << std::left << bookName << "|" << std::endl;
  std::cout << std::setw(choiceInterval) << std::left << "|"
            << "Series : " << std::setw(totalWidth - choiceInterval - 10) << std::left << bookSeries << "|" << std::endl;
  std::cout << std::setw(choiceInterval) << std::left << "|"
            << "Author : " << std::setw(totalWidth - choiceInterval - 10) << std::left << bookAuthor << "|" << std::endl;
  std::cout << std::setw(choiceInterval) << std::left << "|"
            << "Published Date : " << std::setw(totalWidth - choiceInterval - 18) << std::left << bookDate << "|" << std::endl;
  std::cout << std::setw(choiceInterval) << std::left << "|"
            << "Publisher : " << std::setw(totalWidth - choiceInterval - 13) << std::left << bookPub << "|" << std::endl;
  std::cout << std::setw(choiceInterval) << std::left << "|"
            << "Count : " << std::setw(totalWidth - choiceInterval - 9) << std::left << bookCount << "|" << std::endl;
  std::cout << std::left << std::setfill('-') << std::setw(totalWidth) << "" << std::endl;
  std::cout << std::setfill(' ');
}

Comment Book::getComment()
{
  Comment cm(buid);
  cm.load();
  return cm;
}
