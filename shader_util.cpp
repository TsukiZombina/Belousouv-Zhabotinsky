#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>

#include "shader_util.h"

using std::cout;
using std::endl;
using std::string;
using std::stringstream;
using std::ifstream;

string loadShaderCode(const char* filename)
{
    ifstream shaderFile(filename);

    if(!shaderFile)
    {
        cout << "Can't find " << filename << endl;

        exit(1);
    }

    stringstream shaderData;
    shaderData << shaderFile.rdbuf();
    shaderFile.close();

    return shaderData.str();
}

GLuint compileShaderObject(const GLchar* shaderCode, GLenum shaderType)
{
    GLuint shaderObject = glCreateShader(shaderType);

    if(shaderObject == 0)
    {
        cout << "Error creating shader type: " << shaderType << endl;

        exit(1);
    }

    glShaderSource(shaderObject, 1, &shaderCode, NULL);
    glCompileShader(shaderObject);

    GLint success;
    GLchar infoLog[512];

    glGetShaderiv(shaderObject, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shaderObject, 512, NULL, infoLog);

        cout << "Error compiling shader type: " << shaderType << endl;
        cout << infoLog << endl;

        exit(1);
    }

    return shaderObject;
}

GLuint linkShaderProgram(const GLchar *vsFilename,
                         const GLchar *fsFilename)
{
    GLuint shaderProgram = glCreateProgram();

    string shaderStr = loadShaderCode(vsFilename);
    GLuint vertexShader = compileShaderObject(shaderStr.c_str(), GL_VERTEX_SHADER);

    shaderStr = loadShaderCode(fsFilename);
    GLuint fragmentShader = compileShaderObject(shaderStr.c_str(), GL_FRAGMENT_SHADER);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    GLchar infoLog[512];

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

        cout << "Link Error: " << infoLog << endl;

        exit(1);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

GLuint linkShaderProgram(const char *vsFilename,
                         const char *gsFilename,
                         const char *fsFilename)
{
    GLuint shaderProgram = glCreateProgram();

    string shaderStr = loadShaderCode(vsFilename);
    GLuint vertexShader = compileShaderObject(shaderStr.c_str(), GL_VERTEX_SHADER);

    shaderStr = loadShaderCode(gsFilename);
    GLuint geometryShader = compileShaderObject(shaderStr.c_str(), GL_GEOMETRY_SHADER);

    shaderStr = loadShaderCode(fsFilename);
    GLuint fragmentShader = compileShaderObject(shaderStr.c_str(), GL_FRAGMENT_SHADER);

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glAttachShader(shaderProgram, geometryShader);
    glLinkProgram(shaderProgram);

    GLint success;
    GLchar infoLog[512];

    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);

        cout << "Link Error: " << infoLog << endl;

        exit(1);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
