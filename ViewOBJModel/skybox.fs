#version 330 core

in vec3 TexCoords;
uniform samplerCube skybox;
void main()
{
   FragColor=texture(skybox,TexCoords);
}