#include <filesystem>
namespace fs = std::filesystem;


#include "Model.h"
#include "Tank.h"
#include "ThirdPersonCamera.h"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")

const unsigned width = 1200;
const unsigned height = 900;


float skyboxVertices[] =
{
	//   Coordinates
	-1.0f, -1.0f,  1.0f,//        7--------6
	 1.0f, -1.0f,  1.0f,//       /|       /|
	 1.0f, -1.0f, -1.0f,//      4--------5 |
	-1.0f, -1.0f, -1.0f,//      | |      | |
	-1.0f,  1.0f,  1.0f,//      | 3------|-2
	 1.0f,  1.0f,  1.0f,//      |/       |/
	 1.0f,  1.0f, -1.0f,//      0--------1
	-1.0f,  1.0f, -1.0f
};



unsigned int skyboxIndices[] =
{
	// Right
	1, 2, 6,
	6, 5, 1,
	// Left
	0, 4, 7,
	7, 3, 0,
	// Top
	4, 5, 6,
	6, 7, 4,
	// Bottom
	0, 3, 2,
	2, 1, 0,
	// Back
	0, 1, 5,
	5, 4, 0,
	// Front
	3, 7, 6,
	6, 2, 3
};


std::vector<std::string> facesDay
{
	"Skybox\\right.jpg",
	"Skybox\\left.jpg",
	"Skybox\\top.jpg",
	"Skybox\\bottom.jpg",
	"Skybox\\back.jpg",
	"Skybox\\front.jpg"
};

std::vector<std::string>facesNight
{
	"Skybox_night\\11.jpg",
	"Skybox_night\\1.jpg",
	"Skybox_night\\1.jpg",
	"Skybox_night\\1.jpg",
	"Skybox_night\\1.jpg",
	"Skybox_night\\1.jpg"
};


float blendFactor = 0;
float ambientFactor = 0.9;
float mixValue = 1.0f;


void decomposeMatrix(const glm::mat4& matrix, glm::vec3& translation, glm::vec3& scale, glm::quat& rotation) {
	// Extract the translation
	translation = glm::vec3(matrix[3]);

	// Extract the scale
	scale.x = glm::length(glm::vec3(matrix[0]));
	scale.y = glm::length(glm::vec3(matrix[1]));
	scale.z = glm::length(glm::vec3(matrix[2]));

	// Remove the scale from the matrix to extract the rotation
	glm::mat4 rotationMatrix = matrix;

	rotationMatrix[0] /= scale.x;
	rotationMatrix[1] /= scale.y;
	rotationMatrix[2] /= scale.z;

	rotation = glm::quat_cast(rotationMatrix);
}


