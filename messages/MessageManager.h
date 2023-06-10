#ifndef MESSAGEMANAGER_H
#define MESSAGEMANAGER_H

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


class MessageManager : public FileHandler
{
private:
    int fromId;
    std::vector<std::vector<std::string>> messages;

public:
    MessageManager() {};
    MessageManager(int);
    bool write(int, std::string, std::string);
    void load();
    bool print_messages(UserManager &, int &);
    void open_message(UserManager &, int);
};

#endif
