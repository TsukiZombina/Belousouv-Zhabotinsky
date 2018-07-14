#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader_util.h"

GLuint createDisplayQuad(GLuint& vbo, GLuint& ebo);

GLuint createDisplayQuad(GLuint& vbo, GLuint& ebo) { 
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, 0.0f,
        1.0f, -1.0f, 1.0f, 0.0f,
        -1.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f
    };

    GLuint elements[] = {
        0, 1, 2,
        1, 3, 2
    };
}

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(512, 512, "Belouvsov-Zhavotisky Reaction", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewInit();
    glViewport(0, 0, 512, 512);
    glClearColor(0.33, 0.33, 0.33, 0);

    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);


        glfwSwapBuffers(window);
    }
    glfwTerminate();
    return 0;
}