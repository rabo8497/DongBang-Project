#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "../FileHandler.h"
#include "../users/User.h"
#include "Book.h"

class BookManager : public FileHandler
{
public:
  BookManager();

  int getLatestId_lend();
  void lendwrite(int, int, std::string);

  void booklist(int, std::vector<std::vector<std::string>>);
  std::vector<std::vector<std::string>> booksearch();
  std::vector<std::vector<std::string>> booksearch(std::string);
  void bookadd(std::string, std::string, std::string, std::string, std::string, int, bool);
  void booklend(User &, int);
  void bookreturn(User &, int);

  int findIdFromItem(std ::string);

  void load(int);
  void write(Book);
  void modifyFile(Book);
  void deleteFile(int);

  Book &getBook();

protected:
  int latestId;
  int latestluid;
  Book nowBook;
  std::string saveLocation_lend;
  int interval_lend;
  time_t timer;
  struct tm *t;
  std::string timeDate;
  int bookNumForPage = 5;
};

#endif