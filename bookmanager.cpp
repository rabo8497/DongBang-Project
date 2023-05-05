#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "bookmanger.h"
#include "book.h"
BookManager::BookManager() : FileHandler("book.txt", 15)
{
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
    load(bookId);
    nowBook.BookInfo();
    std::cout << std::endl;
  }
}
void BookManager::booksearch(std::string findBook) {}
void BookManager::booklend(User lendUser, std::string bookName)
{
}
void BookManager::bookback(User backUser, std::string bookName) {}

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
  int val_Bdate = std::stoi(tokens[5]);
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
  int bookDate = newBook.getBDate();
  std::string bookDateStr = std::to_string(bookDate);
  std::string bookAuthor = newBook.getBAuthor();
  std::string bookPub = newBook.getBPub();
  bool isCanLend = newBook.getIsCanLend();
  std::string isCanLendStr = isCanLend ? "True" : "False";
  std::string newBuid = std::to_string(latestId + 1);

  std::string saveData = newBuid + "\n" + bookName + "\n" + bookSeries + "\n" + bookAuthor + "\n" + bookPub + "\n" + bookDateStr + "\n" + bookCountStr + "\n" + isCanLendStr + "\n" + "\n" + "\n" + "\n" + "\n" + "\n" + "\n";

  std::ofstream outFile(saveLocation, std::ios::app);
  if (!outFile)
  {
    std::cerr << "cannot open file!!" << std::endl;
    return;
  }

  outFile << saveData << std::endl;
  outFile.close();
}
void BookManager::modifyFile(int bookId, Book editBook) {}
void BookManager::deleteFile(int bookId) {}