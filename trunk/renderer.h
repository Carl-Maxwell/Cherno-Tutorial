#pragma once

#define GLEW_STATIC
#include <GL/glew.h>

#include "mtypedefs.h"

#include "index_buffer.h"
#include "vertex_array.h"
#include "shader.h"

// #include "glDebugMessageCallback.h"

#define ASSERT(x) if (!(x)) __debugbreak();

class Renderer {
public:
  void draw(
    const VertexArray& vertexArr, 
    const IndexBuffer& indexBuf, 
    const Shader& shader 
  );
  void clear() const { glClear(GL_COLOR_BUFFER_BIT); }
};
