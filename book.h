#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include "user.h"

class Book
{
public:
  Book(const int buid, std::string bookName, std::string bookSeries,std::string bookAuthor, std::string bookPub, const int bookDate, int bookCount);

private:
  const int buid;
  std::string bookName;
  std::string bookSeries;
  int bookCount;
  const int bookDate;
  std::string bookAuthor;
  std::string bookPub;
  std::vector<std::string[3]> bookComm;
};

#endif