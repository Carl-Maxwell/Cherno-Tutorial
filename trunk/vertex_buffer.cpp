
#include "renderer.h"

#include "vertex_buffer.h"

VertexBuffer::VertexBuffer(const void* data, u32 size) {
  glGenBuffers(1, &m_renderer_id);
  glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &m_renderer_id);
}

void VertexBuffer::bind() const {
  glBindBuffer(GL_ARRAY_BUFFER, m_renderer_id);
}
void VertexBuffer::unbind() const {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}