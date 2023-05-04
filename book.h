#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include "user.h"

class Book
{
public:
  Book(const int buid, std::string bookName, std::string bookSeries, std::string bookAuthor, std::string bookPub, const int bookDate, int bookCount = 1, bool isCanLend = true);
  int getBuid() const;
  std::string getBName() const;
  int getBCount() const;
  std::string getBSeries() const;
  std::string getBAuthor() const;
  std::string getBPub() const;
  int getBDate() const;
  bool getIsCanLend() const;

  void setBCount(int newBCount);
  void setIsCanLend(bool newIsCanLend);
  void BookInfo();
  
  //void addComm(std::vector<std::string> newComm);
  //void BookComm();

private:
  const int buid;
  std::string bookName;
  std::string bookSeries;
  int bookCount;
  const int bookDate;
  std::string bookAuthor;
  std::string bookPub;
  bool isCanLend;
  std::vector<std::vector<std::string>> bookComm;
};

#endif