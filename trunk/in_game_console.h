#pragma once

#include <string>
#include <vector>

#include <imgui/imgui.h>

#include "mtypedefs.h"

class Console{
public:
  std::vector<std::string> console_lines;
  u32 console_selected_line;
  bool visible;

  Console::Console();
  static Console& the() {
    static Console* my_console = nullptr;
    if (!my_console) {
      my_console = new Console;
    }
    return *my_console;
  }

  static void Console::draw();
  static void Console::initialize();
};
