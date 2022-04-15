
#include <string>
#include <unordered_map>

#include <GLFW/glfw3.h>

#include "print.h"
#include "mtypedefs.h"
#include "keyboard.h"

namespace keyboard{

//-----------------------------------------------------------------------------
// Keyboard class
//-----------------------------------------------------------------------------

Keyboard::Keyboard() {
  keystates  .reserve(Keyboard::SIZE);
  key_toggles.reserve(Keyboard::SIZE);

  for (i32 i = 0; i < 256; i++) {
    keystates.push_back(false);
    key_toggles.push_back(false);
  }
}

void Keyboard::emitKeyDown(Key key) {

}

void Keyboard::emitKeyUp(Key key) {

}

void Keyboard::keyCallback(GLFWwindow* window, int glfw_key, int scancode, int action, int mods) {
  auto& keyboard = Keyboard::the();

  std::string str_key = Key::fromGlfwKeyToStr(glfw_key);
  Key key(str_key);

  bool old = keyboard.keystates[ key.to_int() ];

  if (action == GLFW_PRESS) {
    key.setPressed(true);
    keyboard.keystates[key.to_int()] = true;
    if (old != true) { // it was up, now it's down
      keyboard.emitKeyDown(key);
    }
  } else if (action == GLFW_RELEASE) {
    key.setPressed(false);
    keyboard.keystates[key.to_int()] = false;
    if (old == true) { // it was down, now it's up
      keyboard.emitKeyUp(key);
      keyboard.key_toggles[key.to_int()] = !keyboard.key_toggles[key.to_int()];
    }
  }
}

//-----------------------------------------------------------------------------
// Key class
//-----------------------------------------------------------------------------


inline void Key::setPressed(bool pressed) {
  m_pressed = pressed;
}

Key::Key(std::string str_key) {
  m_str_key = str_key;
  m_int_key = u32(-1);
  m_int_key = to_int();
  m_pressed = Keyboard::the().keystates[ m_int_key ];
}

//-----------------------------------------------------------------------------
//  Lists of keys, map scancodes to keys, etc
//-----------------------------------------------------------------------------

// TODO should alias things like lowercase letters, and whatnot

u32 Key::to_int() {
  if (m_int_key != u32(-1)) {
    return m_int_key;
  }

  const std::string array_of_key_strs[] = {
    "error unknown key",
    " ",
    "'",
    ",",
    "-",
    ".",
    "/",
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    ";",
    "=",
    "A",
    "B",
    "C",
    "D",
    "E",
    "F",
    "G",
    "H",
    "I",
    "J",
    "K",
    "L",
    "M",
    "N",
    "O",
    "P",
    "Q",
    "R",
    "S",
    "T",
    "U",
    "V",
    "W",
    "X",
    "Y",
    "Z",
    "[",
    "\\",
    "]",
    "`",
    "world 1",
    "world 2",
    "esc",
    "enter",
    "tab",
    "backspace",
    "insert",
    "delete",
    "right",
    "left",
    "down",
    "up",
    "page up",
    "page down",
    "home",
    "end",
    "capslock",
    "scroll lock",
    "num lock",
    "print screen",
    "pause",
    "f1",
    "f2",
    "f3",
    "f4",
    "f5",
    "f6",
    "f7",
    "f8",
    "f9",
    "f10",
    "f11",
    "f12",
    "f13",
    "f14",
    "f15",
    "f16",
    "f17",
    "f18",
    "f19",
    "f20",
    "f21",
    "f22",
    "f23",
    "f24",
    "f25",
    "keypad 0",
    "keypad 1",
    "keypad 2",
    "keypad 3",
    "keypad 4",
    "keypad 5",
    "keypad 6",
    "keypad 7",
    "keypad 8",
    "keypad 9",
    ".",
    "/",
    "*",
    "-",
    "+",
    "enter",
    "=",
    "left shift",
    "left control",
    "left alt",
    "left super",
    "right shift",
    "right control",
    "right alt",
    "right super",
    "menu"
  };

  for (int i = 0; i < Keyboard::SIZE; i++) {
    if (array_of_key_strs[i] == m_str_key) {
      return i;
    }
  }

  // aliases

  if (m_str_key == "~") { return 48; }

  return 0;
}

std::string Key::fromGlfwKeyToStr(i32 glfw_key) {
  switch(glfw_key) {
    case GLFW_KEY_UNKNOWN       : return "error unknown key";
    case GLFW_KEY_SPACE         : return " ";
    case GLFW_KEY_APOSTROPHE    : return "'";  /* ' */
    case GLFW_KEY_COMMA         : return ",";  /* , */
    case GLFW_KEY_MINUS         : return "-";  /* - */
    case GLFW_KEY_PERIOD        : return ".";  /* . */
    case GLFW_KEY_SLASH         : return "/";  /* / */
    case GLFW_KEY_0             : return "0";
    case GLFW_KEY_1             : return "1";
    case GLFW_KEY_2             : return "2";
    case GLFW_KEY_3             : return "3";
    case GLFW_KEY_4             : return "4";
    case GLFW_KEY_5             : return "5";
    case GLFW_KEY_6             : return "6";
    case GLFW_KEY_7             : return "7";
    case GLFW_KEY_8             : return "8";
    case GLFW_KEY_9             : return "9";
    case GLFW_KEY_SEMICOLON     : return ";";  /* ; */
    case GLFW_KEY_EQUAL         : return "=";  /* = */
    case GLFW_KEY_A             : return "A";
    case GLFW_KEY_B             : return "B";
    case GLFW_KEY_C             : return "C";
    case GLFW_KEY_D             : return "D";
    case GLFW_KEY_E             : return "E";
    case GLFW_KEY_F             : return "F";
    case GLFW_KEY_G             : return "G";
    case GLFW_KEY_H             : return "H";
    case GLFW_KEY_I             : return "I";
    case GLFW_KEY_J             : return "J";
    case GLFW_KEY_K             : return "K";
    case GLFW_KEY_L             : return "L";
    case GLFW_KEY_M             : return "M";
    case GLFW_KEY_N             : return "N";
    case GLFW_KEY_O             : return "O";
    case GLFW_KEY_P             : return "P";
    case GLFW_KEY_Q             : return "Q";
    case GLFW_KEY_R             : return "R";
    case GLFW_KEY_S             : return "S";
    case GLFW_KEY_T             : return "T";
    case GLFW_KEY_U             : return "U";
    case GLFW_KEY_V             : return "V";
    case GLFW_KEY_W             : return "W";
    case GLFW_KEY_X             : return "X";
    case GLFW_KEY_Y             : return "Y";
    case GLFW_KEY_Z             : return "Z";
    case GLFW_KEY_LEFT_BRACKET  : return "[";  /* [ */
    case GLFW_KEY_BACKSLASH     : return "\\";  /* \ */
    case GLFW_KEY_RIGHT_BRACKET : return "]";  /* ] */
    case GLFW_KEY_GRAVE_ACCENT  : return "`";  /* ` */ // TODO alias ~ to `
    case GLFW_KEY_WORLD_1       : return "world 1"; /* non-US #1 */
    case GLFW_KEY_WORLD_2       : return "world 2"; /* non-US #2 */
    case GLFW_KEY_ESCAPE        : return "esc";
    case GLFW_KEY_ENTER         : return "enter";
    case GLFW_KEY_TAB           : return "tab";
    case GLFW_KEY_BACKSPACE     : return "backspace";
    case GLFW_KEY_INSERT        : return "insert";
    case GLFW_KEY_DELETE        : return "delete";
    case GLFW_KEY_RIGHT         : return "right";
    case GLFW_KEY_LEFT          : return "left";
    case GLFW_KEY_DOWN          : return "down";
    case GLFW_KEY_UP            : return "up";
    case GLFW_KEY_PAGE_UP       : return "page up";
    case GLFW_KEY_PAGE_DOWN     : return "page down";
    case GLFW_KEY_HOME          : return "home";
    case GLFW_KEY_END           : return "end";
    case GLFW_KEY_CAPS_LOCK     : return "capslock";
    case GLFW_KEY_SCROLL_LOCK   : return "scroll lock";
    case GLFW_KEY_NUM_LOCK      : return "num lock";
    case GLFW_KEY_PRINT_SCREEN  : return "print screen";
    case GLFW_KEY_PAUSE         : return "pause";
    case GLFW_KEY_F1            : return "f1";
    case GLFW_KEY_F2            : return "f2";
    case GLFW_KEY_F3            : return "f3";
    case GLFW_KEY_F4            : return "f4";
    case GLFW_KEY_F5            : return "f5";
    case GLFW_KEY_F6            : return "f6";
    case GLFW_KEY_F7            : return "f7";
    case GLFW_KEY_F8            : return "f8";
    case GLFW_KEY_F9            : return "f9";
    case GLFW_KEY_F10           : return "f10";
    case GLFW_KEY_F11           : return "f11";
    case GLFW_KEY_F12           : return "f12";
    case GLFW_KEY_F13           : return "f13";
    case GLFW_KEY_F14           : return "f14";
    case GLFW_KEY_F15           : return "f15";
    case GLFW_KEY_F16           : return "f16";
    case GLFW_KEY_F17           : return "f17";
    case GLFW_KEY_F18           : return "f18";
    case GLFW_KEY_F19           : return "f19";
    case GLFW_KEY_F20           : return "f20";
    case GLFW_KEY_F21           : return "f21";
    case GLFW_KEY_F22           : return "f22";
    case GLFW_KEY_F23           : return "f23";
    case GLFW_KEY_F24           : return "f24";
    case GLFW_KEY_F25           : return "f25";
    case GLFW_KEY_KP_0          : return "keypad 0";
    case GLFW_KEY_KP_1          : return "keypad 1";
    case GLFW_KEY_KP_2          : return "keypad 2";
    case GLFW_KEY_KP_3          : return "keypad 3";
    case GLFW_KEY_KP_4          : return "keypad 4";
    case GLFW_KEY_KP_5          : return "keypad 5";
    case GLFW_KEY_KP_6          : return "keypad 6";
    case GLFW_KEY_KP_7          : return "keypad 7";
    case GLFW_KEY_KP_8          : return "keypad 8";
    case GLFW_KEY_KP_9          : return "keypad 9";
    case GLFW_KEY_KP_DECIMAL    : return ".";
    case GLFW_KEY_KP_DIVIDE     : return "/";
    case GLFW_KEY_KP_MULTIPLY   : return "*";
    case GLFW_KEY_KP_SUBTRACT   : return "-";
    case GLFW_KEY_KP_ADD        : return "+";
    case GLFW_KEY_KP_ENTER      : return "enter";
    case GLFW_KEY_KP_EQUAL      : return "=";
    case GLFW_KEY_LEFT_SHIFT    : return "left shift";
    case GLFW_KEY_LEFT_CONTROL  : return "left control";
    case GLFW_KEY_LEFT_ALT      : return "left alt";
    case GLFW_KEY_LEFT_SUPER    : return "left super";
    case GLFW_KEY_RIGHT_SHIFT   : return "right shift";
    case GLFW_KEY_RIGHT_CONTROL : return "right control";
    case GLFW_KEY_RIGHT_ALT     : return "right alt";
    case GLFW_KEY_RIGHT_SUPER   : return "right super";
    case GLFW_KEY_MENU          : return "menu";
  }
  return "error unknown key";
}

} // namespace keyboard