void drawMountain(Model modelMountain, Shader shaderProgram, Camera camera)
{
	modelMountain.Draw(shaderProgram, camera, glm::vec3(0.0f, 0.3f, 20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(2.5f, 2.5f, 2.5f));//spate mijloc
	modelMountain.Draw(shaderProgram, camera, glm::vec3(-17.0f, 0.3f, 20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(4.5f, 3.5f, 3.5f));//spate 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(-15.0f, 0.3f, 20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(3.5f, 2.5f, 3.5f));//spate 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(-11.0f, 0.3f, 20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(2.5f, 2.5f, 2.5f));//spate 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(-8.0f, 0.3f, 20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(2.5f, 2.5f, 2.5f));//spate
	modelMountain.Draw(shaderProgram, camera, glm::vec3(-6.0f, 0.3f, 20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(2.5f, 2.5f, 2.5f));//spate
	modelMountain.Draw(shaderProgram, camera, glm::vec3(-2.0f, 0.3f, 20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(3.5f, 3.5f, 3.5f));//spate 

	modelMountain.Draw(shaderProgram, camera, glm::vec3(-16.0f, 0.3f, -20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(6.5f, 4.5f, 5.5f));//fata stanga
	modelMountain.Draw(shaderProgram, camera, glm::vec3(-10.0, 0.3f, -20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(3.5f, 3.5f, 3.5f));//fata 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(-7.0, 0.3f, -20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(3.5f, 2.5f, 2.5f));//fata 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(-2.0, 0.3f, -20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(3.5f, 2.5f, 3.5f));//fata 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(-1.0, 0.3f, -20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(3.5f, 2.5f, 3.5f));//fata 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(2.0, 0.3f, -20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(4.5f, 3.5f, 4.5f));//fata 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(5.0, 0.3f, -20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(4.5f, 3.5f, 3.5f));//fata 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(9.0, 0.3f, -20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(3.5f, 4.5f, 3.5f));//fata 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(12.0, 0.3f, -20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(3.5f, 3.5f, 2.5f));//fata 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(15.0, 0.3f, -20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(4.5f, 3.5f, 4.5f));//fata 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(17.0, 0.3f, -20.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(6.5f, 4.5f, 5.5f));//fata 

	modelMountain.Draw(shaderProgram, camera, glm::vec3(20.0f, 0.3f, 6.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(2.1f, 3.5f, 2.5f));//dreapta 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(20.0f, 0.3f, 8.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(3.1f, 2.5f, 2.5f));//dreapta 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(20.0f, 0.3f, 10.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(3.8f, 3.5f, 3.5f));//dreapta 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(20.0f, 0.3f, 13.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(3.5f, 2.5f, 3.5f));//dreapta 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(20.0f, 0.3f, 15.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(3.5f, 3.0f, 2.5f));//dreapta 
	modelMountain.Draw(shaderProgram, camera, glm::vec3(20.0f, 0.3f, 17.0f), glm::quat(1.0f, 0.0f, 0.0f, 0.0f), glm::vec3(3.5f, 2.5f, 3.5f));//dreapta 
}


void drawnCactusModels(Model modelCactus, Model modelCactus2, Shader shaderProgram, Camera camera, float angleRadians)
{
	///////cactus 
		// fata mijloc
	modelCactus.Draw(shaderProgram, camera, glm::vec3(-18.0f, 60.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(5.0f, 4.0f, 4.0f));
	modelCactus.Draw(shaderProgram, camera, glm::vec3(-46.0f, 68.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(6.0f, 3.0f, 3.0f));
	modelCactus.Draw(shaderProgram, camera, glm::vec3(8.0f, 68.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(8.0f, 4.0f, 4.0f));


	//fata stanga
	modelCactus.Draw(shaderProgram, camera, glm::vec3(-118.0f, 60.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(10.0f, 8.0f, 7.0f));
	modelCactus.Draw(shaderProgram, camera, glm::vec3(-146.0f, 68.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(6.0f, 3.0f, 3.0f));


	//spate
	modelCactus.Draw(shaderProgram, camera, glm::vec3(-160.0f, -155.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(9.0f, 10.0f, 10.0f));
	modelCactus.Draw(shaderProgram, camera, glm::vec3(30.0f, -170.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(9.0f, 10.0f, 10.0f));
	modelCactus.Draw(shaderProgram, camera, glm::vec3(120.0f, -150.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(9.0f, 10.0f, 10.0f));
	modelCactus.Draw(shaderProgram, camera, glm::vec3(190.0f, -40.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(10.0f, 10.0f, 10.0f));


	//////cactus 2
	modelCactus2.Draw(shaderProgram, camera, glm::vec3(20.0f, 12.0f, -1.7f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(0.2f, 0.2f, 0.2f));
	modelCactus2.Draw(shaderProgram, camera, glm::vec3(15.0f, 12.0f, -1.7f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(0.3f, 0.3f, 0.3f));

}

void drawnHouse(Model modelHouse, Camera camera, Shader shaderProgram, float angleRadians)
{
	//mijloc
	modelHouse.Draw(shaderProgram, camera, glm::vec3(-1.0f, 70.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(3.0f, 2.0f, 2.0f));
	modelHouse.Draw(shaderProgram, camera, glm::vec3(-13.0f, 70.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(2.0f, 2.0f, 2.0f));
	modelHouse.Draw(shaderProgram, camera, glm::vec3(-25.0f, 70.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(2.0f, 2.0f, 2.0f));
	modelHouse.Draw(shaderProgram, camera, glm::vec3(-37.0f, 70.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(2.0f, 2.0f, 2.0f));


	//stanga
	modelHouse.Draw(shaderProgram, camera, glm::vec3(-100.0f, 70.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(2.0f, 2.0f, 2.0f));
	modelHouse.Draw(shaderProgram, camera, glm::vec3(-112.0f, 70.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(3.0f, 2.0f, 2.0f));
	modelHouse.Draw(shaderProgram, camera, glm::vec3(-124.0f, 70.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(2.0f, 2.0f, 2.0f));
	modelHouse.Draw(shaderProgram, camera, glm::vec3(-136.0f, 70.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(2.0f, 2.0f, 2.0f));

	/*modelHouse.Draw(shaderProgram, camera, glm::vec3(100.0f, 60.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(1.0f, 1.0f, 1.0f));
	modelHouse.Draw(shaderProgram, camera, glm::vec3(106.0f, 60.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(2.0f, 1.0f, 1.0f));
	modelHouse.Draw(shaderProgram, camera, glm::vec3(112.0f, 60.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(1.0f, 1.0f, 1.0f));
	modelHouse.Draw(shaderProgram, camera, glm::vec3(118.0f, 60.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(1.0f, 1.0f, 1.0f));*/


		//dreapta
	modelHouse.Draw(shaderProgram, camera, glm::vec3(100.0f, 70.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(1.0f, 1.0f, 1.0f));
	modelHouse.Draw(shaderProgram, camera, glm::vec3(106.0f, 70.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(2.0f, 1.0f, 1.0f));
	modelHouse.Draw(shaderProgram, camera, glm::vec3(112.0f, 70.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(1.0f, 1.0f, 1.0f));
	modelHouse.Draw(shaderProgram, camera, glm::vec3(118.0f, 70.0f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(1.0f, 1.0f, 1.0f));
}

void drawnHeliport(Model modelHeliport, Camera camera, Shader shaderProgram, float angleRadians)
{

	modelHeliport.Draw(shaderProgram, camera, glm::vec3(20.0f, -9.6f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, 0.0f, 1.0f))), glm::vec3(1.0f, 1.0f, 1.0f));
	modelHeliport.Draw(shaderProgram, camera, glm::vec3(20.0f, -9.6f, 10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, 0.0f, 1.0f))), glm::vec3(1.0f, 1.0f, 1.0f));
	modelHeliport.Draw(shaderProgram, camera, glm::vec3(-20.0f, -9.6f, -10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, 0.0f, 1.0f))), glm::vec3(1.0f, 1.0f, 1.0f));
	modelHeliport.Draw(shaderProgram, camera, glm::vec3(-20.0f, -9.6f, 10.0f),
		glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, 0.0f, 1.0f))), glm::vec3(1.0f, 1.0f, 1.0f));

}


void UpdateCamera(Tank& tank, ThirdPersonCamera& camera)
{
	// Update the camera to always look at the tank's position
	camera.SetTargetPosition(tank.m_position);

	// Optionally update yaw based on tank's rotation if needed
	camera.SetYaw(tank.GetYaw());

	// You may need to handle pitch if you want vertical rotation based on user input
}



void processInput(GLFWwindow* window, Tank& tank, double deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS)
	{
		blendFactor = std::min(blendFactor + 0.01f, 1.0f);  // Increase blend factor towards night
		mixValue = 1.0f - blendFactor;
	}

	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
	{
		blendFactor = std::max(blendFactor - 0.01f, 0.0f); // Decrease blend factor towards day
		mixValue = 1.0f - blendFactor;
	}
	if (mixValue < 0.5f)
		mixValue = 0.5f;


	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
		tank.ProcessInput(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
		tank.ProcessInput(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
		tank.ProcessInput(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
		tank.ProcessInput(RIGHT, (float)deltaTime);

}


double deltaTime = 0.0f;	// time between current frame and last frame
double lastFrame = 0.0f;


int main()
{
	//Initialize GLFW
	glfwInit();

	//specify OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell GLFW we are using CORE profile
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Tancodrom", NULL, NULL);

	//error check
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glewInit();


	Shader shaderProgram("default.vert", "default.frag");
	Shader skyboxShader("skybox.vert", "skybox.frag");
	Shader shadowShader("ShadowMapping.vs", "ShadowMapping.fs");
	Shader depthShader("ShadowMappingDepth.vs", "ShadowMappingDepth.fs");


	unsigned int depthMapFBO;
	glGenFramebuffers(1, &depthMapFBO);

	const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
	unsigned int depthMap;
	glGenTextures(1, &depthMap);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
		SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
	glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
	glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);




	// Take care of all the light related things
	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	/*glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);*/

	glm::mat4 lightProjection, lightView, lightSpaceMatrix;
	float near_plane = 1.0f, far_plane = 7.5f;
	lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
	lightView = glm::lookAt(lightPos, glm::vec3(0.0f), glm::vec3(0.0, 1.0, 0.0));
	lightSpaceMatrix = lightProjection * lightView;




	glEnable(GL_DEPTH_TEST);
	// Enables Cull Facing
	glEnable(GL_CULL_FACE);
	// Keeps front faces
	glCullFace(GL_FRONT);
	// Uses counter clock-wise standard
	glFrontFace(GL_CCW);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	std::filesystem::path currentDir = std::filesystem::current_path();

	std::string modelPath;
	/*modelPath="Models/helicopter/h/scene.gltf";
	Model heli(modelPath.c_str());*/

	modelPath = "Models/airplane/scene.gltf";
	//Model modelAirplane(modelPath.c_str());

	modelPath = "Models/grass/scene.gltf";
	Model modelGround(modelPath.c_str());

	modelPath = "Models/mountain/scene.gltf";
	Model modelMountain(modelPath.c_str());

	modelPath = "Models/cactus/scene.gltf";
	Model modelCactus(modelPath.c_str());

	modelPath = "Models/cactus2/scene.gltf";
	Model modelCactus2(modelPath.c_str());


	modelPath = "Models/heliport/heliport.gltf";
	Model modelHeliport(modelPath.c_str());

	modelPath = "Models/old_building/scene.gltf";
	Model modelHouse(modelPath.c_str());

	modelPath = "Models/stone/scene.gltf";
	Model modelStone(modelPath.c_str());

	modelPath = "Models/tank/tank.gltf";
	Model tank(modelPath.c_str());

	modelPath = "Models/helicopter/h/scene.gltf";
	Model heli(modelPath.c_str());




	// Variables to create periodic event for FPS displaying
	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	// Keeps track of the amount of frames in timeDiff
	unsigned int counter = 0;

	// Use this to disable VSync (not advized)
	//glfwSwapInterval(0);


	// Create VAO, VBO, and EBO for the skybox
	unsigned int skyboxVAO, skyboxVBO, skyboxEBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glGenBuffers(1, &skyboxEBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(skyboxIndices), &skyboxIndices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// All the faces of the cubemap (make sure they are in this exact order)
	std::string facesCubemap[6] =
	{
		 "Skybox/right.jpg",
		 "Skybox/left.jpg",
		 "Skybox/top.jpg",
		 "Skybox/bottom.jpg",
		 "Skybox/front.jpg",
		 "Skybox/back.jpg"
	};



	// Creates the cubemap texture object
	unsigned int cubemapTexture;
	glGenTextures(1, &cubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// These are very important to prevent seams
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// This might help with seams on some systems
	//glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

	// Cycles through all the textures and attaches them to the cubemap object
	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(facesCubemap[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture: " << facesCubemap[i] << std::endl;
			stbi_image_free(data);
		}
	}
	unsigned int nightCubemapTexture;
	glGenTextures(1, &nightCubemapTexture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, nightCubemapTexture);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);



	for (unsigned int i = 0; i < 6; i++)
	{
		int width, height, nrChannels;
		unsigned char* data = stbi_load(facesNight[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			stbi_set_flip_vertically_on_load(false);
			glTexImage2D
			(
				GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
				0,
				GL_RGB,
				width,
				height,
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				data
			);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Failed to load texture: " << facesNight[i] << std::endl;
			stbi_image_free(data);
		}
	}


	Tank modelTank;
	//Tank t1(modelTank), t2(modelTank);

	/*t1.m_position = glm::vec3(8.0f, -9.5f, 5.0f);
	t1.m_headPosition = glm::vec3(8.17f, -9.5f, 5.0f);
	t2.m_position = glm::vec3(3.0f, -9.5f, -5.0f);
	t2.m_headPosition = glm::vec3(3.17f, -9.5f, -5.0f);*/
	//main while loop


	ThirdPersonCamera tpc(modelTank.m_position, 10.0f, 20.0f, 0.0f);
		
	while (!glfwWindowShouldClose(window))
	{
		//per-frame time logic 
		double currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		processInput(window, modelTank, deltaTime);
		//modelTank.ProcessInput(window, deltaTime);

		//UpdateCamera(modelTank, tpc);
		//glm::mat4 viewMatrix = tpc.GetViewMatrix();


	
		//glUniformMatrix4fv(glGetUniformLocation(shaderProgram.ID, "camMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));


		//std::cout << modelTank.m_headRotation.x << " " << modelTank.m_headRotation.y << " " << modelTank.m_headRotation.z << " " << "\n";
		shaderProgram.Activate();
		glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
		glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
		glUniform1f(glGetUniformLocation(shaderProgram.ID, "mixValue"), mixValue);


		//decomposeMatrix(modelTank.bodyTransformationMatrix, translation, scale, rotation);


		depthShader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(depthShader.ID, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

		shadowShader.Activate();
		glUniformMatrix4fv(glGetUniformLocation(shadowShader.ID, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));
		glUniform1i(glGetUniformLocation(shadowShader.ID, "diffuseTexture"), 0);
		glUniform1i(glGetUniformLocation(shadowShader.ID, "shadowMap"), 1);

		skyboxShader.Activate();
		glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox"), 0);

		std::string newTitle = "Tancodrom";
		glfwSetWindowTitle(window, newTitle.c_str());

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		camera.Inputs(window);
		camera.updateMatrix(45.0f, 0.1f, 5000.0f);

		
		float angleRadians = glm::radians(90.0f);
		glm::quat rotation = glm::angleAxis(angleRadians, glm::vec3(0.0f, 0.0f, -1.0f));

		//tank.Draw(shaderProgram, camera, glm::vec3(5.0f, 4.0f, 0.0f), glm::quat(0.0f, 0.0f, 0.0f, 0.0f), glm::vec3(0.5f, 0.5f, 0.5f));

		drawMountain(modelMountain, shaderProgram, camera);
		drawnHouse(modelHouse, camera, shaderProgram, angleRadians);
		drawnHeliport(modelHeliport, camera, shaderProgram, angleRadians);
		drawnCactusModels(modelCactus, modelCactus2, shaderProgram, camera, angleRadians);

		modelStone.Draw(shaderProgram, camera, glm::vec3(84.0f, -75.0f, 7.0f),
			glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(3.0f, 3.0f, 3.0f));
		modelStone.Draw(shaderProgram, camera, glm::vec3(78.0f, -75.0f, 7.0f),
			glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(5.0f, 3.0f, 3.0f));
		modelStone.Draw(shaderProgram, camera, glm::vec3(-88.0f, -75.0f, 7.0f),
			glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(5.0f, 3.0f, 3.0f));
		modelStone.Draw(shaderProgram, camera, glm::vec3(-82.0f, -75.0f, 7.0f),
			glm::quat(glm::angleAxis(angleRadians, glm::vec3(0.0f, -1.0f, 0.0f))), glm::vec3(4.0f, 3.0f, 3.0f));
		//Tank drawing

		heli.Draw(shaderProgram, camera, glm::vec3(-20.0f, -10.0f,6.0f), glm::angleAxis(glm::radians(90.0f), glm::vec3(0.0f, -1.0f, 0.0f)), glm::vec3(0.5f,0.5f,0.5f));
		modelTank.DrawBody(shaderProgram, camera);

		/*t1.DrawBody(shaderProgram, camera);
		t1.DrawHead(shaderProgram, camera);

		t2.DrawBody(shaderProgram, camera);
		t2.DrawHead(shaderProgram, camera);*/

		modelGround.Draw(shaderProgram, camera, glm::vec3(0.0f, -10.0f, 0.0f), glm::quat(glm::vec3(0.0f, 0.0f, 0.0f)), glm::vec3(1.0f, 1.0f, 1.0f));//colt dreapta
		int numInstances = 10;
		float ySpacing = 40.0f;

		for (int i = 0; i < numInstances; i++) {
			float yOffset = -30.0f + ySpacing * i;
			//modelGround.Draw(shaderProgram, camera, glm::vec3(-12.0f, yOffset, 0.0f), glm::quat(glm::vec3(4.0f, 4.5f, 0.0f)), glm::vec3(3.0f, 3.0f, 3.0f));
		}

		//glm::quat(glm::radians(-90.0f), glm::vec3(0.0f, 1.1f, 0.2f))
		// Since the cubemap will always have a depth of 1.0, we need that equal sign so it doesn't get discarded
		glDepthFunc(GL_LEQUAL);



		skyboxShader.Activate();
		glUniform1f(glGetUniformLocation(skyboxShader.ID, "blendFactor"), blendFactor);

		//aici pui si blendfactorul de la lumina



		glm::mat4 view = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);
		// We make the mat4 into a mat3 and then a mat4 again in order to get rid of the last row and column
		// The last row and column affect the translation of the skybox (which we don't want to affect)
		view = glm::mat4(glm::mat3(glm::lookAt(camera.Position, camera.Position + camera.Orientation, camera.Up)));
		projection = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "view"), 1, GL_FALSE, glm::value_ptr(view));
		glUniformMatrix4fv(glGetUniformLocation(skyboxShader.ID, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

		// Draws the cubemap as the last object so we can save a bit of performance by discarding all fragments
		// where an object is present (a depth of 1.0f will always fail against any object's depth value)
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox1"), 0);

		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_CUBE_MAP, nightCubemapTexture);
		glUniform1i(glGetUniformLocation(skyboxShader.ID, "skybox2"), 1);

		glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// Switch back to the normal depth function
		glDepthFunc(GL_LESS);

		glfwSwapBuffers(window);
		//take care of all GLFW events
		glfwPollEvents();
	}


	shaderProgram.Delete();
	skyboxShader.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
