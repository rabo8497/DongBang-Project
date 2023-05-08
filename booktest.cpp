#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "user.h"
#include "userManager.h"
#include "book.h"
#include "bookManager.h"
using namespace std;

int main(int argc, char *argv[])
{
  BookManager BookManager;

  /*for (int i = 1; i <= 3; i++)
  {
    BookManager.bookadd("Re zero " + to_string(i), "Re zero", "Nagatsuki", "A Publisher", 123, 1, true);
  }
  for (int i = 1; i <= 3; i++)
  {
    BookManager.bookadd("Onii chan wa Oshimai " + to_string(i), "Onii chan wa Oshimai", "NekoTofu", "B Publisher", 456, 1, true);
  }
  for (int i = 1; i <= 3; i++)
  {
    BookManager.bookadd("ONE PUNCH MAN " + to_string(i), "ONE PUNCH MAN", "ONE", "C Publisher", 789, 1, true);
  }
  for (int i = 1; i <= 3; i++)
  {
    BookManager.bookadd("CHAINSAW MAN " + to_string(i), "CHAINSAW MAN", "Tatsuki", "D Publisher", 000, 1, true);
  }*/
  std::string keyword;
  cout << "Enter the search keyword" << endl;
  cin >> keyword;

  BookManager.booksearch(keyword);
}