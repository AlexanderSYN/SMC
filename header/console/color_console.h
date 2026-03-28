//
// Created by AlexanderSYN on 29.03.2026.
//

#ifndef COLOR_CONSOLE_H
#define COLOR_CONSOLE_H

#include <iostream>
#include <windows.h>

#ifdef __STRINGIFY__
    #define STRING_INCLUDED 1
#else
    #include <string>
    #define STRING_INCLUDED 0
#endif

enum color_console
{
    Black        = 0,
    Blue         = 1,
    Green        = 2,
    Cyan         = 3,
    Red          = 4,
    Magenta      = 5,
    Brown        = 6,
    LightGray    = 7,
    DarkGray     = 8,
    LightBlue    = 9,
    LightGreen   = 10,
    LightCyan    = 11,
    LightRed     = 12,
    LightMagenta = 13,
    Yellow       = 14,
    White        = 15
};

namespace ColCons {
    void set_red_color_console();
    void set_green_color_console();
    void set_blue_color_console();
    void set_white_color_console();
    void set_yellow_color_console();
    void set_cyan_color_console();
    void set_magenta_color_console();

    void set_Brown_color_console();
    void set_LightGray_color_console();
    void set_DarkGray_console();
    void set_LightBlue_color_console();
    void set_LightGreen_color_console();
    void set_LightCyan_color_console();
    void set_LightRed_color_console();
}

namespace ColorConsole {
    std::string choice_color(std::string user_input);
}


#endif //COLOR_CONSOLE_H
