#version 410

in vec2 vTexCoord;

out vec4 FragColor;

uniform sampler2D Albedo;
uniform sampler2D Light;

void main()
{
    vec3 albedoColor = texture(Albedo, vTexCoord).rgb;
    vec3 lightColor = texture(Light, vTexCoord).rgb;

    //FragColor = vec4(albedoColor * lightColor, 1);
    FragColor = vec4(albedoColor, 1);
    //FragColor = vec4(vTexCoord, albedoColor.z, 1);
    //FragColor = vec4(1,1,1,1);
}