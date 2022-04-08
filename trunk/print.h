#pragma once

#include <string>
#include <iostream>

class Print{
public:
  static void line(std::string msg) {
    std::cout << msg << "\n";
  }
};
