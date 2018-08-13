#ifndef PINGPONG_H
#define PINGPONG_H

#include <GL/glew.h>

class PingPong
{
public:
    PingPong(GLuint width, GLuint height);
    ~PingPong();

    void update(GLuint vao);
    GLuint getFront();

private:
    void createFrontAndBackTextures();

    GLuint mWidth, mHeight;
    GLuint mColorAttachments[2], mFront = {0}, mBack = {0};
    GLuint mFbo = {0};

    GLuint mShaderProgram = {0};
};

#endif // PINGPONG_H
