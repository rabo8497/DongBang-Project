#ifndef COLORS_H
#define COLORS_H

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>

// Text color codes
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

// Text style codes
#define BOLD "\033[1m"
#define THIN "\033[2m"
#define ITALIC "\033[3m"
#define UNDER "\033[4m"
#define REVERSE "\033[7m"
#define STRIKE "\033[28m"

// Function to set the text color using RGB values
inline const std::string setcolor(std::stringstream &parser, short r, short g, short b)
{
    parser.str("");
    parser.clear();
    parser << "\033[38;2;" << r << ";" << g << ";" << b << "m";
    return parser.str();
}

// Function to set the background color using RGB values
inline const std::string setbackgroundcolor(std::stringstream &parser, short r, short g, short b)
{
    parser.str("");
    parser.clear();
    parser << "\033[48;2;" << r << ";" << g << ";" << b << "m";
    return parser.str();
}

// Enumeration for cursor movement direction
enum CursorMoveDir
{
    CURSOR_UP = 'A',
    CURSOR_DOWN = 'B',
    CURSOR_RIGHT = 'C',
    CURSOR_LEFT = 'D',
};

// Function to move the cursor to a specific position
inline std::string gotoxy(std::stringstream &parser, int x, int y)
{
    parser.str("");
    parser.clear();
    parser << "\033[" << x << ";" << y << "H";
    return parser.str();
}

// Function to move the cursor to a relative position
inline std::string gotorelativexy(std::stringstream &parser, int x, int y)
{
    parser.str("");
    parser.clear();
    parser << "\033[" << x << CursorMoveDir::CURSOR_DOWN << y << CursorMoveDir::CURSOR_RIGHT;
    return parser.str();
}

// Function to move the cursor by a specified distance in a specific direction
inline std::string moveto(std::stringstream &parser, int distance, CursorMoveDir dir)
{
    parser.str("");
    parser.clear();
    parser << "\033[" << distance << (char)dir;
    return parser.str();
}

#endif
