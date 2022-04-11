#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;

uniform mat4 u_model_view_projection_matrix;

void main() {
 gl_Position = position * u_model_view_projection_matrix;
 v_texCoord = texCoord;
}
