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
#include "../styles/colors.h"

class Comment : public FileHandler
{
private:
    int bookId;                                         // comment ID
    std::vector<std::vector<std::string>> bookComments; // 2D vector stores the comment

public:
    // Parameterized constructor
    Comment(int);

    // write comment information to the file
    bool write(User, std::string);

    // load comment information from the file
    void load();

    // print the comments associated with the bookId provided
    bool print_comments(UserManager &, int);

    // delete comment information from the file
    void deleteFile(User &);
};

#endif
