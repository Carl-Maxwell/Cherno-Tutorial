#pragma once

#include <string>
#include <unordered_map>

#include <GLFW/glfw3.h>

#include "mtypedefs.h"

namespace keyboard{

class Key;

class Keyboard {
public:
  std::vector<bool> keystates;
  std::vector<bool> key_toggles;

  static const i32 SIZE = 121;
  static Keyboard& the() {
    static Keyboard* my_keyboard = nullptr;
    if (!my_keyboard) {
      my_keyboard = new Keyboard;
    }
    return *my_keyboard;
  };

  Keyboard();

  static void keyCallback(GLFWwindow* window, int glfw_key, int scancode, int action, int mods);
  void emitKeyDown(Key key);
  void emitKeyUp(Key key);
};

class Key{
private:
  std::string m_str_key;
  u32 m_int_key; // TODO could use a u8 for this right?
  bool m_pressed;
public:
  Key(std::string identifier);

  inline bool isKeyUp() {
    m_pressed = Keyboard::the().keystates[m_int_key]; 
    return m_pressed;
  }
  inline bool isKeyToggled() { return Keyboard::the().key_toggles[m_int_key]; }

  void setPressed(bool pressed);
  u32 to_int();
  std::string to_str() { return m_str_key; };
  
  static std::string fromGlfwKeyToStr(i32 glfw_key);
};

} // namespace keyboard
