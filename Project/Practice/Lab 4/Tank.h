#pragma once

#define M_PI 3.14159

#include "Model.h"

enum ECameraMovementType
{
	UNKNOWN,
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};



class Tank
{
private:
	//Models
	Model m_body;


	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
	glm::vec3 worldUp;

	float yaw;
	float pitch;
	
	const float tankSpeedFactor = 2.5f;
	const float rotationSpeed = 50.0f;


	glm::vec3 startPosition;
	


public:

	Tank();
	void Set(const glm::vec3& position);
	Tank(const Tank& t1);

	void ProcessInput(ECameraMovementType direction, float deltaTime);

	void UpdateTankVectors();


	float GetYaw();

	glm::vec3 m_position;
	glm::vec3 m_scale;
	glm::quat m_rotation;
	glm::quat m_tankBodyRotation;

	glm::vec3 m_orientation;


	



	////accelerators
	//float m_tankSpeed = 2.5f; // Speed of the tank
	//float m_tankRotation = 0.0f; //-158, 156 
	//float m_tankRotationRadians; // = tankRotation * (M_PI / 180.0f);


	void DrawBody(Shader shader, Camera camera);

	

};