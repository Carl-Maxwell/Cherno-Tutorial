
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

#define GLEW_STATIC
#include <GL/glew.h>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
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
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


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
    // Positions          // UV coords
    -0.5f, -0.5f,          0.0f, 0.0f,
     0.5f, -0.5f,          1.0f, 0.0f,
     0.5f,  0.5f,          1.0f, 1.0f,
    -0.5f,  0.5f,          0.0f, 1.0f
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

  glm::mat4 proj_matrix = glm::ortho(-20.0f, 20.0f, -1.5f, 1.5f, -1.0f, 1.0f);

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
  // Main loop
  //

  float red = 0.01f;

  while (!glfwWindowShouldClose(window)) {
    renderer.clear();

    red += 0.01f;
    red = red < 1.0f ? red : 0.01f;

    shader.bind();
    shader.setUniform4f("u_Color", vec4{red, 0.3f, 0.8f, 1.0f});
    shader.setUniform1i("u_texture", 0);
    shader.setUniform4f("u_model_view_projection_matrix", proj_matrix);

    renderer.draw(vertexArr, indexBuf, shader);

    glfwSwapBuffers(window); // swap front and back buffers

    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}