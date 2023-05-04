#pragma once // include guard

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
    // 아래처럼 동일한 닉네임으로 회원가입을 시도하면 안내글이 뜸
    usermanage.signUp(20224234, "rabo8497", "aaaaasssss", false, false);

    cout << usermanage.getLoginedUser().getNickName() << endl; // 로그인 하지 않은 상태에서 현재 로그인 된 계정에 접근하면 빈 User을 반환
    usermanage.signIn("rabo84978", "aaaaa8");
    cout << usermanage.getLoginedUser().getNickName() << endl; // 이 경우 위에서 로그인 됐으므로 제대로 로그인 된 User 반환

    usermanage.signOut(); // 로그아웃

    cout << endl << endl << endl << "<program operating example>" << endl << endl;
    while (true) {
        int choice = -1;
        cout << "choice one.\n1. login\n2. signup\n3. program exit\n\nYou : ";
        cin >> choice;
        if (choice == 1) {
            string nick;
            string passw;
            cout << endl;
            cout << "Your nickname : ";
            cin >> nick;
            cout << "Your password : ";
            cin >> passw;
            cout << endl;
            usermanage.signIn(nick, passw);
            if (usermanage.getIsSignIn()) {
                break;
            }
        } else if (choice == 2) {
            int stuN;
            string nick;
            string passw;
            string passw2;
            cout << endl;
            cout << "Your student number : ";
            cin >> stuN;
            cout << "Your nickname : ";
            cin >> nick;
            cout << "Your password : ";
            cin >> passw;
            cout << "Your password one more time : ";
            cin >> passw2;
            if (passw2 != passw) {
                cout << endl << "[login fail]\nanother password" << endl << endl;
            } else {
                usermanage.signUp(stuN, nick, passw, false, false);
            }
        } else if (choice == 3) {
            cout << "program exit" << endl;
            return 0;
        } else {
            cout << "you can choice 1 or 2 or 3" << endl;
        }
    }

    cout << "Hello " << usermanage.getLoginedUser().getNickName() << endl;
    cout << "choice one.\n1. lend book\n2. check schedule\n3. program exit\n\nYou : ";
    return 0;

}
