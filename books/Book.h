#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <vector>
#include <iomanip>
#include "../users/User.h"
#include "../styles/colors.h"

// Forward declaration of the Comment class
class Comment;

class Book
{
public:
  Book();
  Book(int buid, std::string bookName, std::string bookSeries, std::string bookAuthor, std::string bookPub, std::string bookDate, int bookCount = 1, bool isCanLend = true);
  int getBuid() const;
  std::string getBName() const;
  int getBCount() const;
  std::string getBSeries() const;
  std::string getBAuthor() const;
  std::string getBPub() const;
  std::string getBDate() const;
  bool getIsCanLend();

  void setBCount(int newBCount);
  void setIsCanLend(bool newIsCanLend);
  void BookInfo();

  Comment getComment(); // Declaration of the Comment class

private:
  int buid;
  std::string bookName;
  std::string bookSeries;
  int bookCount;
  std::string bookDate;
  std::string bookAuthor;
  std::string bookPub;
  bool isCanLend;
};

#endif
