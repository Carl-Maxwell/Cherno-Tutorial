#include <memory>

#include <GL/glew.h>
#include <imgui/imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "renderer.h"
#include "vertex_buffer.h"
#include "index_buffer.h"
#include "vertex_buffer_layout.h"
#include "vertex_array.h"
#include "shader.h"
#include "texture.h"

#include "test_texture_2d.h"

namespace test{

TestTexture2d::TestTexture2d() :
  translationA(200, 200, 0),
  translationB(400, 200, 0)
 {
  f32 positions[] = {
   // Positions           // UV coords
     -50.0f, -50.0f,          0.0f, 0.0f,
      50.0f, -50.0f,          1.0f, 0.0f,
      50.0f,  50.0f,          1.0f, 1.0f,
     -50.0f,  50.0f,          0.0f, 1.0f
  };

  u32 indices[] = {
    0, 1, 2,
    2, 3, 0
  };

  const u32 number_of_vertices = 4;
  const u32 vertice_components = 4;

  vertexBuff = std::make_unique<VertexBuffer>(positions, sizeof(f32) * number_of_vertices * vertice_components);

  layout.push<f32>(2);
  layout.push<f32>(2);
  vertexArr.AddBuffer(*vertexBuff, layout);

  indexBuf = std::make_unique<IndexBuffer>(indices, 6);

  proj_matrix = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
  view  = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
  model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));

  model_view_projection_matrix = proj_matrix * view * model;

  // Load images

  texture = std::make_unique<Texture>("resources/images/badguy.png");

  // setup shader

  shader = std::make_unique<Shader>("resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
}

TestTexture2d::~TestTexture2d() {}

void TestTexture2d::onUpdate(float delta_time) {}

void TestTexture2d::onRender() {
  shader->bind();
  texture->bind();
  shader->setUniform1i("u_texture", 0);

  Renderer renderer;

  {
    model = glm::translate(glm::mat4(1.0f), translationA);
    model_view_projection_matrix = proj_matrix * view * model;
    shader->setUniform4f("u_model_view_projection_matrix", model_view_projection_matrix);
    renderer.draw(vertexArr, *indexBuf, *shader);
  }

  {
    model = glm::translate(glm::mat4(1.0f), translationB);
    model_view_projection_matrix = proj_matrix * view * model;
    shader->setUniform4f("u_model_view_projection_matrix", model_view_projection_matrix);
    renderer.draw(vertexArr, *indexBuf, *shader);
  }
}

void TestTexture2d::onImguiRender() {
  ImGui::BeginChild("texture 2D sliders");

  ImGui::SliderFloat3("translation A", &translationA.x, 0.0f, 720.0f);
  ImGui::SliderFloat3("translation B", &translationB.x, 0.0f, 720.0f);

  ImGui::EndChild();
}

}