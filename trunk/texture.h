#pragma once

#include <string>

class Texture{
public:
  unsigned int m_renderer_id;
  std::string m_file_path;
  unsigned char* m_pixels;
  int m_width, m_height, m_bytes_per_pixel;

  Texture(const std::string& path);
  ~Texture();

  void bind(unsigned int slot = 0) const;
  void unbind();

  inline int getWidth()  const { return m_width; };
  inline int getHeight() const { return m_height; };
};
