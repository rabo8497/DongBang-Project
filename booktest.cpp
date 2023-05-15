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
  LendManager LendManager;
  UserManager usermanage;

  BookManager.load(2);

  usermanage.signUp(20225167, "rabo84978", "aaaaa8", false, false);
  usermanage.signIn("rabo84987", "aaaaa8");
  cout << "현재 책의 수" << usermanage.getLoginedUser().getLendBookNum() << endl;

  BookManager.booklend(usermanage.getLoginedUser(), BookManager.getBook().getBuid());
  LendManager.write(usermanage.getLoginedUser().getId(), BookManager.getBook().getBuid());
  usermanage.modifyFile(usermanage.getLoginedUser()); // 변한 User 객체를 저장하기 위해 파일 수정

  BookManager.load(4);

  BookManager.booklend(usermanage.getLoginedUser(), BookManager.getBook().getBuid());
  LendManager.write(usermanage.getLoginedUser().getId(), BookManager.getBook().getBuid());
  usermanage.modifyFile(usermanage.getLoginedUser());

  cout << usermanage.getLoginedUser().getLendBookNum() << " " << BookManager.getBook().getBCount() << " " << BookManager.getBook().getIsCanLend() << endl;

  BookManager.bookback(usermanage.getLoginedUser(), BookManager.getBook().getBuid());
  usermanage.modifyFile(usermanage.getLoginedUser());

  cout << usermanage.getLoginedUser().getLendBookNum() << " " << BookManager.getBook().getBCount() << " " << BookManager.getBook().getIsCanLend() << endl;

  /*for (int i = 1; i <= 3; i++)
  {
    BookManager.bookadd("Physics " + to_string(i), "Physics", "Author A", "Publisher A", "20220101", 1, true);
  }

  for (int i = 1; i <= 3; i++)
  {
    BookManager.bookadd("Comics " + to_string(i), "Comics", "Author B", "Publisher B", "20230101", 1, true);
  }*/


  return 0;
}