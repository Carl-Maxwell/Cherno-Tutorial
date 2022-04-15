#pragma once

#include <memory>

#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_buffer_layout.h"
#include "vertex_array.h"
#include "shader.h"
#include "texture.h"

#include "test.h"

namespace test{

class TestTexture2d : public Test{
private:
  std::unique_ptr<Shader> shader;

  std::unique_ptr<VertexBuffer> vertexBuff;
  VertexArray vertexArr;
  VertexBufferLayout layout;
  std::unique_ptr<IndexBuffer> indexBuf;

  glm::mat4 proj_matrix;
  glm::mat4 view;
  glm::mat4 model;
  glm::mat4 model_view_projection_matrix;
  glm::vec3 translationA;
  glm::vec3 translationB;

  std::unique_ptr<Texture> texture;
public:
  TestTexture2d();
  ~TestTexture2d();

  void onUpdate(float delta_time) override;
  void onRender() override;
  void onImguiRender() override;
};

}