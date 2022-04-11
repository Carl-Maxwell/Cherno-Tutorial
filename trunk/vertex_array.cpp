#pragma once

#include "vertex_array.h"

#include "renderer.h"
#include "vertex_buffer.h"
#include "vertex_buffer_layout.h"

VertexArray::VertexArray() {
  glGenVertexArrays(1, &m_renderer_id);
}
VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &m_renderer_id);
}

void VertexArray::AddBuffer(
  const VertexBuffer& vertexBuf, 
  const VertexBufferLayout& layout
) {
  bind();
  vertexBuf.bind();
  
  const auto& elements = layout.getElements();
  u32 offset = 0;
  for (u32 i = 0; i < elements.size(); i++) {
    const auto& element = elements[i];
    glEnableVertexAttribArray(i);
    glVertexAttribPointer(
      i, 
      element.count, 
      element.type, 
      element.normalized, 
      layout.getStride(), 
      (const void*)offset
    );
    offset += element.sizeOf();
  }
}

void VertexArray::bind() const {
  glBindVertexArray(m_renderer_id);
}

void VertexArray::unbind() const {
  glBindVertexArray(0);
}
