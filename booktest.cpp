#include <iostream>
#include "books/Book.h"
#include "books/BookManager.h"
#include "users/User.h"
#include "users/UserManager.h"
using namespace std;

int main()
{
  UserManager UM;
  UM.signIn("pengdol2", "pengdol2");
  BookManager BM;
  BM.lendlist(UM.getLoginedUser());
}