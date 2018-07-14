#include <iostream>
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader_util.h"
#include "pingpong.h"

GLuint createDisplayQuad(GLuint& vbo, GLuint& ebo);

void error_callback(GLint error, const GLchar* description);

int main()
{
    constexpr GLuint WIDTH = 512, HEIGHT = 512;

    glfwSetErrorCallback(error_callback);

    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Opengl App", nullptr, nullptr);

    if(!window)
    {
        std::cerr << "GLFW error: can't create window.\n";

        return 1;
    }

    glfwMakeContextCurrent(window);

    GLenum status = glewInit();

    if(status != GLEW_OK)
    {
        std::cerr << "GLEW error: " << glewGetErrorString(status) << "\n";

        return 1;
    }

    PingPong pingPong(512, 512);

    GLuint shaderProgram = linkShaderProgram("vertex_shader.glsl",
                                             "fragment_shader.glsl");

    GLuint vao, vbo, ebo;
    vao = createDisplayQuad(vbo, ebo);

    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

    GLfloat currentTime = 0.0f;
    GLfloat oldTime     = 0.0f;
    GLfloat elapsedTime = 0.0f;

    while(!glfwWindowShouldClose(window))
    {
        currentTime  = (GLfloat)glfwGetTime();
        elapsedTime += currentTime - oldTime;
        oldTime      = currentTime;

        if(elapsedTime > 0.0f)
        {
            pingPong.update(vao);

            elapsedTime = 0.0f;
        }

        glfwPollEvents();

        GLuint front = pingPong.getFront();

        glViewport(0, 0, WIDTH, HEIGHT);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, front);

        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}

GLuint createDisplayQuad(GLuint& vbo, GLuint& ebo)
{
    GLfloat vertices[] =
    {
        -1.0f, -1.0f,   0.0f, 0.0f,
         1.0f, -1.0f,   1.0f, 0.0f,
        -1.0f,  1.0f,   0.0f, 1.0f,
         1.0f,  1.0f,   1.0f, 1.0f,
    };

    GLuint elements[] =
    {
        0, 1, 2,
        1, 3, 2,
    };

    GLuint vao;

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(elements), elements, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),
                          (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat),
                          (GLvoid*)(2 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    return vao;
}

void error_callback(GLint error, const GLchar* description)
{
    std::cerr << "GLFW error " << error << ": " << description << "\n";

    exit(1);
}
