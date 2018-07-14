#ifndef SHADER_UTIL_H
#define SHADER_UTIL_H

#include <iostream>
#include <fstream>
#include <GL/glew.h>

std::string loadShaderCode(const GLchar* filename);
GLuint compileShaderObject(const GLchar *shaderCode, GLenum shaderType);
GLuint linkShaderProgram(const GLchar* vsFilename,
                         const GLchar* fsFilename);

GLuint linkShaderProgram(const char* vsFilename,
                         const char* gsFilename,
                         const char* fsFilename);

#endif // SHADER_UTIL_H

