#pragma once
#define M_PI 3.14

#include <Windows.h>
#include <locale>
#include "Model.h"
#include "Shader.h"
#include <codecvt>
#include <fstream>
#include <sstream>
#include <glfw3.h>
#include <GL/glew.h>
class Tank
{
private:

	//models --- hitbox to be included
	Model m_bodyModel;
	Model m_headModel;

	//accelerators
	float m_tankSpeed = 2.5f; // Speed of the tank
	float m_tankRotation = 0.0f; //-158, 156 
	float m_tankRotationRadians; // = tankRotation * (M_PI / 180.0f);


public:
	//vectors
	glm::vec3 m_position;
	glm::vec3 m_headPivot;
	glm::mat4 m_tankBaseMat4;// = glm::mat4(1.0);
	glm::mat4 m_bodyMat4;
	glm::mat4 m_headMat4;

	
//Methods
public:
	//Constructor, Setters & Getters
	Tank();
	

	Model GetBodyModel() const;
	Model GetHeadModel() const;
	float GetTankRotation() const;

	//Functionalities
	void ProcessInput(GLFWwindow* window,double deltaTime);
	void UpdateRotationRadians();


private:
	void RotationAngleCorrection();

//EndMethods
};

