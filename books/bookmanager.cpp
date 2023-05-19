#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>

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

void BookManager::bookadd(std::string bookName, std::string bookSeries, std::string bookAuthor, std::string bookPub, std::string bookDate, int bookCount, bool isCanLend)
{
  Book newBook(getLatestId() + 1, bookName, bookSeries, bookAuthor, bookPub, bookDate, bookCount, isCanLend);
  write(newBook);
  latestId = getLatestId();
}

void BookManager::booklist(int listpage)
{
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
  }
  for (int bookId = (listpage - 1) * 5 + 1; bookId <= listpage * 5; bookId++)
  {
    if (bookId <= lineNum / 5)
    {
      load(bookId);
      nowBook.BookInfo();
      std::cout << std::endl;
    }
  }
}
void BookManager::booksearch(std::string findBook)
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
    return;
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

  std::cout << "Search Result" << std::endl;
  for (auto i : searchResult)
  {
    std::cout << i[0] << ". " << i[2] << std::endl;
  }
  int resultNum;
  std::cout << "Enter the number of book that you wanna know the information." << std::endl;
  std::cin >> resultNum;
  load(std::stoi(searchResult[resultNum - 1][1]) + 1);
  nowBook.BookInfo();
  std::cout << std::endl;
}

void BookManager::booklend(User &lendUser, int buid)
{
  lendUser.lendBook();
  load(buid);
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
  std::cout << "Loading Book......." << std::endl;
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
  std::cout << "Loading Complete!" << std::endl;
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