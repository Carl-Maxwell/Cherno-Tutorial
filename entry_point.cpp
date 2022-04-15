
//
// std includes
//

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

//
// Graphics libraries
//

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include <imgui/imgui_internal.h>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h> // Will drag system OpenGL headers

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

//
// Maxwell libraries
//

#include "mtypedefs.h"
#include "print.h"
#include "mvec3.h"
#include "in_game_console.h"
#include "keyboard.h"

//
// Project Code
//

#include "glDebugMessageCallback.h"
#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_buffer_layout.h"
#include "vertex_array.h"
#include "shader.h"
#include "texture.h"
#include "ui_styling.h"

// Tests

#include "tests/test.h"
#include "tests/test_clear_color.h"

//
// Entry point
//

int main() {
  Print::line("Hello world!");

  //
  // Initialize window & context (glfw)
  //

  GLFWwindow* window;

  if (!glfwInit()) return -1;

  const char* glsl_version = "#version 330";

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // window:
  int WIDTH = 1280, HEIGHT = 720;
  window = glfwCreateWindow(WIDTH, HEIGHT, "Following Cherno OpenGL Tutorial", NULL, NULL);

  // borderless window:
  // int WIDTH = 1920, HEIGHT = 1080;
  // window = glfwCreateWindow(WIDTH, HEIGHT, "Following Cherno OpenGL Tutorial", glfwGetPrimaryMonitor(), NULL);

  if (!window) {
    glfwTerminate();
    return -1;
  }

  glfwMakeContextCurrent(window);

  glfwSetKeyCallback(window, keyboard::Keyboard::keyCallback);
  // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

  //
  // Initialize glew
  //

  {
    GLenum glew_error = glewInit();
    if (glew_error != GLEW_OK) {
      fprintf(stderr, "glew init Error: %s\n", glewGetErrorString(glew_error));
      return -1;
    }
    fprintf(stdout, "Using GLEW %s\n", glewGetString(GLEW_VERSION));
    Print::line("OpenGL version: " + std::string((char*)glGetString(GL_VERSION)) );
  }

  // Enable openGL debugging

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(GLDebugMessageCallback, NULL);

  //
  // Initialize graphics
  //

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  Shader shader("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
  Renderer renderer;

  //
  // Initialize ImGui
  //

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO(); (void)io;

  ImGui::StyleColorsDark();
  defaultImguiSpacing();
  defaultImguiColors();

  ImGui_ImplGlfw_InitForOpenGL(window, true);
  ImGui_ImplOpenGL3_Init(glsl_version);

  test::Test* current_test = nullptr;
  test::TestMenu* test_menu = new test::TestMenu(current_test);
  current_test = test_menu;
  current_test->title = "Test Menu";

  test_menu->registerTest<test::TestClearColor>("Clear Color");

  //
  // Main loop
  //

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    renderer.clear();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    if (current_test) {
      current_test->onUpdate(0.0f);
      current_test->onRender();
      ImGui::Begin(current_test->title.c_str());
      if (current_test != test_menu && ImGui::Button("Back")) {
        delete current_test;
        current_test = test_menu;
      }
      current_test->onImguiRender();
      ImGui::End();
    }

    // Draw the in-game console
    {
      using keyboard::Keyboard;
      using keyboard::Key;

      // show/hide console if tilda is hit (~)
      Console::the().visible = Key("~").isKeyToggled();

      if (Console::the().visible) {
        Console::draw();
      }
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);

    glfwPollEvents();

    // close app if esc is hit
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose(window, true);
    }
  }

  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();

  return 0;
}
