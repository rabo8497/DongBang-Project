#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <regex>
#include <ctime>

#include "LendManager.h"
#include "Book.h"
#include "../users/User.h"


LendManager::LendManager() : FileHandler(".\\dataBase\\lend.txt", 10)
{
  latestId = getLatestId();
}

void LendManager::nowTime()
{
  timer = time(NULL);
  t = localtime(&timer);
  timeDate = std::to_string(t->tm_year + 1900) + (t->tm_mon < 9 ? "0" + std::to_string(t->tm_mon + 1) : std::to_string(t->tm_mon + 1)) + (t->tm_mday < 10 ? "0" + std::to_string(t->tm_mday) : std::to_string(t->tm_mday));
}

void LendManager::load(int) {}
void LendManager::write(int uuid, int buid)
{
  nowTime();
  std::string uuidStr = std::to_string(uuid);
  std::string buidStr = std::to_string(buid);
  std::string newluid = std::to_string(latestId + 2);
  std::string saveData = newluid + "\n" + uuidStr + "\n" + buidStr + "\n" + timeDate + "\n" + "\n" + "\n" + "\n" + "\n" + "\n";

  std::ofstream outFile(saveLocation, std::ios::app);
  if (!outFile)
  {
    std::cerr << "cannot open file!!" << std::endl;
    return;
  }
  outFile << saveData << std::endl;
  outFile.close();
}
void LendManager::modifyFile(int, User, Book) {}
void LendManager::deleteFile(int) {}
