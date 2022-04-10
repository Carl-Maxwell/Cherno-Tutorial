
#include "mtypedefs.h"

#include "renderer.h"
#include "index_buffer.h"

IndexBuffer::IndexBuffer(const u32* data, u32 count) : m_count(count) {
  ASSERT(sizeof(u32) == sizeof(GLuint));

  glGenBuffers(1, &m_renderer_id);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(u32), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
  glDeleteBuffers(1, &m_renderer_id);
}

void IndexBuffer::bind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_renderer_id);
}

void IndexBuffer::unbind() const {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}