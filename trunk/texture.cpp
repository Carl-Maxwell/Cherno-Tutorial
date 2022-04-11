
#include <iostream>
#include <string>

#define GLEW_STATIC
#include <GL/glew.h>

#include "texture.h"

#include "stb_image_namespace.h"

Texture::Texture(const std::string& path)
  : m_renderer_id(0),
  m_file_path(path),
  m_pixels(nullptr),
  m_width(0),
  m_height(0),
  m_bytes_per_pixel(0)
{
  stb::stbi_set_flip_vertically_on_load(true);
  m_pixels = stb::stbi_load(path.c_str(), &m_width, &m_height, &m_bytes_per_pixel, 4);

  std::cout << path << " ,"
    << " width:  " << m_width
    << " height: " << m_height
    << " n: " << m_bytes_per_pixel
    << "\n";

  glGenTextures(1, &m_renderer_id);
  glBindTexture(GL_TEXTURE_2D, m_renderer_id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_pixels);
  glBindTexture(GL_TEXTURE_2D, 0);

  if (m_pixels)
    stb::stbi_image_free(m_pixels);
}

Texture::~Texture() {
  glDeleteTextures(1, &m_renderer_id);
}

void Texture::bind(unsigned int slot) const {
  glActiveTexture(GL_TEXTURE0 + slot);
  glBindTexture(GL_TEXTURE_2D, m_renderer_id);
}

void Texture::unbind() {
  glBindTexture(GL_TEXTURE_2D, 0);
}
