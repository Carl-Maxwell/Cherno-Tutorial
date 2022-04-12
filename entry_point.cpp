
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

//
// Entry point
//

int main() {
  std::cout << "Hello world!\n";

  //
  // Initialize window & context (glfw)
  //

  GLFWwindow* window;

  if (!glfwInit()) return -1;

  const char* glsl_version = "#version 330";

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  int WIDTH = 1280, HEIGHT = 720;
  // int WIDTH = 1920, HEIGHT = 1080;

  // glfwGetPrimaryMonitor() param before last

  window = glfwCreateWindow(WIDTH, HEIGHT, "Urbarak 3d", NULL, NULL);
  if (!window) {
    glfwTerminate();
    return -1;
  }

  // Application::the().window = window;

  glfwMakeContextCurrent(window);

  // glfwSetKeyCallback(window, key_callback);
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
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
  }

  // Enable openGL debugging

  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(GLDebugMessageCallback, NULL);

  //
  // Initialize graphics
  //

  f32 positions[] = {
   // Positions           // UV coords
     -50.0f, -50.0f,          0.0f, 0.0f,
      50.0f, -50.0f,          1.0f, 0.0f,
      50.0f,  50.0f,          1.0f, 1.0f,
     -50.0f,  50.0f,          0.0f, 1.0f
  };

  u32 indices[] = {
    0, 1, 2,
    2, 3, 0
  };

  const u32 number_of_vertices = 4;
  const u32 vertice_components = 4;

  VertexArray vertexArr;
  VertexBuffer vertexBuff(positions, sizeof(f32) * number_of_vertices * vertice_components);

  VertexBufferLayout layout;
  layout.push<f32>(2);
  layout.push<f32>(2);
  vertexArr.AddBuffer(vertexBuff, layout);

  IndexBuffer indexBuf(indices, 6);

  glm::mat4 proj_matrix = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
  glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
  glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

  glm::mat4 model_view_projection_matrix = proj_matrix * view * model;

  // Load images

  Texture texture("resources/images/badguy.png");
  texture.bind();

  // Shader stuff

  Shader shader("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");

  // unbind all that stuff

  glBindVertexArray(0);
  glUseProgram(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  // 

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

  // set imgui styles



  // imgui example state variables
  bool show_demo_window = true;
  bool show_another_window = false;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
  glm::vec3 translation(200, 200, 0);

  //

  glm::vec3 translationA(200, 200, 0);
  glm::vec3 translationB(400, 200, 0);

  //
  // Main loop
  //

  float red = 0.01f;

  while (!glfwWindowShouldClose(window)) {
    renderer.clear();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    red += 0.01f;
    red = red < 1.0f ? red : 0.01f;

    shader.setUniform4f("u_Color", vec4{red, 0.3f, 0.8f, 1.0f});

    shader.bind();
    shader.setUniform1i("u_texture", 0);

    {
      model = glm::translate(glm::mat4(1.0f), translationA);
      model_view_projection_matrix = proj_matrix * view * model;
      shader.setUniform4f("u_model_view_projection_matrix", model_view_projection_matrix);
      renderer.draw(vertexArr, indexBuf, shader);
    }

    {
      model = glm::translate(glm::mat4(1.0f), translationB);
      model_view_projection_matrix = proj_matrix * view * model;
      shader.setUniform4f("u_model_view_projection_matrix", model_view_projection_matrix);
      renderer.draw(vertexArr, indexBuf, shader);
    }
    // imgui interface

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
    if (show_demo_window) ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
      ImGui::Begin("Hello, world!");

      ImGui::SliderFloat3("translation A", &translationA.x, 0.0f, 720.0f);
      ImGui::SliderFloat3("translation B", &translationB.x, 0.0f, 720.0f);

      ImGui::End();
    }

    // 3. Show another simple window.
    if (show_another_window) {
      ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
      ImGui::Text("Hello from another window!");
      if (ImGui::Button("Close Me")) show_another_window = false;
      ImGui::End();
    }

    // end imgui interface

    // render imgui
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window); // swap front and back buffers

    glfwPollEvents();
  }

  // Cleanup imgui
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();

  glfwTerminate();

  return 0;
}