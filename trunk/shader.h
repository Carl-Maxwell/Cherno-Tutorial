#pragma once

#include <string>

#include "mtypedefs.h"
#include "mvec3.h"

class Shader{
public:
  u32 m_renderer_id;
  std::string m_vertex_filepath;
  std::string m_fragment_filepath;

  Shader(const std::string& vertex_filepath, const std::string& fragment_filepath);
  ~Shader();

  void bind() const;
  void unbind() const;

  u32 createShader(const std::string& vertexShader, const std::string& fragmentShader);
  u32 compileShader(u32 type, const std::string& strSource);
  std::string parseShader(const std::string& filepath); 

  // Set uniforms
  // void setUniform1i(const std::string& name, i32  v);
  // void setUniform2i(const std::string& name, i32* v);
  // void setUniform3i(const std::string& name, i32* v);
  // void setUniform4i(const std::string& name, i32* v);

  // void setUniform1uiv(const std::string& name, i32 count, const u32* v);

  // void setUniform1ui(const std::string& name, i32* v);
  // void setUniform2ui(const std::string& name, i32* v);
  // void setUniform3ui(const std::string& name, i32* v);
  // void setUniform4ui(const std::string& name, i32* v);

  // void setUniform1f(const std::string& name, f32  v);
  // void setUniform2f(const std::string& name, f32  v0, f32 v1);

  // void setUniform1f(const std::string& name, f32* v);
  // void setUniform2f(const std::string& name, f32* v);
  // void setUniform3f(const std::string& name, vec3 v);
  void setUniform4f(const std::string& name, vec4 v) const;

  // void setUniform(const std::string& name, i32 count, vec3* v);
  // void setUniform(const std::string& name, i32 count, vec4* v);

  i32 getUniformLocation(const std::string& name) const;
  
};
