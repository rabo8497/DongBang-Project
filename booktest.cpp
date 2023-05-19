#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>

#include "books/Book.h"
#include "books/BookManager.h"
#include "users/User.h"
#include "users/UserManager.h"

using namespace std;

const string version = "0.0.1";

int main(int argc, char *argv[])
{
  BookManager bookmanager;

  User u1(3, 20225167, "aaaaa", "aaaaa");

  bookmanager.booklend(u1, 2);
  cout << endl;
  cout << u1.getLendBookNum() << endl;
  bookmanager.load(2);
  cout << bookmanager.getBook().getBCount() << endl;

  cout << endl;
  bookmanager.bookreturn(u1, 2);
  cout << endl;
  cout << u1.getLendBookNum() << endl;
  bookmanager.load(2);
  cout << bookmanager.getBook().getBCount() << endl;

  return 0;
}