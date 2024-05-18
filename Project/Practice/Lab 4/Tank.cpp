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
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		m_position.x += m_tankSpeed * deltaTime;
		m_headPosition.x += m_tankSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		m_position.x -= m_tankSpeed * deltaTime;
		m_headPosition.x -= m_tankSpeed * deltaTime;
	}
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
	{
		if (90.0f * deltaTime < 156.0f)
		{
			m_tankRotation -= 90.0f * deltaTime;
		}
		//std::cout << tankRotation << "\n";
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
	{
		m_tankRotation += 90.0f * deltaTime;
		//std::cout << tankRotation << "\n";
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		m_bodyRotation -= 45.0f * deltaTime;
		m_tankRotation -= 45.0f * deltaTime;

	}
	
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_bodyRotation += 45.0f * deltaTime;
		m_tankRotation += 45.0f * deltaTime;
	}
	RotationAngleCorrection();
}


void Tank::UpdateRotationRadians()
{
	m_tankRotationRadians = m_tankRotation * (M_PI / 180.0f);
	m_bodyRotationRadians = m_bodyRotation * (M_PI / 180.0f);

	 // Decompose the current headRotation quaternion to Euler angles
	glm::vec3 euler = glm::eulerAngles(m_headRotation);
	glm::vec3 eulerBody = glm::eulerAngles(m_rotation);

	// Update only the x-axis rotation (pitch)
	euler.x = m_tankRotationRadians;
	eulerBody.x = m_bodyRotationRadians;
	

	// Recompose the quaternion with the updated x-axis rotation
	m_headRotation = glm::quat(euler);
	m_rotation = glm::quat(eulerBody);

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

	glm::vec3 m_centerOfRotation = glm::vec3(0.067f,0.0f,0.0f); // Center of rotation for the body

	glm::vec3 translation = m_position - m_centerOfRotation;

	// Apply rotation around the center of rotation
	//glm::vec3 rotatedTranslation = m_rotation * translation;

	// Calculate the final position
	//glm::vec3 finalPosition = m_centerOfRotation + rotatedTranslation;

	// Draw the body model with the final position and rotation
	m_body.Draw(shader, camera, translation, m_rotation, m_scale);



	//m_body.Draw(shader, camera, this->m_position, this->m_rotation, this->m_scale);


}

void Tank::DrawHead(Shader shader, Camera camera)
{

	
	m_head.Draw(shader, camera, m_headPosition, m_headRotation, m_scale);

}
