#ifndef __GL_SHADER_H__
#define __GL_SHADER_H__
#include <GL/glew.h>
#include <gl/gl.h>
extern const GLchar* char_shader_color_draw_vertex;
extern const GLchar* char_shader_color_vertex;
extern const GLchar* char_shader_color_frag;

extern const GLchar* char_shader_texture_vertex;
extern const GLchar* char_shader_texture_frag;
extern const GLchar* char_shader_texture_blur_frag;
extern const GLchar* char_shader_texture_gray_frag;
extern const GLchar* char_shader_texture_spark_frag;

GLuint loadShaders(const GLchar* vertexStr, const GLchar* fragmentStr);
#endif