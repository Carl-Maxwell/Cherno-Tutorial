
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

#include "mtypedefs.h"
#include "print.h"

//
// Shader code
//

static u32 compileShader(u32 type, const std::string& source) {
  u32 id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    i32 length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    
    Print::line("failed to compile " + std::string(type == GL_VERTEX_SHADER ? "vertex" : "fragment") + " shader\n");
    Print::line(message);
  }

  return id;
}

static i32 createShader(const std::string& vertexShader, const std::string& fragmentShader) {
  u32 program = glCreateProgram();
  u32 vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  u32 fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

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
  // Initialize graphics
  //

  f32 positions[6] = {
    -0.5f, -0.5f,
     0.0f,  0.5f,
     0.5f, -0.5f
  };

  u32 buffer = 3;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(f32), positions, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(f32) * 2, 0);

  std::string vertexSrc = ""
    "#version 330 core\n"
    "layout(location = 0) in vec4 position;\n"
    "void main() {\n"
    " gl_Position = position;\n"
    "}\n";

  std::string fragmentSrc = ""
    "#version 330 core\n"
    "out vec4 color;\n"
    "void main() {\n"
    " color = vec4(1.0f, 0.0f, 0.0f, 1.0f);\n"
    "}\n";

  u32 shader = createShader(vertexSrc, fragmentSrc);
  glUseProgram(shader);

  //
  // Main loop
  //

  while (!glfwWindowShouldClose(window)) {
    glClear(GL_COLOR_BUFFER_BIT);

    // shader.Bind();
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(window); // swap front and back buffers

    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}