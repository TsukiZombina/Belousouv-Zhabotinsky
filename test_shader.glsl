// Rules for Brian's brain
// Each cell has three possible states: passive (0), active (1) and semi - active(2).
// If a cell is active, it goes to semi-active state on the next step.
// If a cell is semi-active, it becomes passive on the next step.
// If a cell is passive, it becomes active if and only if it has exactly 2 active neighbors.

#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D sampler;

struct Neighbors
{
    int numActive;
    int numNonActive;
    int sum;
};

void getInfo(out Neighbors n)
{
    n.numActive = 0;
    n.numNonActive = 0;
    n.sum = 0;

    int state = int(texture(sampler, TexCoord + vec2(-1, -1) / 512).r * 255);
    n.sum += state;

    if(state == 200)
    {
        n.numActive += 1;
    }
    else if(state > 0)
    {
        n.numNonActive += 1;
    }

    state = int(texture(sampler, TexCoord + vec2(-1, 0) / 512).r * 255);
    n.sum += state;

    if(state == 200)
    {
        n.numActive += 1;
    }
    else if(state > 0)
    {
        n.numNonActive += 1;
    }

    state = int(texture(sampler, TexCoord + vec2(-1, 1) / 512).r * 255);
    n.sum += state;

    if(state == 200)
    {
        n.numActive += 1;
    }
    else if(state > 0)
    {
        n.numNonActive += 1;
    }

    state = int(texture(sampler, TexCoord + vec2(0, -1) / 512).r * 255);
    n.sum += state;

    if(state == 200)
    {
        n.numActive += 1;
    }
    else if(state > 0)
    {
        n.numNonActive += 1;
    }

    state = int(texture(sampler, TexCoord + vec2(0, 1) / 512).r * 255);
    n.sum += state;

    if(state == 200)
    {
        n.numActive += 1;
    }
    else if(state > 0)
    {
        n.numNonActive += 1;
    }

    state = int(texture(sampler, TexCoord + vec2(1, -1) / 512).r * 255);
    n.sum += state;

    if(state == 200)
    {
        n.numActive += 1;
    }
    else if(state > 0)
    {
        n.numNonActive += 1;
    }

    state = int(texture(sampler, TexCoord + vec2(1, 0) / 512).r * 255);
    n.sum += state;

    if(state == 200)
    {
        n.numActive += 1;
    }
    else if(state > 0)
    {
        n.numNonActive += 1;
    }

    state = int(texture(sampler, TexCoord + vec2(1, 1) / 512).r * 255);
    n.sum += state;

    if(state == 200)
    {
        n.numActive += 1;
    }
    else if(state > 0)
    {
        n.numNonActive += 1;
    }
}

void main()
{
    int q  = 200;
    int g  = 28;
    int k1 = 3;
    int k2 = 3;

    int state = int(texture(sampler, TexCoord).r * 255);

    Neighbors n;
    getInfo(n);

    if(state == 0)
    {
        float newState = (int(float(n.numActive) / k1) +
            int(float(n.numNonActive) / k2)) / 255.0;

        color = vec4(newState, 0.0, 0.0, 1.0);
    }
    else if(state < q)
    {
        float newState = (int(float(n.sum) / (n.numActive + n.numNonActive + 1)) + g) / 255.0;

        color = vec4(newState, 0.0, 0.0, 1.0);
    }
    else if(state == q)
    {
        color = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
