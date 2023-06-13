#include "MessageManager.h"

// Constructor
MessageManager::MessageManager(int userId) : fromId(userId)
{
    interval = 6;
    saveLocation = "dataBase\\message.txt";
}

// Write a new message to the file
bool MessageManager::write(int toUser, std::string title, std::string messageStr)
{
    std::ofstream outFile(saveLocation, std::ios::app); // Open the file in append mode
    if (!outFile)
    {
        std::cout << RED << "cannot open file" << RESET << std::endl; // Display an error message if the file cannot be opened
        return false;
    }
    int newId = getLatestId();                                                                                  // Get the latest message ID
    std::string newIdStr = std::to_string(newId + 1);                                                           // Convert the ID to a string
    std::string userId = std::to_string(fromId);                                                                // Convert the user ID to a string
    std::string toIdStr = std::to_string(toUser);                                                               // Convert the recipient's ID to a string
    std::string saveData = newIdStr + '\n' + toIdStr + '\n' + userId + '\n' + title + '\n' + messageStr + '\n'; // Concatenate the message data
    outFile << saveData << std::endl;                                                                           // Write the message data to the file
    outFile.close();                                                                                            // Close the file
    return true;                                                                                                // Return true to indicate a successful write operation
}

// Load messages from the file
void MessageManager::load()
{
    std::ifstream inFile(saveLocation); // Open the file for reading

    if (inFile.is_open())
    {
        int length = 4;
        std::string line;
        int lineNum = 0;
        std::vector<std::string> oneMessage(length, ""); // Create a vector to store a single message
        int count = 0;
        while (std::getline(inFile, line))
        {
            lineNum += 1;
            if (count > 0)
            {
                count -= 1;
                oneMessage[length - 1 - count] = line; // Store the lines of the message in the vector
                if (count == 0)
                {
                    messages.push_back(oneMessage);                  // Add the complete message to the messages vector
                    std::vector<std::string> oneMessage(length, ""); // Reset the vector for the next message
                }
            }
            else if (lineNum % interval == 2)
            {
                if (line == std::to_string(fromId))
                {
                    count = 3;
                    oneMessage[0] = line; // Store the sender's ID in the message vector
                }
            }
        }
        inFile.close(); // Close the file
    }
    else
    {
        std::cout << "Unable to open file for reading.\n"; // Display an error message if the file cannot be opened
    }
}

// Print messages to the console
bool MessageManager::print_messages(UserManager &UM_, int &page)
{
    std::cout << std::endl;
    int totalWidth = 78;
    int choiceInterval = 2;
    int commentsPerPage = 5;
    std::cout << std::setfill('-') << std::setw((totalWidth)) << "-" << std::endl;
    if (messages.size() == 0)
    {
        return true;
    }
    if (page <= 0)
    {
        page = 1;
        std::cout << std::left << std::setw(choiceInterval) << "|" << RED << std::left << std::setw(totalWidth - choiceInterval - 1) << "Invalid page number. Page number should be greater than 0." << RESET << "|" << std::endl;
    }

    int startIndex = (page - 1) * commentsPerPage;
    int endIndex = startIndex + commentsPerPage;
    int totalPage = (messages.size() - 1) / commentsPerPage + 1;

    if (startIndex >= messages.size())
    {
        page -= 1;
        startIndex = (page - 1) * commentsPerPage;
        endIndex = startIndex + commentsPerPage;
        totalPage = (messages.size() - 1) / commentsPerPage + 1;
        std::cout << std::left << std::setw(choiceInterval) << "|" << RED << std::left << std::setw(totalWidth - choiceInterval - 1) << " Invalid page number. There are not enough messages." << RESET << "|" << std::endl;
    }

    for (int i = startIndex; i < endIndex && i < messages.size(); i++)
    {
        std::string nick_ = UM_.findNickFromId(std::stoi(messages[i][1])); // Get the sender's nickname

        if (nick_ == "")
        {
            std::cout << RED << "cannot read user data" << RESET << std::endl;
            return false;
        }
        std::string comment_ = messages[i][2]; // Get the message content
        std::cout << std::setfill(' ');
        std::cout << std::setw(choiceInterval) << std::left << "|"
                  << i + 1 << ". " << GREEN << nick_ << RESET << " " << std::setw(totalWidth - choiceInterval - nick_.size() - 5) << std::left << comment_ << "|" << std::endl;
    }

    std::string pageInfo = "<" + std::to_string(page) + "/" + std::to_string(totalPage) + ">";
    std::cout << std::setfill('-') << std::setw((totalWidth - pageInfo.size()) / 2) << "-"
              << pageInfo
              << std::setfill('-') << std::setw((totalWidth - pageInfo.size()) / 2) << "-" << std::endl;

    return true;
}

// Open a specific message
void MessageManager::open_message(UserManager &UM_, int m)
{
    m -= 1;
    if (m >= 0 && m < messages.size())
    {
        std::cout << YELLOW << "from : " << RESET << UM_.findNickFromId(std::stoi(messages[m][1])) << std::endl; // Display the sender's nickname
        std::cout << YELLOW << "to : " << RESET << UM_.findNickFromId(std::stoi(messages[m][0])) << std::endl;   // Display the recipient's nickname
        std::cout << YELLOW << "title : " << RESET << messages[m][2] << std::endl;                               // Display the message title
        for (size_t i = 0; i < messages[m][3].size(); i++)
        {
            std::cout << messages[m][3][i]; // Display the message content
            if ((i + 1) % 40 == 0)
            {
                std::cout << '\n'; // Add a newline every 40 characters
            }
        }
        std::cout << std::endl;
        std::string i_;
        std::cout << "(0:back) >> ";
        std::cin.ignore();
        std::getline(std::cin, i_);
        std::cout << std::endl;
    }
    else
    {
        std::cout << RED << "not exist message number" << RESET << std::endl; // Display an error message if the message number is invalid
        return;
    }
}
