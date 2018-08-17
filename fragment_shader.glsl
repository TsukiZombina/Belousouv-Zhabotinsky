#version 330 core

in  vec2 TexCoord;

out vec4 color;

uniform usampler2D sampler;

void main()
{
    uint state = texture(sampler, TexCoord).r;

    color = vec4(state/ 255.0, state / 255.0, 0.0, 1.0);
}

