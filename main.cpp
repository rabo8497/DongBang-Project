#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "user.h"
#include "userManager.h"
using namespace std;

const string version = "0.0.1";

int main(int argc, char *argv[]) // argc=인자 갯수, argv=인자들
{
    // 아래의 프로그램 실행 : g++ user.cpp userManager.cpp main.cpp -i program
    // 파일 아래에 있는 program.exe 실행
    UserManager usermanage;
    usermanage.signUp(20225167, "rabo8497", "aaaaa", true, false); // 회원가입 기능, User.txt에 저장됨
    usermanage.signUp(20225168, "rabo84978", "aaaaa8", false, false);
    usermanage.signUp(20225169, "rabo84979", "aaaaa9", false, true);
    
    usermanage.signIn("rabo84978", "aaaaa8");
    // 책 빌리기
    cout << "현재 책의 수" << usermanage.getLoginedUser().getLendBookNum() << endl;
    
    usermanage.getLoginedUser().lendBook(); // 책 빌림 -> User 객체 변함
    usermanage.modifyFile(usermanage.getLoginedUser()); // 변한 User 객체를 저장하기 위해 파일 수정
    
    usermanage.getLoginedUser().lendBook();
    usermanage.modifyFile(usermanage.getLoginedUser());
    
    cout << "현재 책의 수" << usermanage.getLoginedUser().getLendBookNum() << endl;

    usermanage.getLoginedUser().returnBook();
    usermanage.modifyFile(usermanage.getLoginedUser());

    cout << "현재 책의 수" << usermanage.getLoginedUser().getLendBookNum() << endl;

    return 0;

}
