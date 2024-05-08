#version 330 core
out vec4 FragColor;

struct DirectionalLight {
    vec3 direction;
    vec3 color;
};

uniform DirectionalLight dirLight;
uniform vec3 viewPos;

in vec3 Normal;
in vec3 FragPos;

void main()
{
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(-dirLight.direction);
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);

    float spec = 0.5;
    float shininess = 16.0;
    vec3 ambient = 0.05 * dirLight.color;
    vec3 diffuse = max(dot(norm, lightDir), 0.0) * dirLight.color;
    vec3 specular = pow(max(dot(reflectDir, viewDir), 0.0), shininess) * spec * dirLight.color;

    vec3 result = ambient + diffuse + specular;
    FragColor = vec4(result, 1.0);
}
