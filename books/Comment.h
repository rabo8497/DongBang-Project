#ifndef COMMENT_H
#define COMMENT_H

#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "../styles/colors.h"
#include "../FileHandler.h"
#include "../users/User.h"
#include "../users/UserManager.h"

#define RESET "\033[0m"
#define RED "\033[31m"

class Comment : public FileHandler
{
private:
    int bookId;
    std::vector<std::vector<std::string>> bookComments;

public:
    Comment(int);
    bool write(User, std::string);
    void load();
    bool print_comments(UserManager &, int);
    void deleteFile(User &);
};

#endif
