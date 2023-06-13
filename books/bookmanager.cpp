// Including necessary libraries
#include <vector>
#include <regex>
#include <cmath>
#include <ctime>

#include "BookManager.h"
#include "Book.h"

// Constructor
BookManager::BookManager() : FileHandler(".\\dataBase\\book.txt", 15)
{
  // Initialize member variables
  saveLocation_lend = ".\\dataBase\\lend.txt";
  interval_lend = 10;
  latestId = getLatestId();
  latestluid = getLatestId_lend();
}

// Function to get the latest lend ID from the file
int BookManager::getLatestId_lend()
{
  int latestluid = -1;
  std::ifstream inFile(saveLocation_lend);

  // If the file is not found, print error and return -2
  if (!inFile)
  {
    std::cout << RED << "cannot open lend.txt file" << RESET << std::endl;
    return -2;
  }

  // Read the file line by line and keep updating the latest ID
  std::string line;
  int lineNum = 0;
  while (std::getline(inFile, line))
  {
    lineNum += 1;
    if (lineNum % interval_lend == 1)
    {
      latestluid = std::stoi(line);
    }
  }
  return latestluid;
}

// Function to add a book lending transaction to the file
void BookManager::lendwrite(int uuid, int buid)
{
  // Get the current time and convert to a date string
  timer = time(NULL);
  t = localtime(&timer);
  timeDate = std::to_string(t->tm_year + 1900) + (t->tm_mon < 9 ? "0" + std::to_string(t->tm_mon + 1) : std::to_string(t->tm_mon + 1)) + (t->tm_mday < 10 ? "0" + std::to_string(t->tm_mday) : std::to_string(t->tm_mday));

  // Convert uuid and buid to string and create the saveData string
  std::string uuidStr = std::to_string(uuid);
  std::string buidStr = std::to_string(buid);
  std::string newluid = std::to_string(getLatestId_lend() + 1);
  std::string saveData = newluid + "\n" + uuidStr + "\n" + buidStr + "\n" + timeDate + "\n" + "\n" + "\n" + "\n" + "\n" + "\n";

  // Open the file in append mode and write the saveData string
  std::ofstream outFile(saveLocation_lend, std::ios::app);
  if (!outFile)
  {
    std::cout << RED << "cannot open file!!" << RESET << std::endl;
    return;
  }
  outFile << saveData << std::endl;
  outFile.close();
}

// Function to delete a book lending transaction from the file
void BookManager::lenddelete(int luid)
{
  // Open the original file and a temporary file
  std::ifstream inFile(saveLocation_lend);
  std::ofstream outFile(".\\dataBase\\lendtemp.txt");
  if (!inFile || !outFile)
  {
    std::cout << RED << "cannot open file!!" << RESET << std::endl;
    return;
  }

  // Read the original file line by line and write to the temporary file, except the lines to be deleted
  std::string line;
  int lineNumber = 0;
  int deleteNum = 0;
  while (std::getline(inFile, line))
  {
    lineNumber += 1;
    if (deleteNum > 0)
    {
      deleteNum -= 1;
      continue;
    }
    else if (lineNumber % interval_lend == 1)
    {
      if (luid == std::stoi(line))
      {
        deleteNum = interval_lend - 1;
      }
      else
      {
        outFile << line << std::endl;
      }
    }
    else
    {
      outFile << line << std::endl;
    }
  }
  inFile.close();
  outFile.close();

  // Remove the original file and rename the temporary file
  std::remove(saveLocation_lend.c_str());
  std::rename(".\\dataBase\\lendtemp.txt", saveLocation_lend.c_str());
}

