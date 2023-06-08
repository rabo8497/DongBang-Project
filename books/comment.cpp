#include "Comment.h"

Comment::Comment(int bookId) : bookId(bookId)
{
    interval = 5;
    saveLocation = "dataBase\\comment.txt";
}

void Comment::write(User nowUser, std::string commentStr)
{
    std::ofstream outFile(saveLocation, std::ios::app);
    if (!outFile)
    {
        std::cerr << RED << "cannot open file" << RESET << std::endl;
        return;
    }
    int newId = getLatestId();
    std::string newIdStr = std::to_string(newId + 1);
    std::string userId = std::to_string(nowUser.getId());
    std::string bookIdStr = std::to_string(bookId);
    std::string saveData = newIdStr + '\n' + bookIdStr + '\n' + userId + '\n' + commentStr + '\n';
    outFile << saveData << std::endl;
    outFile.close();
}

void Comment::load()
{
    std::ifstream inFile(saveLocation);

    if (inFile.is_open())
    {
        int length = 3;
        std::string line;
        int lineNum = 0;
        std::vector<std::string> oneComment(length, "");
        int count = 0;
        while (std::getline(inFile, line))
        {
            lineNum += 1;
            if (count > 0)
            {
                count -= 1;
                oneComment[length - 1 - count] = line;
                if (count == 0)
                {
                    bookComments.push_back(oneComment);
                    std::vector<std::string> oneComment(length, "");
                }
            }
            else if (lineNum % interval == 2)
            {
                if (line == std::to_string(bookId))
                {
                    count = 2;
                    oneComment[0] = line;
                }
            }
        }
        inFile.close();
    }
    else
    {
        std::cerr << "Unable to open file for reading.\n";
    }
}

void Comment::print_comments(UserManager &UM_)
{
    int totalWidth = 78;
    int choiceInterval = 2;

    for (const auto &commentVec : bookComments)
    {
        std::string nick_ = UM_.findNickFromId(std::stoi(commentVec[1]));
        if (nick_ == "")
        {
            std::cerr << RED << "cannot read user data" << RESET << std::endl;
            return;
        }
        std::string comment_ = commentVec[2];
        std::cout << std::setfill(' ');
        std::cout << std::setw(choiceInterval) << std::left << "|"
                  << GREEN << nick_ << RESET << " " << std::setw(totalWidth - choiceInterval - nick_.size() - 2) << std::left << comment_ << "|" << std::endl;
    }
}

void Comment::deleteFile(User &nowUser)
{
    std::ifstream infile(saveLocation);
    std::ofstream outfile(".\\dataBase\\commenttemp.txt");
    int cuid, buid, uuid;
    std::string comment;

    if (infile.is_open() && outfile.is_open())
    {
        while (!infile.eof())
        {
            infile >> cuid >> buid >> uuid;
            getline(infile, comment);
            getline(infile, comment);

            if (!(buid == bookId && uuid == nowUser.getId()))
            {
                outfile << cuid << "\n"
                        << buid << "\n"
                        << uuid << "\n"
                        << comment << "\n"
                        << "\n";
            }
        }
    }

    infile.close();
    outfile.close();

    std::remove(saveLocation.c_str());
    std::rename(".\\dataBase\\commenttemp.txt", saveLocation.c_str());
}