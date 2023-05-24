#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <iomanip>

#include "BookManager.h"
#include "Book.h"

BookManager::BookManager() : FileHandler(".\\dataBase\\book.txt", 15)
{
  saveLocation_lend = ".\\dataBase\\lend.txt";
  interval_lend = 10;
  latestId = getLatestId();
  latestluid = getLatestId_lend();
}

int BookManager::getLatestId_lend()
{
  int latestluid = -1;
  std::ifstream inFile(saveLocation_lend);

  if (!inFile)
  {
    std::cerr << "cannot open lend.txt file" << std::endl;
    return -2;
  }

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

void BookManager::lendwrite(int uuid, int buid, std::string lb)
{
  timer = time(NULL);
  t = localtime(&timer);
  timeDate = std::to_string(t->tm_year + 1900) + (t->tm_mon < 9 ? "0" + std::to_string(t->tm_mon + 1) : std::to_string(t->tm_mon + 1)) + (t->tm_mday < 10 ? "0" + std::to_string(t->tm_mday) : std::to_string(t->tm_mday));

  std::string uuidStr = std::to_string(uuid);
  std::string buidStr = std::to_string(buid);
  std::string newluid = std::to_string(getLatestId_lend() + 1);
  std::string saveData = newluid + "\n" + uuidStr + "\n" + buidStr + "\n" + lb + "\n" + timeDate + "\n" + "\n" + "\n" + "\n" + "\n";

  std::ofstream outFile(saveLocation_lend, std::ios::app);
  if (!outFile)
  {
    std::cerr << "cannot open file!!" << std::endl;
    return;
  }
  outFile << saveData << std::endl;
  outFile.close();
}

void BookManager::lenddelete(int luid)
{
  std::ifstream inFile(saveLocation_lend);
  std::ofstream outFile(".\\dataBase\\lendtemp.txt");
  if (!inFile || !outFile)
  {
    std::cerr << "cannot open lend.txt file" << std::endl;
    return;
  }

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

  std::remove(saveLocation_lend.c_str());
  std::rename(".\\dataBase\\lendtemp.txt", saveLocation_lend.c_str());
}
std::vector<std::vector<std::string>> BookManager::lendlist(User &lenduser)
{
  std::vector<std::vector<std::string>> lendlist;
  int nowId = -1;
  int index = 0;
  std::ifstream inFile(saveLocation);
  if (!inFile)
  {
    std::cerr << "cannot open book.txt file!!" << std::endl;
    return searchResult;
  }
  std::string line;
  int lineNum = 0;
  while (std::getline(inFile, line))
  {
    lineNum += 1;
    if (lineNum % interval == 2)
    {
      nowId += 1;
      lineStr = regex_replace(line, std::regex("[^a-zA-Z-_.]+"), "");
      std::transform(lineStr.begin(), lineStr.end(), lineStr.begin(), ::tolower);
      if (lineStr.find(bookStr) != std::string::npos)
      {
        searchResult.resize(index + 1);
        searchResult[index].push_back(std::to_string(index + 1));
        searchResult[index].push_back(std::to_string(nowId));
        searchResult[index].push_back(line);
        index += 1;
      }
    }
  };
  inFile.close();
}

void BookManager::bookadd(std::string bookName, std::string bookSeries, std::string bookAuthor, std::string bookPub, std::string bookDate, int bookCount, bool isCanLend)
{
  Book newBook(getLatestId() + 1, bookName, bookSeries, bookAuthor, bookPub, bookDate, bookCount, isCanLend);
  write(newBook);
  latestId = getLatestId();
}

void BookManager::booklist(int listpage, std::vector<std::vector<std::string>> searchResult)
{
  const int totalWidth = 78;
  const int interval = 2;
  std::string printline;
  std::cout << std::left << std::setfill('-') << std::setw((totalWidth - 8) / 2) << "";
  std::cout << "<Result>";
  std::cout << std::right << std::setfill('-') << std::setw((totalWidth - 8) / 2) << "" << std::endl;
  std::cout << std::setfill(' ');

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
  std::cout << std::left << std::setfill('-') << std::setw((totalWidth - 5) / 2) << "";
  std::cout << "<" << listpage << "/" << searchResult.size() / 5 + 1 << ">";
  std::cout << std::right << std::setfill('-') << std::setw((totalWidth - 5) / 2) << "" << std::endl;
  std::cout << std::setfill(' ');

  /*int resultNum;
  std::cout << std::endl;
  std::cout << "Enter the number of book that you wanna know the information." << std::endl;
  std::cin >> resultNum;
  load(std::stoi(searchResult[resultNum - 1][1]));
  nowBook.BookInfo();
  std::cout << std::endl;*/
}

std::vector<std::vector<std::string>> BookManager::booksearch()
{
  std::string lineStr;
  std::vector<std::vector<std::string>> searchResult;
  int nowId = -1;
  int index = 0;
  std::ifstream inFile(saveLocation);
  if (!inFile)
  {
    std::cerr << "cannot open book.txt file!!" << std::endl;
    return searchResult;
  }
  std::string line;
  int lineNum = 0;
  while (std::getline(inFile, line))
  {
    lineNum += 1;
    if (lineNum % interval == 2)
    {
      nowId += 1;

      searchResult.resize(index + 1);
      searchResult[index].push_back(std::to_string(index + 1));
      searchResult[index].push_back(std::to_string(nowId));
      searchResult[index].push_back(line);
      index += 1;
    }
  };
  inFile.close();
  return searchResult;
}

std::vector<std::vector<std::string>>
BookManager::booksearch(std::string findBook)
{
  std::string lineStr;
  std::string bookStr = regex_replace(findBook, std::regex("[^a-zA-Z-_.]+"), "");
  std::transform(bookStr.begin(), bookStr.end(), bookStr.begin(), ::tolower);
  std::vector<std::vector<std::string>> searchResult;
  int nowId = -1;
  int index = 0;
  std::ifstream inFile(saveLocation);
  if (!inFile)
  {
    std::cerr << "cannot open book.txt file!!" << std::endl;
    return searchResult;
  }
  std::string line;
  int lineNum = 0;
  while (std::getline(inFile, line))
  {
    lineNum += 1;
    if (lineNum % interval == 2)
    {
      nowId += 1;
      lineStr = regex_replace(line, std::regex("[^a-zA-Z-_.]+"), "");
      std::transform(lineStr.begin(), lineStr.end(), lineStr.begin(), ::tolower);
      if (lineStr.find(bookStr) != std::string::npos)
      {
        searchResult.resize(index + 1);
        searchResult[index].push_back(std::to_string(index + 1));
        searchResult[index].push_back(std::to_string(nowId));
        searchResult[index].push_back(line);
        index += 1;
      }
    }
  };
  inFile.close();
  return searchResult;
}

void BookManager::booklend(User &lendUser, int buid)
{
  load(buid);
  if (!nowBook.getIsCanLend())
  {
    std::cerr << "This book is out of stock!!" << std::endl;
    return;
  }
  lendUser.lendBook();

  nowBook.setBCount(nowBook.getBCount() - 1);
  lendwrite(lendUser.getId(), nowBook.getBuid(), "lend");
  modifyFile(nowBook);
}

void BookManager::bookreturn(User &backUser, int buid)
{
  backUser.returnBook();
  load(buid);
  nowBook.setBCount(nowBook.getBCount() + 1);
  lendwrite(backUser.getId(), nowBook.getBuid(), "return");
  modifyFile(nowBook);
}

int BookManager::findIdFromItem(std::string findBook)
{
  int findId = -1;
  int nowId = -1;
  std::ifstream inFile(saveLocation);
  if (!inFile)
  {
    std::cerr << "cannot open book.txt file!!" << std::endl;
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
        findId = nowId;
      }
    }
  }
  inFile.close();
  return findId;
}

