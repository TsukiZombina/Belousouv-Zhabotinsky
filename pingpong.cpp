#include <cstdlib>
#include <ctime>
#include "pingpong.h"
#include "shader_util.h"

PingPong::PingPong(GLuint width, GLuint height) : mWidth(width), mHeight(height)
{
    /* Create our framebuffer */
    glGenFramebuffers(1, &mFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, mFbo);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    createFrontAndBackTextures();

    /* Setup shaders */
    mShaderProgram = linkShaderProgram("vertex_shader.glsl",
                                       "test_shader.glsl");

    srand(time(NULL));
}

PingPong::~PingPong()
{
    glDeleteTextures(2, mColorAttachments);
}

void PingPong::update(GLuint vao)
{
    glBindFramebuffer(GL_FRAMEBUFFER, mFbo);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
                           mFront, 0);

    glViewport(0, 0, mWidth, mHeight);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(mShaderProgram);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, mBack);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (GLvoid*)0);
    glBindVertexArray(0);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    // Swap textures
    GLuint temp = mBack;
    mBack = mFront;
    mFront = temp;
}

GLuint PingPong::getFront()
{
    return mFront;
}

void PingPong::createFrontAndBackTextures()
{
    GLuint* textureData = new GLuint[mWidth * mHeight];

    for(GLuint row = 0; row < mHeight; row += 2)
    {
        for(GLuint col = 0; col < mWidth; col++)
        {
            GLfloat r = (GLfloat)rand() / RAND_MAX;

            if(r < 0.33)
            {
                textureData[mWidth * row + col] = 0xFF000064;
                textureData[mWidth * row + col + 1] = 0xFF000064;
            }
            else if(r > 0.33 && r < 0.66)
            {
                textureData[mWidth * row + col] = 0xFF000001;
                textureData[mWidth * row + col + 1] = 0xFF000001;
            }
            else
            {
                textureData[mWidth * row + col] = 0xFF000000;
                textureData[mWidth * row + col + 1] = 0xFF000000;
            }
        }
    }

    glGenTextures(1, &mColorAttachments[0]);
    glBindTexture(GL_TEXTURE_2D, mColorAttachments[0]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8UI, mWidth, mHeight, 0, GL_RGBA_INTEGER,
                 GL_UNSIGNED_BYTE, textureData);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    glGenTextures(1, &mColorAttachments[1]);
    glBindTexture(GL_TEXTURE_2D, mColorAttachments[1]);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8UI, mWidth, mHeight, 0, GL_RGBA_INTEGER,
                 GL_UNSIGNED_BYTE, nullptr);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    delete[] textureData;

    /* Set front and back */
    mBack  = mColorAttachments[0];
    mFront = mColorAttachments[1];
}
