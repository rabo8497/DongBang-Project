#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <iostream>
#include <string>
#include "FileHandler.h"
#include "user.h"
#include "book.h"
#include "lendManager.h"

class BookManager : public FileHandler
{
public:
  BookManager();

  void booklist(int);
  void booksearch(std::string);
  void bookadd(std::string, std::string, std::string, std::string, std::string, int, bool);
  void booklend(User, int);
  void bookback(User, int);

  int findIdFromItem(std ::string);

  void load(int);
  void write(Book);
  void modifyFile(int, Book);
  void deleteFile(int);

  Book &getBook();

private:
  int latestId;
  Book nowBook;
};

#endif