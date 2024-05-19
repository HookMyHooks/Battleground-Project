#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aColor;
layout (location = 3) in vec2 aTex;

out vec3 crntPos;
out vec3 Normal;
out vec3 color;
out vec2 texCoord;

out VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} vs_out;

uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform mat4 lightSpaceMatrix;

void main()
{
    mat4 transform = model * translation * rotation * scale;
    crntPos = vec3(transform * vec4(aPos, 1.0f));
    Normal = aNormal;
    color = aColor;
    texCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTex;

    // Shadow mapping specific outputs
    vs_out.FragPos = crntPos;
    vs_out.Normal = Normal;
    vs_out.TexCoords = texCoord;
    vs_out.FragPosLightSpace = lightSpaceMatrix * vec4(crntPos, 1.0);

    // Position transformation
    gl_Position = camMatrix * vec4(crntPos, 1.0);
}
