#pragma once

// TODO rename file to mprint or such,
//   something less generic to avoid shadowing other files

#include <string>
#include <iostream>

#include "in_game_console.h"

class Print{
public:
  static void line(std::string msg) {
    std::cout << msg << "\n";
    Console::the().console_lines.push_back(msg);
  }
};
