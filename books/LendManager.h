#ifndef LENDMANAGER_H
#define LENDMANAGER_H

#include <iostream>
#include <string>
#include <ctime>
#include "../FileHandler.h"
#include "Book.h"

class LendManager : public FileHandler
{
public:
  LendManager();

  void load(int);
  void write(int, int);
  void modifyFile(int, User, Book);
  void deleteFile(int);
  void nowTime();

private:
  int latestId;
  Book nowBook;
  time_t timer;
  struct tm *t;
  std::string timeDate;
};

#endif
