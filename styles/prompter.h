#ifndef PROMPTER_H
#define PROMPTER_H

#include <string>
#include <vector>

#define BOXWIDTH 40

class Prompter
{
public:
    Prompter() = default;
    ~Prompter() = default;
    void makeBox(std::string, std::vector<std::string>, int = BOXWIDTH);
    void makePagedBox(std::vector<std::string>, std::string, int = BOXWIDTH);
    int makeChoice(std::string);
};

#endif