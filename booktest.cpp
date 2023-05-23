#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
#include <vector>

#include "books/Book.h"
#include "books/BookManager.h"
#include "users/User.h"
#include "users/UserManager.h"

using namespace std;

const string version = "0.0.1";

int main(int argc, char *argv[])
{
  BookManager bookmanager;

  vector<vector<string>> search;

  search = bookmanager.booksearch();

  bookmanager.booklist(1, search);

  return 0;
}