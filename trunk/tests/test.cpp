
#include <vector>
#include <string>
#include <functional>
#include <utility>

#include <imgui/imgui.h>

#include "print.h"

#include "test.h"

namespace test{

TestMenu::TestMenu(Test*& current_test_ptr) : m_current_test(current_test_ptr) {

}

void TestMenu::onImguiRender() {
  for (auto& test : m_tests) {
    if (ImGui::Button(test.first.c_str())) {
      m_current_test = test.second();
    }
  } 
}

}
