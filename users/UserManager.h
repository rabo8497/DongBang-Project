#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include <iostream>
#include "../fileHandler.h"
#include "User.h"

class UserManager : public FileHandler
{
public:
    UserManager();
    bool getIsSignIn() const; // 로그인 되어있는지 체크
    User &getLoginedUser();   // 로그인 되어있을 경우 그 User를 반환하는 함수, 다른 곳에서 필요하다면 가져다 쓰면 되 (ex. 댓글 쓴사람이 누군지)

    int findIdFromItem(std::string); // nickname이 주어졌을 때, 해당 uuid를 반환하는 함수
    std::string findNickFromId(int);
    void signUp(int, std::string, std::string, bool, bool); // 회원가입, txt에 정보 추가
    void signIn(std::string, std::string);                  // 로그인
    void signOut();                                         // 로그아웃

    // 아래는 FileHandler에서 상속받아 오버로딩 하는 함수임
    void load(int);                // txt 파일로부터 특정 uuid를 갖는 User을 nowUser에 저장하는 기능
    void write(User, std::string); // txt 파일에 저장하는 기능
    void modifyFile();
    void deleteFile(int);

private:
    int latestId;  // 가장 최근의 uuid를 저장하는 곳
    bool isSignIn; // 로그인 되어있는지, default false
    User nowUser;  // 빈 User, 로그인 하면 로그인 한 계정의 User가 저장됨
};

#endif