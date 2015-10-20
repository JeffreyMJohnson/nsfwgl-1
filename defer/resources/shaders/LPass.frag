#version 410

in vec4 vPosition;
in vec4 vNormal;

in vec2 vTexCoord;

out vec3 LightOutput;

uniform vec3 LightDirection;
uniform vec3 LightColor;

uniform sampler2D Position;
uniform sampler2D Normal;

void main()
{
    vec3 normal = normalize(texture(Normal, vTexCoord).xyz);
    vec3 position = texture(Position, vTexCoord).xyz;

    float d = max(0, dot(normal, -LightDirection));

    LightOutput = LightColor * d;
}