// Function to get a list of books lent by a user
std::vector<std::vector<std::string>> BookManager::lendlist(User &lenduser)
{
  std::string uidStr = std::to_string(lenduser.getId());
  std::string bookStr = "";
  std::vector<std::vector<std::string>> lendlist;
  std::vector<std::string> temp;
  int index = 0;
  std::ifstream inFile(saveLocation_lend);
  if (!inFile)
  {
    std::cout << RED << "cannot open file!!" << RESET << std::endl;
    return lendlist;
  }

  // Read the file line by line and add the relevant lines to lendlist
  std::string line;
  int lineNum = 0;
  std::string nowLuid;
  std::string nowUuid;
  int lendValNum = 0;
  while (std::getline(inFile, line))
  {
    lineNum += 1;
    if (lineNum % interval_lend == 1)
    {
      nowLuid = line;
    }
    if (lineNum % interval_lend == 2)
    {
      lendValNum = 2;
      nowUuid = line;
      if (nowUuid != uidStr)
      {
        break;
      }
      temp = {std::to_string(index + 1), nowLuid, line};
    }
    else if (lendValNum != 0)
    {
      lendValNum -= 1;

      if (nowUuid != uidStr)
      {
        break;
      }
      temp.push_back(line);
      if (lendValNum == 0)
      {
        lendlist.push_back(temp);
        index += 1;
      }
    }
  };
  inFile.close();

  // Load the book details for each book in lendlist
  for (auto &item : lendlist)
  {
    load(std::stoi(item[3]));
    item.insert(item.begin() + 2, nowBook.getBName());
  }
  return lendlist;
}

// Function to add a book to the file
void BookManager::bookadd(std::string bookName, std::string bookSeries, std::string bookAuthor, std::string bookPub, std::string bookDate, int bookCount, bool isCanLend)
{
  // Check if the book already exists in the file
  std::vector<std::vector<std::string>> temp = booksearch();
  for (auto i : temp)
  {
    if (i[2] == bookName)
    {
      std::cout << RED << "cannot add the duplicate book!!" << RESET << std::endl;
      return;
    }
  }
  // If not, create a new book and add it to the file
  Book newBook(getLatestId() + 1, bookName, bookSeries, bookAuthor, bookPub, bookDate, bookCount, isCanLend);
  write(newBook);
  std::cout << BLUE << "Succesfully added the new book!" << RESET << std::endl;
  latestId = getLatestId();
}

// Function to list all books or a list of searched books
void BookManager::booklist(int listpage, std::vector<std::vector<std::string>> searchResult)
{
  // Define constants for the formatting of the print
  const int totalWidth = 78;
  const int interval = 2;
  std::string printline;

  // Print the header of the list
  std::cout << std::left << std::setfill('-') << std::setw((totalWidth - 8) / 2) << "";
  std::cout << "<Result>";
  std::cout << std::right << std::setfill('-') << std::setw((totalWidth - 8) / 2) << "" << std::endl;
  std::cout << std::setfill(' ');

  // Print the books in the list
  for (int i = (listpage - 1) * bookNumForPage; i <= listpage * bookNumForPage - 1; i++)
  {
    printline = searchResult[i][0] + ". " + searchResult[i][2];
    std::cout << std::setw(interval) << std::left << "|" << std::setw(totalWidth - interval - 2) << std::left << printline
              << "|" << std::endl;
    if (i + 1 >= searchResult.size())
    {
      break;
    }
  }
  // Print the footer of the list
  std::cout << std::left << std::setfill('-') << std::setw((totalWidth - 5) / 2) << "";
  std::cout << "<" << listpage << "/" << (searchResult.size() - 1) / bookNumForPage + 1 << ">";
  std::cout << std::right << std::setfill('-') << std::setw((totalWidth - 5) / 2) << "" << std::endl;
  std::cout << std::setfill(' ');
}

