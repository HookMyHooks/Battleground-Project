#version 330 core
out vec4 FragColor;

in vec3 texCoords;

//uniform samplerCube skybox;
uniform samplerCube skybox1; // First skybox texture
uniform samplerCube skybox2; // Second skybox texture
uniform float blendFactor;

void main()
{    
    vec4 texColor1 = texture(skybox1, texCoords);
    vec4 texColor2 = texture(skybox2, texCoords);
    FragColor = mix(texColor1, texColor2, blendFactor);
}