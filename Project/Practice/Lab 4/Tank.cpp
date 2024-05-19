#include "Tank.h"




Tank::Tank()
{
	std::string modelPath;
	modelPath = "Models/tank/tank.gltf";
	m_body=Model(modelPath.c_str());



	


	m_rotation = (glm::angleAxis(180.0f,glm::vec3(1.0f,0.0f,0.0f)));

	m_position = glm::vec3(5.0f, -9.5f, 1.0f);
	m_scale = glm::vec3(0.5f, 0.5f, 0.5f);


	startPosition = m_position;
	Set(m_position);


}


void Tank::Set(const glm::vec3& position)
{
	this->m_position = position;
	this->yaw = 90.0f; // Facing forward initially
	this->pitch = 0.0f;

	this->worldUp = glm::vec3(0, 1, 0);

	UpdateTankVectors();
}



Tank::Tank(const Tank& t1)
{
	this->m_body = t1.m_body;

	this->m_position = t1.m_position;
	this->m_rotation = t1.m_rotation;
	this->m_scale = t1.m_scale;
	this->yaw = t1.yaw;
	this->pitch = t1.pitch;
	this->worldUp = t1.worldUp;
	this->forward = t1.forward;
	this->right = t1.right;
	this->up = t1.up;
	
}


void Tank::ProcessInput(ECameraMovementType direction, float deltaTime)
{
	float velocity = tankSpeedFactor * deltaTime;
	float rotationVelocity = rotationSpeed * deltaTime;

	switch (direction) {
	case ECameraMovementType::FORWARD:
		m_position += forward * velocity;
		break;
	case ECameraMovementType::BACKWARD:
		m_position -= forward * velocity;
		break;
	case ECameraMovementType::LEFT: // Rotate counterclockwise
		yaw += rotationVelocity;
		break;
	case ECameraMovementType::RIGHT: // Rotate clockwise
		yaw -= rotationVelocity;
		break;
	}

	UpdateTankVectors();
}

void Tank::UpdateTankVectors()
{
	// Calculate the new forward vector
	this->forward.x = cos(glm::radians(yaw));
	this->forward.z = -sin(glm::radians(yaw));
	this->forward.y = 0; // Keep the tank on the ground plane
	this->forward = glm::normalize(this->forward);

	// Also re-calculate the Right and Up vector
	this->right = glm::normalize(glm::cross(forward, worldUp)); // Normalize the vectors
	this->up = glm::normalize(glm::cross(right, forward));
}

float Tank::GetYaw()
{
	return yaw;
}


void Tank::DrawBody(Shader shader, Camera camera)
{

	m_body.Draw(shader, camera, m_position, glm::angleAxis(glm::radians(yaw), worldUp), m_scale);

}


