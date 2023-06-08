#include "Comment.h"

Comment::Comment(int bookId) : bookId(bookId)
{
    interval = 5;
    saveLocation = "dataBase\\comment.txt";
}

bool Comment::write(User nowUser, std::string commentStr)
{
    std::ofstream outFile(saveLocation, std::ios::app);
    if (!outFile)
    {
        std::cerr << RED << "cannot open file" << RESET << std::endl;
        return false;
    }
    int newId = getLatestId();
    std::string newIdStr = std::to_string(newId + 1);
    std::string userId = std::to_string(nowUser.getId());
    std::string bookIdStr = std::to_string(bookId);
    std::string saveData = newIdStr + '\n' + bookIdStr + '\n' + userId + '\n' + commentStr + '\n';
    outFile << saveData << std::endl;
    outFile.close();
    return true;
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

bool Comment::print_comments(UserManager &UM_, int page)
{
    int totalWidth = 78;
    int choiceInterval = 2;
    int commentsPerPage = 3;

    if (bookComments.size() == 0)
    {
        return true;
    }
    if (page <= 0)
    {
        std::cout << std::left << std::setw(choiceInterval) << "|" << RED << std::left << std::setw(totalWidth - choiceInterval - 1) << "Invalid page number. Page number should be greater than 0." << RESET << "|" << std::endl;
        return false;
    }

    int startIndex = (page - 1) * commentsPerPage;
    int endIndex = startIndex + commentsPerPage;
    int totalPage = (bookComments.size() - 1) / commentsPerPage + 1;

    if (startIndex >= bookComments.size())
    {
        std::cout << std::left << std::setw(choiceInterval) << "|" << RED << std::left << std::setw(totalWidth - choiceInterval - 1) << " Invalid page number.There are not enough comments." << RESET << "|" << std::endl;
        return false;
    }

    for (int i = startIndex; i < endIndex && i < bookComments.size(); i++)
    {
        std::string nick_ = UM_.findNickFromId(std::stoi(bookComments[i][1]));
        if (nick_ == "")
        {
            std::cerr << RED << "cannot read user data" << RESET << std::endl;
            return false;
        }
        std::string comment_ = bookComments[i][2];
        std::cout << std::setfill(' ');
        std::cout << std::setw(choiceInterval) << std::left << "|"
                  << GREEN << nick_ << RESET << " " << std::setw(totalWidth - choiceInterval - nick_.size() - 2) << std::left << comment_ << "|" << std::endl;
    }

    std::string pageInfo = "<" + std::to_string(page) + "/" + std::to_string(totalPage) + ">";
    std::cout << std::setfill('-') << std::setw((totalWidth - pageInfo.size()) / 2) << "-"
              << pageInfo
              << std::setfill('-') << std::setw((totalWidth - pageInfo.size()) / 2) << "-" << std::endl;

    return true;
}

void Comment::deleteFile(User &nowUser)
{
    std::ifstream infile(saveLocation);
    std::ofstream outfile(".\\dataBase\\commenttemp.txt");
    int cuid, buid, uuid;
    std::string comment;

    if (infile.is_open() && outfile.is_open())
    {
        while (infile >> cuid >> buid >> uuid)
        {
            getline(infile >> std::ws, comment);

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
    else
    {
        std::cout << "cannot open comment.txt file" << std::endl;
    }

    infile.close();
    outfile.close();

    std::remove(saveLocation.c_str());
    std::rename(".\\dataBase\\commenttemp.txt", saveLocation.c_str());
}