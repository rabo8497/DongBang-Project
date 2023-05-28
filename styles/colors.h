#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#define BOLD "\033[1m"
#define THIN "\033[2m"
#define ITALIC "\033[3m"
#define UNDER "\033[4m"
#define REVERSE "\033[7m"
#define STRIKE "\033[28m"

std::stringstream ss;

inline const std::string setcolor(short r, short g, short b)
{
    ss.str("");
    ss.clear();
    ss << "\033[38;2;" << r << ";" << g << ";" << b << "m";
    return ss.str();
}

inline const std::string setbackgroundcolor(short r, short g, short b)
{
    ss.str("");
    ss.clear();
    ss << "\033[48;2;" << r << ";" << g << ";" << b << "m";
    return ss.str();
}

enum CursorMoveDir
{
    CURSOR_UP = 'A',
    CURSOR_DOWN = 'B',
    CURSOR_RIGHT = 'C',
    CURSOR_LEFT = 'D',
};

inline std::string gotoxy(int x, int y)
{
    ss.str("");
    ss.clear();
    ss << "\033[" << x << ";" << y << "H";
    return ss.str();
}

inline std::string gotorelativexy(int x, int y)
{
    ss.str("");
    ss.clear();
    ss << "\033[" << x << CURSOR_DOWN << y << CURSOR_RIGHT;
    return ss.str();
}

inline std::string moveto(int distance, CursorMoveDir dir)
{
    ss.str("");
    ss.clear();
    ss << "\033[" << distance << (char)dir;
    return ss.str();
}

inline std::string clrscr()
{
    return "\033[3J";
}

inline void pause()
{
#if __linux__
    std::system("read -p \"press any key to continue...\"");
#elif _WIN32
    std::system("pause");
#else
    std::cout << "Press any key to continue... ";
    int tmp;
    std::cin >> tmp;
#endif
}

#endif