#ifndef BOOKMANAGER_H
#define BOOKMANAGER_H

#include <iostream>
#include <string>
#include "FileHandler.h"
#include "user.h"
#include "book.h"

class BookManager : public FileHandler
{
public:
  BookManager();

  void booklist(int);
  void booksearch(std::string);
  void booklend(User, std::string);
  void bookback(User, std::string);

  int findIdFromItem(std ::string);

  void load(int);
  void write(Book);
  void modifyFile(int, Book);
  void deleteFile(int);

private:
  int latestId;
  Book nowBook;
};

#endif