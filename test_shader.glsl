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

    uint state = texture(sampler, TexCoord + vec2(-1, 1) / 512).r;
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

    state = texture(sampler, TexCoord + vec2(-2, 0) / 512).r;
    info.sum += state;

    if(state == q)
    {
        info.numActive++;
    }
    else if(state > 0u)
    {
        info.numInactive++;
    }

    state = texture(sampler, TexCoord + vec2(2, 0) / 512).r;
    info.sum += state;

    if(state == q)
    {
        info.numActive++;
    }
    else if(state > 0u)
    {
        info.numInactive++;
    }

    state = texture(sampler, TexCoord + vec2(-1, -1) / 512).r;
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