void BookManager::load(int bookId)
{
  bool isFind = false;
  std::string findData = "";
  std::ifstream inFile(saveLocation);
  if (!inFile)
  {
    std::cerr << "cannot open book.txt file!!" << std::endl;
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
        isFind = true;
      }
      else
      {
        isFind = false;
      }
    }
    if (isFind)
    {
      findData += line;
      findData += '*';
    }
  }
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
  inFile.close();
  nowBook = Book(val_Buid, val_Bname, val_Bseries, val_Bauthor, val_Bpub, val_Bdate, val_Bcount, val_Blend);
}

void BookManager::write(Book newBook)
{
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

  std::string saveData = newBuid + "\n" + bookName + "\n" + bookSeries + "\n" + bookAuthor + "\n" + bookPub + "\n" + bookDate + "\n" + bookCountStr + "\n" + isCanLendStr + "\n" + "\n" + "\n" + "\n" + "\n" + "\n" + "\n";

  std::ofstream outFile(saveLocation, std::ios::app);
  if (!outFile)
  {
    std::cerr << "cannot open file!!" << std::endl;
    return;
  }

  outFile << saveData << std::endl;
  outFile.close();
}

Book &BookManager::getBook()
{
  return nowBook;
}
void BookManager::modifyFile(Book editBook)
{
  std::ifstream inFile(saveLocation);
  std::ofstream outFile(".\\dataBase\\booktemp.txt");
  std::string findIdStr = std::to_string(editBook.getBuid());
  int findModifiyBookCount = -1;
  if (!inFile || !outFile)
  {
    std::cerr << "cannot open book.txt file" << std::endl;
    return;
  }

  std::string line;
  int lineNumber = 0;
  while (std::getline(inFile, line))
  {
    lineNumber += 1;
    if (lineNumber == findModifiyBookCount)
    {
      outFile << editBook.getBCount() << std::endl;
    }
    else if (lineNumber % interval == 1 && line == findIdStr)
    {
      outFile << findIdStr << std::endl;
      findModifiyBookCount = lineNumber + 6;
    }
    else
    {
      outFile << line << std::endl;
    }
  }
  inFile.close();
  outFile.close();

  std::remove(saveLocation.c_str());
  std::rename(".\\dataBase\\booktemp.txt", saveLocation.c_str());
}

void BookManager::deleteFile(int bookId) {}