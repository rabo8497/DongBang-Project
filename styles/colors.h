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

inline const std::string setcolor(std::stringstream &parser, short r, short g, short b)
{
    parser.str("");
    parser.clear();
    parser << "\033[38;2;" << r << ";" << g << ";" << b << "m";
    return parser.str();
}

inline const std::string setbackgroundcolor(std::stringstream &parser, short r, short g, short b)
{
    parser.str("");
    parser.clear();
    parser << "\033[48;2;" << r << ";" << g << ";" << b << "m";
    return parser.str();
}

enum CursorMoveDir
{
    CURSOR_UP = 'A',
    CURSOR_DOWN = 'B',
    CURSOR_RIGHT = 'C',
    CURSOR_LEFT = 'D',
};

inline std::string gotoxy(std::stringstream &parser, int x, int y)
{
    parser.str("");
    parser.clear();
    parser << "\033[" << x << ";" << y << "H";
    return parser.str();
}

inline std::string gotorelativexy(std::stringstream &parser, int x, int y)
{
    parser.str("");
    parser.clear();
    parser << "\033[" << x << CURSOR_DOWN << y << CURSOR_RIGHT;
    return parser.str();
}

inline std::string moveto(std::stringstream &parser, int distance, CursorMoveDir dir)
{
    parser.str("");
    parser.clear();
    parser << "\033[" << distance << (char)dir;
    return parser.str();
}

#endif