
#include <GL/glew.h>

#include <imgui/imgui.h>

#include "test_clear_color.h"

namespace test{

TestClearColor::TestClearColor() : m_clear_color{0.2f, 0.3f, 0.6f, 1.0f} {

}

TestClearColor::~TestClearColor() {}

void TestClearColor::onUpdate(float delta_time) {}

void TestClearColor::onRender() {
  glClearColor(m_clear_color[0], m_clear_color[1], m_clear_color[2], m_clear_color[3]);
  glClear(GL_COLOR_BUFFER_BIT);
}

void TestClearColor::onImguiRender() {
  ImGui::ColorEdit4("Clear Color", m_clear_color);
}

}