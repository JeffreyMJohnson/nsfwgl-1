#version 410

layout(location=0) in vec4 Position;
layout(location=1) in vec4 Normal;
layout(location=2) in vec2 Tangent;
layout(location=3) in vec2 TexCoord;

out vec4 vColor;

uniform mat4 Projection;
uniform mat4 View;
uniform mat4 Model;

void main()
{
    vColor = vec4(1,1,1,1);
    gl_Position = Projection * View * Model * Position;
}