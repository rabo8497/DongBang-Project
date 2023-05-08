#include "userManager.h"
#include "user.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

UserManager::UserManager() : FileHandler("user.txt", 10)
{
  isSignIn = false;
  latestId = getLatestId();
}

bool UserManager::getIsSignIn() const
{
  return isSignIn;
}

User &UserManager::getLoginedUser()
{
  if (getIsSignIn())
  {
    return nowUser;
  }
  else
  {
    std::cout << "not logined. You have to login to use this function" << std::endl;
    return nowUser; // 빈 유저 객체 반환
  }
}

void UserManager::write(User newUser, std::string password)
{
  int studentNumber = newUser.getStudentNumber();
  bool isEru = newUser.getIsEru();
  bool isManager = newUser.getIsManager();
  int lendBookNum = newUser.getLendBookNum();
  std::string nickname = newUser.getNickName();
  std::string newUUID = std::to_string(latestId + 1);
  std::string studentNumberStr = std::to_string(studentNumber);
  std::string isEruStr = isEru ? "true" : "false";
  std::string isManagerStr = isManager ? "true" : "false";
  std::string lendBookNumStr = std::to_string(lendBookNum);
  std::string saveData = newUUID + "\n" + studentNumberStr + "\n" + nickname + "\n" + password + "\n" + isEruStr + "\n" + isManagerStr + "\n" + lendBookNumStr + "\n" + "\n" + "\n";
  std::ofstream outFile(saveLocation, std::ios::app);
  if (!outFile)
  {
    std::cerr << "cannot open file" << std::endl;
    return;
  }
  outFile << saveData << std::endl;
  outFile.close();
}

int UserManager::findIdFromItem(std::string findNickName)
{
  int findId = -1;
  int nowId = -1;
  std::ifstream inFile(saveLocation);
  if (!inFile)
  {
    std::cerr << "cannot open user.txt file" << std::endl;
    return -1;
  }
  std::string line;
  int lineNum = 0;
  while (std::getline(inFile, line))
  {
    lineNum += 1;
    if (lineNum % interval == 3)
    {
      nowId += 1;
      if (line == findNickName)
      {
        findId = nowId;
      }
    }
  }
  inFile.close();
  return findId;
}

void UserManager::load(int findId)
{
  std::cout << "----------load start----------" << std::endl;
  bool isFind = false;
  std::string findData = "";
  std::ifstream inFile(saveLocation);
  if (!inFile)
  {
    std::cerr << "cannot open user.txt file" << std::endl;
    return;
  }
  std::string line;
  int lineNum = 0;
  while (std::getline(inFile, line))
  {
    lineNum += 1;
    if (lineNum % interval == 1)
    {
      if (std::stoi(line) == findId)
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

  // 각 부분을 적절한 타입으로 변환
  int val1 = std::stoi(tokens[0]);
  int val2 = std::stoi(tokens[1]);
  std::string val3 = tokens[2];
  std::string val4 = tokens[3];
  bool val5 = (tokens[4] == "true" || tokens[4] == "True") ? true : false;
  bool val6 = (tokens[5] == "true" || tokens[5] == "True") ? true : false;
  int val7 = std::stoi(tokens[6]);
  inFile.close();
  nowUser = User(val1, val2, val3, val4, val5, val6, val7);
  std::cout << "----------load end----------" << std::endl;
}

void UserManager::modifyFile(User modifiedUser)
{
  std::ifstream inFile(saveLocation);
  std::ofstream outFile("usertemp.txt");
  std::string findIdStr = std::to_string(modifiedUser.getId());
  int findModifiyBookNum = -1;
  if (!inFile || !outFile)
  {
    std::cerr << "cannot open user.txt file" << std::endl;
    return;
  }

  std::string line;
  int lineNumber = 0;
  while (std::getline(inFile, line))
  {
    lineNumber += 1;
    if (lineNumber == findModifiyBookNum)
    {
      outFile << modifiedUser.getLendBookNum() << std::endl;
    }
    else if (lineNumber % interval == 1 && line == findIdStr)
    {
      outFile << findIdStr << std::endl;
      findModifiyBookNum = lineNumber + 6; // book number은 id로부터 6 떨어진 곳에 저장됨
    }
    else
    {
      outFile << line << std::endl;
    }
  }
  inFile.close();
  outFile.close();

  std::remove(saveLocation.c_str()); // string 타입의 인자를 받지 못하는 함수임 -> char로 강제 변환
  std::rename("usertemp.txt", saveLocation.c_str());
}

void UserManager::deleteFile(int uuid)
{
  // modifyFile 함수 구현 필요
  // 아직 필요성을 못 느꼈기에 가만히 놔둠
  // 거의 쓰지 않는 기능으로 예상되기에 프로젝트 막바지에 추가하면 될듯
}

void UserManager::signUp(int studentNumber, std::string nickname, std::string password, bool isEru = false, bool isManager = false)
{
  int getId = findIdFromItem(nickname);
  if (getId != -1)
  {
    std::cout << "this nickname is aleady exist.\nUse other nickname." << std::endl
              << std::endl;
    return;
  }
  latestId = getLatestId();
  std::cout << "----------save start----------" << std::endl;
  User newUser(latestId + 1, studentNumber, nickname, password, isEru, isManager);
  std::cout << "----------save end----------" << std::endl;
  if (newUser.getId() == -2)
  {
    std::cout << std::endl
              << "[signup fail]" << std::endl
              << "get wrong value, rewrite your information" << std::endl
              << std::endl;
  }
  else
  {
    write(newUser, password);
    latestId += 1;
    std::cout << std::endl
              << "[signup success!]" << std::endl
              << "You can login" << std::endl
              << std::endl;
  }
}

void UserManager::signIn(std::string inputNickName, std::string inputPassword)
{
  int getId = findIdFromItem(inputNickName);
  if (getId == -1)
  {
    std::cout << std::endl
              << "[login fail!]" << std::endl
              << "wrong id" << std::endl
              << std::endl;
  }
  load(getId);
  if (nowUser.isValidPassword(inputPassword))
  {
    std::cout << std::endl
              << "[login success!]" << std::endl
              << std::endl;
    isSignIn = true;
  }
  else
  {
    nowUser = User();
    std::cout << std::endl
              << "[login fail!]" << std::endl
              << "wrong password" << std::endl
              << std::endl;
  }
}

void UserManager::signOut()
{
  nowUser = User();
  isSignIn = false;
  std::cout << std::endl
            << "[logout success!]" << std::endl
            << std::endl;
}