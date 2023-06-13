#include "Comment.h"

// Constructor for the Comment class, which initializes bookId with the provided id.
Comment::Comment(int bookId) : bookId(bookId)
{
    interval = 5;                           // Setting interval to 5
    saveLocation = "dataBase\\comment.txt"; // Set the default save location for comments
}

// Write a comment from a user to the comment file.
bool Comment::write(User nowUser, std::string commentStr)
{
    std::ofstream outFile(saveLocation, std::ios::app); // Open the comment file in append mode

    if (!outFile) // Check if the file was opened successfully
    {
        std::cout << RED << "cannot open file" << RESET << std::endl;
        return false; // If not, print an error and return false
    }

    int newId = getLatestId();                                                                     // Get the latest comment id
    std::string newIdStr = std::to_string(newId + 1);                                              // Convert the id to a string
    std::string userId = std::to_string(nowUser.getId());                                          // Get the user's id and convert it to a string
    std::string bookIdStr = std::to_string(bookId);                                                // Convert the book id to a string
    std::string saveData = newIdStr + '\n' + bookIdStr + '\n' + userId + '\n' + commentStr + '\n'; // Construct the data to be saved
    outFile << saveData << std::endl;                                                              // Write the data to the file
    outFile.close();                                                                               // Close the file

    return true; // Return true indicating the comment was written successfully
}

// Load comments from the comment file into the bookComments vector
void Comment::load()
{
    std::ifstream inFile(saveLocation); // Open the comment file for reading

    if (inFile.is_open()) // Check if the file was opened successfully
    {
        int length = 3; // The number of lines that make up a comment
        std::string line;
        int lineNum = 0;
        std::vector<std::string> oneComment(length, ""); // Temporary storage for one comment
        int count = 0;

        while (std::getline(inFile, line)) // Read each line from the file
        {
            lineNum += 1;
            if (count > 0)
            {
                count -= 1;
                oneComment[length - 1 - count] = line;
                if (count == 0)
                {
                    bookComments.push_back(oneComment);              // Add the comment to bookComments
                    std::vector<std::string> oneComment(length, ""); // Reset oneComment
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

        inFile.close(); // Close the file
    }
    else // If the file could not be opened
    {
        std::cout << "Unable to open file for reading.\n"; // Print an error message
    }
}

// Print a specific page of comments
bool Comment::print_comments(UserManager &UM_, int page)
{
    // Setting some constants
    int totalWidth = 78;
    int choiceInterval = 2;
    int commentsPerPage = 3;

    // Check if there are any comments
    if (bookComments.size() == 0)
    {
        return true; // If not, return true
    }

    // Validate the page number
    if (page <= 0)
    {
        std::cout << std::left << std::setw(choiceInterval) << "|" << RED << std::left << std::setw(totalWidth - choiceInterval - 1) << "Invalid page number. Page number should be greater than 0." << RESET << "|" << std::endl;
        return false; // If the page number is invalid, print an error and return false
    }

    // Calculate the index range for the comments on this page
    int startIndex = (page - 1) * commentsPerPage;
    int endIndex = startIndex + commentsPerPage;
    int totalPage = (bookComments.size() - 1) / commentsPerPage + 1;

    // Check if the page number is valid
    if (startIndex >= bookComments.size())
    {
        std::cout << std::left << std::setw(choiceInterval) << "|" << RED << std::left << std::setw(totalWidth - choiceInterval - 1) << " Invalid page number.There are not enough comments." << RESET << "|" << std::endl;
        return false; // If the page number is invalid, print an error and return false
    }

    // Print each comment on this page
    for (int i = startIndex; i < endIndex && i < bookComments.size(); i++)
    {
        std::string nick_ = UM_.findNickFromId(std::stoi(bookComments[i][1]));
        if (nick_ == "")
        {
            std::cout << RED << "cannot read user data" << RESET << std::endl;
            return false;
        }
        std::string comment_ = bookComments[i][2];
        std::cout << std::setfill(' ');
        std::cout << std::setw(choiceInterval) << std::left << "|"
                  << GREEN << nick_ << RESET << " " << std::setw(totalWidth - choiceInterval - nick_.size() - 2) << std::left << comment_ << "|" << std::endl;
    }

    // Print the page number and total number of pages
    std::string pageInfo = "<" + std::to_string(page) + "/" + std::to_string(totalPage) + ">";
    std::cout << std::setfill('-') << std::setw((totalWidth - pageInfo.size()) / 2) << "-"
              << pageInfo
              << std::setfill('-') << std::setw((totalWidth - pageInfo.size()) / 2) << "-" << std::endl;

    return true; // Return true indicating the operation was successful
}

// Delete the comments of a specific user for this book
void Comment::deleteFile(User &nowUser)
{
    std::ifstream infile(saveLocation);                    // Open the comment file for reading
    std::ofstream outfile(".\\dataBase\\commenttemp.txt"); // Open a temporary file for writing
    int cuid, buid, uuid;
    std::string comment;

    if (infile.is_open() && outfile.is_open()) // Check if the files were opened successfully
    {
        while (infile >> cuid >> buid >> uuid) // Read each comment from the file
        {
            getline(infile >> std::ws, comment);

            if (!(buid == bookId && uuid == nowUser.getId())) // If the comment is not by the user for this book
            {
                // Write the comment to the temporary file
                outfile << cuid << "\n"
                        << buid << "\n"
                        << uuid << "\n"
                        << comment << "\n"
                        << "\n";
            }
        }
    }
    else // If the files could not be opened
    {
        std::cout << "cannot open comment.txt file" << std::endl; // Print an error message
    }

    infile.close();  // Close the comment file
    outfile.close(); // Close the temporary file

    // Replace the comment file with the temporary file, effectively deleting the user's comments for this book
    std::remove(saveLocation.c_str());
    std::rename(".\\dataBase\\commenttemp.txt", saveLocation.c_str());
}
