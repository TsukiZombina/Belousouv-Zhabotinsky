// Rules for Brian's brain
// Each cell has three possible states: passive (0), active (1) and semi - active(2).
// If a cell is active, it goes to semi-active state on the next step.
// If a cell is semi-active, it becomes passive on the next step.
// If a cell is passive, it becomes active if and only if it has exactly 2 active neighbors.

#version 330 core

in vec2 TexCoord;

out uvec4 color;

uniform usampler2D sampler;

struct LocalInfo
{
    uint numActive;
    uint numInactive;
    uint sum;
};

void getLocalInfo(out LocalInfo info, uint q)
{
    info.numActive = 0u;
    info.numInactive = 0u;
    info.sum = 0u;

    uint state = texture(sampler, TexCoord + vec2(-1, -1) / 512).r;
    info.sum += state;

    if(state == q)
    {
        info.numActive++;
    }
    else if(state > 0u)
    {
        info.numInactive++;
    }

    state = texture(sampler, TexCoord + vec2(-1, 0) / 512).r;
    info.sum += state;

    if(state == q)
    {
        info.numActive++;
    }
    else if(state > 0u)
    {
        info.numInactive++;
    }

    state = texture(sampler, TexCoord + vec2(-1, 1) / 512).r;
    info.sum += state;

    if(state == q)
    {
        info.numActive++;
    }
    else if(state > 0u)
    {
        info.numInactive++;
    }

    state = texture(sampler, TexCoord + vec2(0, -1) / 512).r;
    info.sum += state;

    if(state == q)
    {
        info.numActive++;
    }
    else if(state > 0u)
    {
        info.numInactive++;
    }

    state = texture(sampler, TexCoord + vec2(0, 1) / 512).r;
    info.sum += state;

    if(state == q)
    {
        info.numActive++;
    }
    else if(state > 0u)
    {
        info.numInactive++;
    }

    state = texture(sampler, TexCoord + vec2(1, -1) / 512).r;
    info.sum += state;

    if(state == q)
    {
        info.numActive++;
    }
    else if(state > 0u)
    {
        info.numInactive++;
    }

    state = texture(sampler, TexCoord + vec2(1, 0) / 512).r;
    info.sum += state;

    if(state == q)
    {
        info.numActive++;
    }
    else if(state > 0u)
    {
        info.numInactive++;
    }

    state = texture(sampler, TexCoord + vec2(1, 1) / 512).r;
    info.sum += state;

    if(state == q)
    {
        info.numActive++;
    }
    else if(state > 0u)
    {
        info.numInactive++;
    }
}

void main()
{
    uint q = 100u;
    uint g = 20u;
    uint k1 = 2u;
    uint k2 = 3u;

    uint state = texture(sampler, TexCoord).r;

    LocalInfo info;
    getLocalInfo(info, q);

    if(state == 0u)
    {
        uint newState = uint(float(info.numActive) / k1) +
            uint(float(info.numInactive) / k2);

        color = uvec4(newState, 0, 0, 1);
    }
    else if(state < q)
    {
        uint newState = uint(float(info.sum) / (info.numActive + info.numInactive + 1u)) + g;

        color = uvec4(newState, 0, 0, 1);
    }
    else if(state == q)
    {
        color = uvec4(0, 0, 0, 1);
    }
}