// Function to search for all books
std::vector<std::vector<std::string>> BookManager::booksearch()
{
  std::string lineStr;
  std::vector<std::vector<std::string>> searchResult;
  std::vector<std::string> temp;
  int nowId = -1;
  int index = 0;
  std::ifstream inFile(saveLocation);
  if (!inFile)
  {
    std::cout << RED << "cannot open file!!" << RESET << std::endl;
    return searchResult;
  }
  // Read the file line by line and add each book to searchResult
  std::string line;
  int lineNum = 0;
  while (std::getline(inFile, line))
  {
    lineNum += 1;
    if (lineNum % interval == 2)
    {
      nowId += 1;
      temp = {std::to_string(index + 1), std::to_string(nowId), line};
      searchResult.push_back(temp);
      index += 1;
    }
  };
  inFile.close();
  return searchResult;
}

// Function to search for a specific book
std::vector<std::vector<std::string>> BookManager::booksearch(std::string findBook)
{
  // Convert the search string to lower case for case insensitive searching
  std::transform(findBook.begin(), findBook.end(), findBook.begin(), ::tolower);

  std::vector<std::vector<std::string>> searchResult;
  std::vector<std::string> temp;
  int nowId = -1;
  int index = 0;
  std::ifstream inFile(saveLocation);
  if (!inFile)
  {
    std::cout << RED << "cannot open file!!" << RESET << std::endl;
    return searchResult;
  }

  // Read the file line by line and add each matching book to searchResult
  std::string line;
  int lineNum = 0;
  while (std::getline(inFile, line))
  {
    lineNum += 1;
    if (lineNum % interval == 2)
    {
      nowId += 1;
      std::string lowerLine = line;
      std::transform(lowerLine.begin(), lowerLine.end(), lowerLine.begin(), ::tolower);
      if (lowerLine.find(findBook) != std::string::npos)
      {
        temp = {std::to_string(index + 1), std::to_string(nowId), line};
        searchResult.push_back(temp);
        index += 1;
      }
    }
  };
  inFile.close();
  return searchResult;
}

// Function to lend a book
void BookManager::booklend(User &lendUser, int buid)
{
  // Check if the user has already reached the max lending limit
  if (lendUser.getLendBookNum() >= lendUser.getLendBookMaxNum())
  {
    std::cout << RED << "can't lend more than " << lendUser.getLendBookMaxNum() << " books." << RESET << std::endl;
    return;
  }

  // Load the book to be lent
  load(buid);

  // Check if the book can be lent
  if (!nowBook.getIsCanLend())
  {
    std::cout << RED << "This book is now unavailable!!" << RESET << std::endl;
    return;
  }

  // Increase the number of books the user has lent
  lendUser.lendBook();

  // Decrease the count of the book being lent
  nowBook.setBCount(nowBook.getBCount() - 1);

  // Write the lending information to the lending file
  lendwrite(lendUser.getId(), nowBook.getBuid());

  // Modify the book information in the book file
  modifyFile(nowBook);
}

