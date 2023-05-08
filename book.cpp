#include <iostream>
#include "book.h"

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

bool Book::getIsCanLend() const
{
  if (bookCount == 0)
  {
    return false;
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
    std::cout << "Book count can't be negative number!!" << std::endl;
    return;
  }
  bookCount = newBCount;
  std::cout << "Book count newly set : " << bookCount << std::endl;
}

void Book::setIsCanLend(bool newIsCanLend)
{
  isCanLend = newIsCanLend;
  std::cout << "isCanLend newly set : " << isCanLend << std::endl;
}

void Book::BookInfo()
{
  std::cout << "Book UID : " << buid << std::endl;
  std::cout << "Name : " << bookName << std::endl;
  std::cout << "Series : " << bookSeries << std::endl;
  std::cout << "Author : " << bookAuthor << std::endl;
  std::cout << "Published Date : " << bookDate << std::endl;
  std::cout << "Publisher : " << bookPub << std::endl;
  std::cout << "Count : " << bookCount << std::endl;
}

/*void Book::addComm(std::vector<std::string> newComm)
{
  bookComm.push_back(newComm);
  std::cout << "New comment added (Current Comments : " << bookComm.size() << ")" << std::endl;
}
void Book::BookComm()
{
  for (auto loop : bookComm)
  {
    std::cout << "ID : " << loop.at(0) << std::endl;
    std::cout << loop.at(1) << std::endl;
    std::cout << "Posted Date : " << loop.at(2) << std::endl;
  }
}*/
