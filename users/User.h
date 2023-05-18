#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "../books/Book.h"

class User
{
public:
    User() {} // 비어있는 User 객체를 만들 필요가 있기에 오버로딩 기능을 이용해 2개의 constructor 생성
    User(int uuid, int studentNumber, std::string nickname, std::string passward, bool isEru = false, bool isManager = false, int lendBookN = 0);
    int getId() const;
    int getStudentNumber() const;
    std::string getNickName() const;
    bool getIsEru() const;
    bool getIsManager() const;
    int getLendBookNum() const;

    // 아래의 set 함수들은 valid 과정을 겪음
    // 예를 들어 setNickName을 하면 영어, 숫자로만 되어있는지, 5자 넘는지, 기존에 있던 아이디인지 등을 체크
    void setStudentNumber(int newStudentNumber);
    void setNickName(std::string newNickName);
    void setPassward(std::string originPassward, std::string newPassward);
    void setPassward(std::string newPassward);
    void setIsEru(bool newIsEru);

    // Password는 보안상의 이유로 get 함수를 만들지 않음, 따라서 누군가 로그인했을 때
    // 해당 Password가 올바른지 확인할 필요가 있음. 아래의 함수는 그 기능을 수행
    // 이렇게 하면 프론트앤드 쪽에서 비밀번호를 알아낼 수 없음 (형식상 의미)
    bool isValidPassword(std::string validPassword); // 비밀번호가 유효한지 유효성 검사
    void lendBook();                                 // 책의 수 +1, valid : max 값 보다 커지면 경고문, 바로 return
    void returnBook();                               // 책의 수 -1, valid : 0 보다 작아지면 경고문, 바로 return
private:
    int uuid;             // User 데이터가 저장될 때 기본적으로 가지는 값
    int studentNumber;    // 학번
    std::string nickname; // ID
    std::string passward; // 비번
    bool isEru;           // 에루인지 아닌지, default false
    bool isManager;       // 관리자인지 아닌지, default false
    int lendBookNum;      // 책 빌린 횟수
    int lendBookMaxNum;   // 책 빌릴 수 있는 최대 수
};

#endif