#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include "Book.h"

class User {
public :
    User(int uuid = -1, int studentNumber = -1, std::string nickname = "none", std::string passward = "none", bool isEru=false, bool isManager=false);
    int getId() const;
    int getStudentNumber() const;
    std::string getNickName() const;
    bool getIsEru() const;
    bool getIsManager() const;

    void setNickName(std::string newNickName);
    void setPassward(std::string originPassward, std::string newPassward);
    void setIsEru(bool newIsEru);
private :
    const int uuid;
    const int studentNumber;
    std::string nickname;
    std::string passward;
    bool isEru;
    bool isManager;
    std::vector<Book> lendBook;
};

#endif
