#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <string>
#include "fileHandler.h"
#include "user.h"

class UserManager : public FileHandler {
public :
    UserManager();
    bool getIsSignIn() const;
    bool checkValid(int, std::string, std::string) const;
    void setLatestId();
    void signUp(int, std::string, std::string, bool, bool);
    void signIn();

    void load(int) override;
    void write(User, std::string) override;
    void modifyFile(int, const std::string = "") override;
    void deleteFile(int) override;

private :
    int latestId;
    bool isSignIn;
    User nowUser;
};

#endif
