// Rules for Brian's brain
// Each cell has three possible states: passive (0), active (1) and semi - active(2).
// If a cell is active, it goes to semi-active state on the next step.
// If a cell is semi-active, it becomes passive on the next step.
// If a cell is passive, it becomes active if and only if it has exactly 2 active neighbors.

#version 330 core

in vec2 TexCoord;

out vec4 color;

uniform sampler2D sampler;

ivec4 get(int x, int y)
{
    return ivec4(texture(sampler, TexCoord + vec2(x, y) / 512));
}

void main()
{
    ivec4 sum =
        get(-1, -1) +
        get(-1,  0) +
        get(-1,  1) +
        get( 0, -1) +
        get( 0,  1) +
        get( 1, -1) +
        get( 1,  0) +
        get( 1,  1);

    ivec4 state = get(0, 0);

    if(state.r == 1)
    {
        color = vec4(0.0, 1.0, 0.0, 1.0);
    }
    else if(state.g == 1)
    {
        color = vec4(0.0, 0.0, 0.0, 1.0);
    }
    else if(state.r == 0 && state.g == 0 && sum.r == 2)
    {
        color = vec4(1.0, 0.0, 0.0, 1.0);
    }
    else
    {
        color = vec4(0.0, 0.0, 0.0, 1.0);
    }
}
