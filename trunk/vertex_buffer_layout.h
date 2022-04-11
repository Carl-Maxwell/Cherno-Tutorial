#pragma once

#include <vector>

#define GLEW_STATIC
#include "GL/glew.h"

#include "mtypedefs.h"

#include "renderer.h"

#define ASSERT(x) if (!(x)) __debugbreak();

struct VertexBufferElement {
  u32 type;
  u32 count;
  u8 normalized;

  inline u32 sizeOf() const {
    return VertexBufferElement::getSizeOfType(type) * count;
  };

  static u32 getSizeOfType(u32 type) {
    switch (type) {
      case GL_FLOAT:          return 4;
      case GL_UNSIGNED_INT:   return 4;
      case GL_UNSIGNED_BYTE:  return 1;
    }
    ASSERT(false);
    return 0;
  }
};

class VertexBufferLayout{
private:
  std::vector<VertexBufferElement> m_elements;
  u32 m_stride;
public:
  VertexBufferLayout() : m_stride(0) {};

  template<typename T>
  void push(u32 count) {
    static_assert(false);
  }

  template<>
  void push<f32>(u32 count) { 
    m_elements.push_back(VertexBufferElement{GL_FLOAT, count, GL_FALSE});
    m_stride += m_elements.back().sizeOf();
  }

  template<>
  void push<u32>(u32 count) {
    m_elements.push_back(VertexBufferElement{GL_UNSIGNED_INT, count, GL_FALSE});
    m_stride += m_elements.back().sizeOf();
  }

  inline u32 getStride() const {
    return m_stride;
  }

  inline const std::vector<VertexBufferElement>& getElements() const { 
    return m_elements; 
  };
};