// Function to return a book
void BookManager::bookreturn(User &backUser, int buid, int luid)
{
  // Get the current time and format it as a string
  timer = time(NULL);
  t = localtime(&timer);
  timeDate = std::to_string(t->tm_year + 1900) + (t->tm_mon < 9 ? "0" + std::to_string(t->tm_mon + 1) : std::to_string(t->tm_mon + 1)) + (t->tm_mday < 10 ? "0" + std::to_string(t->tm_mday) : std::to_string(t->tm_mday));

  // Open the lending file
  std::ifstream inFile(saveLocation_lend);

  // Check if the file opened successfully
  if (!inFile)
  {
    std::cout << RED << "cannot open lend.txt file" << RESET << std::endl;
    return;
  }

  std::string line;
  std::string lendDate;
  int lineNum = 0;
  int checklineNum;

  // Read the lending file line by line
  while (std::getline(inFile, line))
  {
    lineNum += 1;
    // Check if the line number matches the user ID
    if (lineNum % interval_lend == 1)
    {
      if (line == std::to_string(luid))
      {
        // If the line number matches the user ID, remember the line number of the lending date
        checklineNum = lineNum + 3;
      }
    }

    if (lineNum == checklineNum)
    {
      lendDate = line;
      break;
    }
  }
  inFile.close();

  // Extract the year, month and day from the current date and the lending date
  int year1 = std::stoi(timeDate.substr(0, 4));
  int month1 = std::stoi(timeDate.substr(4, 2));
  int day1 = std::stoi(timeDate.substr(6, 2));

  int year2 = std::stoi(lendDate.substr(0, 4));
  int month2 = std::stoi(lendDate.substr(4, 2));
  int day2 = std::stoi(lendDate.substr(6, 2));

  // Construct the current date and the lending date as time_t
  std::tm time1 = {0};
  time1.tm_year = year1 - 1900;
  time1.tm_mon = month1 - 1;
  time1.tm_mday = day1;

  std::tm time2 = {0};
  time2.tm_year = year2 - 1900;
  time2.tm_mon = month2 - 1;
  time2.tm_mday = day2;

  std::time_t timestamp1 = std::mktime(&time1);
  std::time_t timestamp2 = std::mktime(&time2);

  // Calculate the difference in days between the current date and the lending date
  std::time_t diffSeconds = std::difftime(timestamp1, timestamp2);
  int diffDays = std::round(diffSeconds / (24 * 60 * 60));

  // If the book is overdue, print a message
  if (diffDays > maxLendDay)
  {
    std::cout << MAGENTA << "The return of the book is " << diffDays - maxLendDay << " days overdue." << RESET << std::endl;
  }

  // Decrease the number of books the user has borrowed
  backUser.returnBook();

  // Load the returned book
  load(buid);

  // Increase the count of the returned book
  nowBook.setBCount(nowBook.getBCount() + 1);

  // If there are copies of the book available, make the book available for lending
  if (nowBook.getBCount() > 0)
  {
    nowBook.setIsCanLend(true);
  }

  // Delete the lending information from the lending file
  lenddelete(luid);

  // Modify the book information in the book file
  modifyFile(nowBook);
}

// Function to find the book ID from its name
int BookManager::findIdFromItem(std::string findBook)
{
  // Initialize variables
  int findId = -1;                    // Stores the found book ID
  int nowId = -1;                     // Current book ID
  std::ifstream inFile(saveLocation); // Open the book file
  if (!inFile)
  {
    // If the file cannot be opened, print an error message and return -1
    std::cout << RED << "cannot open file!!" << RESET << std::endl;
    return -1;
  }
  std::string line;
  int lineNum = 0;
  while (std::getline(inFile, line))
  {
    lineNum += 1;
    if (lineNum % interval == 2)
    {
      nowId += 1;
      if (line == findBook)
      {
        // If the line matches the findBook, assign the current ID to findId
        findId = nowId;
      }
    }
  }
  inFile.close();
  return findId;
}

// Function to load a book
void BookManager::load(int bookId)
{
  // Initialize variables
  bool isFind = false;                // Flag to indicate if the book with the given ID is found
  std::string findData = "";          // Accumulates the book data in a string
  std::ifstream inFile(saveLocation); // Open the book file
  if (!inFile)
  {
    // If the file cannot be opened, print an error message and return
    std::cout << RED << "cannot open file!!" << RESET << std::endl;
    return;
  }
  std::string line;
  int lineNum = 0;
  while (std::getline(inFile, line))
  {
    lineNum += 1;
    if (lineNum % interval == 1)
    {
      if (std::stoi(line) == bookId)
      {
        // If the current line matches the given book ID, set the flag to true
        isFind = true;
      }
      else
      {
        isFind = false;
      }
    }
    if (isFind)
    {
      // Accumulate the book data by appending each line with an asterisk delimiter
      findData += line;
      findData += '*';
    }
  }
  inFile.close();

  // Process the accumulated book data string and extract individual book attributes
  std::stringstream ss(findData);
  std::string token;
  std::vector<std::string> tokens;
  while (std::getline(ss, token, '*'))
  {
    tokens.push_back(token);
  }
  int val_Buid = std::stoi(tokens[0]);
  std::string val_Bname = tokens[1];
  std::string val_Bseries = tokens[2];
  std::string val_Bauthor = tokens[3];
  std::string val_Bpub = tokens[4];
  std::string val_Bdate = tokens[5];
  int val_Bcount = std::stoi(tokens[6]);
  bool val_Blend = tokens[7] == "True" ? true : false;

  // Create a Book object with the extracted attributes and assign it to nowBook
  nowBook = Book(val_Buid, val_Bname, val_Bseries, val_Bauthor, val_Bpub, val_Bdate, val_Bcount, val_Blend);
}

