
#include <iostream>
#include <iomanip>
#include <string>

#include <fstream>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>

#include "shader.h"
#include "print.h"

Shader::Shader(const std::string& vertex_filepath, const std::string& fragment_filepath)
  : m_vertex_filepath(vertex_filepath), m_fragment_filepath(fragment_filepath), m_renderer_id(0)
{
  std::string vertex_source  = parseShader(vertex_filepath);
  std::string fragment_source = parseShader(fragment_filepath);
  
  m_renderer_id = createShader(vertex_source, fragment_source);
  glUseProgram(m_renderer_id);
}

Shader::~Shader() {
  glDeleteProgram(m_renderer_id);
}

void Shader::bind() const {
  glUseProgram(m_renderer_id);
}

void Shader::unbind() const {
  glUseProgram(0);
}

// TODO rename to loadShader or something
std::string Shader::parseShader(const std::string& filepath) {
  std::ifstream stream(filepath);

  // Print::line( std::filesystem::current_path().string() );
  // Print::line(filepath);

  std::string line;
  std::stringstream ss;
  while (getline(stream, line)) {
    ss << line << "\n";
  }

  return ss.str();
}

u32 Shader::compileShader(u32 type, const std::string& source) {
  u32 id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if (result == GL_FALSE) {
    i32 length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    
    Print::line("failed to compile " + std::string(type == GL_VERTEX_SHADER ? "vertex" : "fragment") + " shader\n");
    Print::line(message);

    return u32(-1);
  }

  return id;
}

u32 Shader::createShader(const std::string& vertexShader, const std::string& fragmentShader) {
  u32 program = glCreateProgram();
  u32 vs = compileShader(GL_VERTEX_SHADER, vertexShader);
  u32 fs = compileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

void Shader::setUniform4f(const std::string& name, vec4 v) const { 
glUniform4f(getUniformLocation(name), v[0], v[1], v[2], v[3]); }

i32 Shader::getUniformLocation(const std::string& name) const {
  i32 location = glGetUniformLocation(m_renderer_id, name.c_str());
  if (location == -1) {
    // Print::once("Shader.cpp warning:\n\tuniform: '" + name + "' doesn't exist in shader " + m_filepath + "!\n\tIs this uniform being used in the shader?");
    __debugbreak();
  }

  return location;
}

