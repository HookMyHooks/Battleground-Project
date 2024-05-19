#version 330 core

// Outputs colors in RGBA
out vec4 FragColor;

// Inputs from the Vertex Shader
in vec3 crntPos;
in vec3 Normal;
in vec3 color;
in vec2 texCoord;

in VS_OUT {
    vec3 FragPos;
    vec3 Normal;
    vec2 TexCoords;
    vec4 FragPosLightSpace;
} fs_in;

uniform float mixValue = 1.0f;

// Gets the Texture Units from the main function
uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform sampler2D shadowMap;

// Gets the color of the light from the main function
uniform vec4 lightColor;
// Gets the position of the light from the main function
uniform vec3 lightPos;
// Gets the position of the camera from the main function
uniform vec3 camPos;

uniform float ambientFactor = 0.2;

// Shadow Calculation function from shadow mapping shader
float ShadowCalculation(vec4 fragPosLightSpace)
{
    // Perform perspective divide
    vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
    // Transform to [0,1] range
    projCoords = projCoords * 0.5 + 0.5;
    // Get closest depth value from light's perspective (using [0,1] range fragPosLight as coords)
    float closestDepth = texture(shadowMap, projCoords.xy).r; 
    // Get depth of current fragment from light's perspective
    float currentDepth = projCoords.z;
    // Calculate bias (based on depth map resolution and slope)
    vec3 normal = normalize(fs_in.Normal);
    vec3 lightDir = normalize(lightPos - fs_in.FragPos);
    
    float bias = 0.005;
    bias = max(0.05 * (1.0 - dot(normal, lightDir)), 0.005);
    float shadow = 0.0;
    vec2 texelSize = 1.0 / textureSize(shadowMap, 0);
    for(int x = -1; x <= 1; ++x)
    {
        for(int y = -1; y <= 1; ++y)
        {
            float pcfDepth = texture(shadowMap, projCoords.xy + vec2(x, y) * texelSize).r; 
            shadow += currentDepth - bias > pcfDepth ? 1.0 : 0.0;        
        }    
    }
    shadow /= 9.0;

    if(projCoords.z > 1.0)
        shadow = 0.0;

    return shadow;
}

vec4 direcLight()
{
    // Ambient lighting
    float ambient = ambientFactor;

    // Diffuse lighting
    vec3 normal = normalize(Normal) * mixValue;
    vec3 lightDirection = normalize(lightPos - crntPos);
    float diffuse = max(dot(normal, lightDirection), 0.0f) * mixValue;

    // Specular lighting
    float specularLight = 0.50f * mixValue;
    vec3 viewDirection = normalize(camPos - crntPos);
    vec3 reflectionDirection = reflect(-lightDirection, normal);
    float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
    float specular = specAmount * specularLight;

    // Calculate shadow
    float shadow = ShadowCalculation(fs_in.FragPosLightSpace);                      	
    vec3 lighting = (ambient + (1.0 - shadow) * (diffuse + specular)) * color;

    // Return final color with textures and light color
    return (texture(diffuse0, texCoord) * (diffuse + ambient) + texture(specular0, texCoord).r * specular) * vec4(lighting, 1.0) * lightColor * mixValue;
}

void main()
{
    // Outputs final color
    FragColor = direcLight();
}
