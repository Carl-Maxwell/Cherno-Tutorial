
#include "renderer.h"

void Renderer::draw(
  const VertexArray& vertexArr, 
  const IndexBuffer& indexBuf, 
  const Shader& shader 
) {
  shader.bind();

  vertexArr.bind();
  indexBuf.bind();

  glDrawElements(GL_TRIANGLES, indexBuf.getCount(), GL_UNSIGNED_INT, nullptr);
}