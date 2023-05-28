#include <iostream>
#include <sstream>
#include <iomanip>
#include "colors.h"
using namespace std;

#include "prompter.h"

void Prompter::makeBox(string title, vector<string> content, int width)
{
    // cout << clrscr();

    gotorelativexy(0, (width - title.length()) / 2);
    cout << title;
    gotorelativexy(1, (width + title.length()) / 2);

    cout << setw(width) << setfill('-') << "" << setfill(' ') << endl
         << endl;

    int idx = 1;
    ostringstream ss;
    for (auto text : content)
    {
        ss << idx << ") " << text;
        cout << "| " << setw(width - 4) << ss.str() << " |" << endl;
        ss.str("");
    }

    cout << endl
         << setw(width) << setfill('-') << "" << setfill(' ') << endl;
}

void Prompter::makePagedBox(vector<string> content, string pageIndex, int width)
{
    // cout << clrscr();
    cout << setw(width) << setfill('-') << "" << setfill(' ') << endl
         << endl;

    int idx = 1;
    ostringstream ss;
    for (auto text : content)
    {
        ss << idx << ") " << text;
        cout << "| " << setw(width - 4) << ss.str() << " |" << endl;
        ss.str("");
    }

    cout << endl
         << setw(width) << setfill('-') << "" << setfill(' ') << endl;

    gotorelativexy(-1, (width - pageIndex.length()) / 2 - 1);
    cout << "<" << pageIndex << ">";
    gotorelativexy(1, -((width + pageIndex.length()) / 2 + 1));
}

int Prompter::makeChoice(string content)
{
    int input;
    cout << content << " > ";
    cin >> input;
    return input;
}