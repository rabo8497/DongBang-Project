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
  /*for (int i = 1; i <= 3; i++)
  {
    BookManager.bookadd("일상 " + to_string(i), "일상", "아라이 케이이치", "대원씨아이", "123456", 1, true);
  }
   for (int i = 1; i <= 3; i++)
   {
     BookManager.bookadd("Onii chan wa Oshimai " + to_string(i), "Onii chan wa Oshimai", "NekoTofu", "B Publisher", "456", 1, true);
   }
   for (int i = 1; i <= 3; i++)
   {
     BookManager.bookadd("ONE PUNCH MAN " + to_string(i), "ONE PUNCH MAN", "ONE", "C Publisher", "789", 1, true);
   }
   for (int i = 1; i <= 3; i++)
   {
     BookManager.bookadd("CHAINSAW MAN " + to_string(i), "CHAINSAW MAN", "Tatsuki", "D Publisher", "000", 1, true);
   }*/
  UserManager usermanage;
  BookManager.load(3);

  usermanage.signUp(20225167, "rabo84978", "aaaaa8", false, false);
  usermanage.signIn("rabo84987", "aaaaa8");
  cout << "현재 책의 수" << usermanage.getLoginedUser().getLendBookNum() << endl;

  BookManager.booklend(usermanage.getLoginedUser(), BookManager.getBook().getBuid());
  LendManager.write(usermanage.getLoginedUser().getId(), BookManager.getBook().getBuid());
  usermanage.modifyFile(usermanage.getLoginedUser()); // 변한 User 객체를 저장하기 위해 파일 수정

  cout << usermanage.getLoginedUser().getLendBookNum() << " " << BookManager.getBook().getBCount() << " " << BookManager.getBook().getIsCanLend() << endl;

  BookManager.bookback(usermanage.getLoginedUser(), BookManager.getBook().getBuid());
  usermanage.modifyFile(usermanage.getLoginedUser());

  cout << usermanage.getLoginedUser().getLendBookNum() << " " << BookManager.getBook().getBCount() << " " << BookManager.getBook().getIsCanLend() << endl;

  return 0;
}