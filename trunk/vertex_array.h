#pragma once

#include "vertex_buffer.h"
// #include "vertex_buffer_layout.h"

class VertexBufferLayout;

class VertexArray{
private:
  u32 m_renderer_id;
public:
  VertexArray();
  ~VertexArray();

  void AddBuffer(const VertexBuffer& vertexBuf, const VertexBufferLayout& layout);

  void bind() const;
  void unbind() const;
};