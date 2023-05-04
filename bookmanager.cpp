#include <iostream>
#include <string>
#include <sstream>

#include "bookmanger.h"
#include "book.h"
BookManager::BookManager() : FileHandler("book.txt", 15)
{
}

void BookManager::booklist() {}
void BookManager::booksearch(std::string findBook) {}

int BookManager::findIdFromItem(std::string findBook) {}

void BookManager::load(int bookId) {}
void BookManager::write(Book newBook) {}
void BookManager::modifyFile(int bookId, Book editBook) {}
void BookManager::deleteFile(int bookId) {}