#include "Tank.h"

Tank::Tank()
{
	std::string modelPath;
	modelPath = "Models/tank/tankBody.gltf";
	m_body=Model(modelPath.c_str());

	modelPath = "Models/tank/tankHead.gltf";
	m_head = Model(modelPath.c_str());


	m_tankSpeed = 2.0f;
	m_tankRotation = 0.0f;


	float angleRadians = glm::radians(90.0f);
	m_rotation = glm::angleAxis(angleRadians, glm::vec3(0.0f, 0.0f, -1.0f));
	m_headRotation = m_rotation;

	m_position = glm::vec3(5.0f, -9.5f, 1.0f);
	m_scale = glm::vec3(0.5f, 0.5f, 0.5f);

	m_headPosition = glm::vec3(5.17f, -9.5f, 1.0f);
}

Tank::Tank(const Tank& t1)
{
	this->m_body = t1.m_body;
	this->m_head = t1.m_head;
	this->m_headPosition = t1.m_headPosition;
	this->m_headRotation = t1.m_headRotation;
	this->m_position = t1.m_position;
	this->m_rotation = t1.m_rotation;
	this->m_scale = t1.m_scale;
	this->m_tankRotation = t1.m_tankRotation;
	this->m_tankRotationRadians = t1.m_tankRotationRadians;
	this->m_tankSpeed = t1.m_tankSpeed;
}


void Tank::ProcessInput(GLFWwindow* window, double deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		m_position.x += m_tankSpeed * deltaTime;
		m_headPosition.x += m_tankSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		m_position.x -= m_tankSpeed * deltaTime;
		m_headPosition.x -= m_tankSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		if (90.0f * deltaTime < 156.0f)
		{
			m_tankRotation -= 90.0f * deltaTime;
		}
		//std::cout << tankRotation << "\n";
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		m_tankRotation += 90.0f * deltaTime;
		//std::cout << tankRotation << "\n";
	}
	RotationAngleCorrection();
}


void Tank::UpdateRotationRadians()
{
	m_tankRotationRadians = m_tankRotation * (M_PI / 180.0f);
	//m_headRotation = glm::angleAxis(m_tankRotationRadians, glm::vec3(1.0f, 0.0f, 0.0f));

	 // Decompose the current headRotation quaternion to Euler angles
	glm::vec3 euler = glm::eulerAngles(m_headRotation);

	// Update only the x-axis rotation (pitch)
	euler.x = m_tankRotationRadians;
	

	// Recompose the quaternion with the updated x-axis rotation
	m_headRotation = glm::quat(euler);

}


void Tank::RotationAngleCorrection()
{
	if (m_tankRotation >= 156.0f)
		m_tankRotation = 156.0f;
	if (m_tankRotation < -158.0f)
		m_tankRotation = -158.0f;
}

void Tank::DrawAll(Shader shader, Camera camera)
{
	m_body.Draw(shader, camera, this->m_position, this->m_rotation, this->m_scale);

	m_head.Draw(shader, camera, this->m_position, this->m_rotation, this->m_scale);


}

void Tank::DrawBody(Shader shader, Camera camera)
{

	m_body.Draw(shader, camera, this->m_position, this->m_rotation, this->m_scale);


}

void Tank::DrawHead(Shader shader, Camera camera)
{

	
	m_head.Draw(shader, camera, m_headPosition, m_headRotation, m_scale);

}
