#pragma once

// TODO rename file to mprint or such,
//   something less generic to avoid shadowing other files

#include <string>
#include <iostream>

class Print{
public:
  static void line(std::string msg) {
    std::cout << msg << "\n";
  }
};
