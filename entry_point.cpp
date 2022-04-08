
//
// std includes
//

#include <iostream>

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

//
// Maxwell libraries
//

#include "trunk/mtypedefs.h"

//
// Entry point
//


int main() {
  std::cout << "Hello world!\n";

  //
  // Initialize glfw
  //


  GLFWwindow* window;

  if (!glfwInit())
    return -1;

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
      return 0;
    }
    fprintf(stdout, "Using GLEW %s\n", glewGetString(GLEW_VERSION));
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << "\n";
  }

  //
  //
  //

  u32 buffer = 3;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  

  //
  // Main loop
  //

  while (!glfwWindowShouldClose(window))
  {
    glClear(GL_COLOR_BUFFER_BIT);

    // shader.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(window); // swap front and back buffers

    glfwPollEvents();

  }

  glfwTerminate();

  return 0;
}