// Function to write a book
void BookManager::write(Book newBook)
{
  // Extract book attributes from the newBook object
  std::string bookName = newBook.getBName();
  std::string bookSeries = newBook.getBSeries();
  int bookCount = newBook.getBCount();
  std::string bookCountStr = std::to_string(bookCount);
  std::string bookDate = newBook.getBDate();
  std::string bookAuthor = newBook.getBAuthor();
  std::string bookPub = newBook.getBPub();
  bool isCanLend = newBook.getIsCanLend();
  std::string isCanLendStr = isCanLend ? "True" : "False";
  std::string newBuid = std::to_string(newBook.getBuid());

  // Create a string containing the book data in the required format
  std::string saveData = newBuid + "\n" + bookName + "\n" + bookSeries + "\n" + bookAuthor + "\n" + bookPub + "\n" + bookDate + "\n" + bookCountStr + "\n" + isCanLendStr + "\n" + "\n" + "\n" + "\n" + "\n" + "\n" + "\n";

  std::ofstream outFile(saveLocation, std::ios::app);
  if (!outFile)
  {
    // If the file cannot be opened, print an error message and return
    std::cout << RED << "cannot open file!!" << RESET << std::endl;
    return;
  }

  // Write the book data to the file and close it
  outFile << saveData << std::endl;
  outFile.close();
}

// Function to get the current book from the book manager
Book &BookManager::getBook()
{
  // Return the reference to the current book object
  return nowBook;
}

// Function to modify the book information in the book manager file
void BookManager::modifyFile(Book editBook)
{
  std::ifstream inFile(saveLocation);
  std::ofstream outFile(".\\dataBase\\booktemp.txt");
  std::string findIdStr = std::to_string(editBook.getBuid());
  int findModifyBookCount = -1;
  if (!inFile || !outFile)
  {
    // If either the input or output file cannot be opened, print an error message and return
    std::cout << RED << "cannot open file!!" << RESET << std::endl;
    return;
  }

  std::string line;
  int lineNumber = 0;
  while (std::getline(inFile, line))
  {
    lineNumber += 1;
    if (lineNumber == findModifyBookCount)
    {
      // Write the modified book count to the output file
      outFile << editBook.getBCount() << std::endl;
    }
    else if (lineNumber == findModifyBookCount + 1)
    {
      // Write the modified isCanLend value to the output file
      if (editBook.getIsCanLend())
      {
        outFile << "True" << std::endl;
      }
      else
      {
        outFile << "False" << std::endl;
      }
    }
    else if (lineNumber % interval == 1 && line == findIdStr)
    {
      // Write the found ID to the output file and set the count for modifying the book data
      outFile << findIdStr << std::endl;
      findModifyBookCount = lineNumber + 6;
    }
    else
    {
      // Copy the unchanged line to the output file
      outFile << line << std::endl;
    }
  }
  inFile.close();
  outFile.close();

  // Replace the original book.txt file with the modified file
  std::remove(saveLocation.c_str());
  std::rename(".\\dataBase\\booktemp.txt", saveLocation.c_str());
}

// Function to get the number of books displayed per page
int BookManager::getBookNumForPage()
{
  // Return the value of bookNumForPage
  return bookNumForPage;
}
