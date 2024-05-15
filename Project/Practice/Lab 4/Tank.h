#pragma once

#define M_PI 3.14159

#include "Model.h"




class Tank
{
private:
	//Models
	Model m_body;
	Model m_head;



	

	


public:

	Tank();

	void ProcessInput(GLFWwindow* window, double deltaTime);

	void UpdateRotationRadians();

	void RotationAngleCorrection();


	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::quat m_rotation;
	glm::quat m_headRotation;
	glm::vec3 m_headPosition;



	//accelerators
	float m_tankSpeed = 2.5f; // Speed of the tank
	float m_tankRotation = 0.0f; //-158, 156 
	float m_tankRotationRadians; // = tankRotation * (M_PI / 180.0f);


	void DrawAll(Shader shader, Camera camera);
	void DrawBody(Shader shader, Camera camera);
	void DrawHead(Shader shader, Camera camera);

	

};