#pragma once

#include "mtypedefs.h"

class IndexBuffer{
private:
  u32 m_renderer_id;
  u32 m_count;
public:
  IndexBuffer(const u32* data, u32 count);
  ~IndexBuffer();

  void bind() const;
  void unbind() const;

  inline u32 getCount() { return m_count; };
};
