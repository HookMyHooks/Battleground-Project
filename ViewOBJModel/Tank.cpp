#include "Tank.h"


Tank::Tank()
{
	wchar_t buffer[MAX_PATH];
	GetCurrentDirectoryW(MAX_PATH, buffer);

	std::wstring executablePath(buffer);
	std::wstring wscurrentPath = executablePath.substr(0, executablePath.find_last_of(L"\\/"));

	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	std::string currentPath = converter.to_bytes(wscurrentPath);

	m_bodyModel = Model(currentPath + "\\Models\\Tank\\body.obj", false);
	m_headModel = Model(currentPath + "\\Models\\Tank\\head.obj", false);
	m_tankSpeed = 2.5f;
	m_tankRotation = 0.0f;

}

void Tank::ProcessInput(GLFWwindow *window, double deltaTime)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		m_position.z += m_tankSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		m_position.z -= m_tankSpeed * deltaTime;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		if (90.0f * deltaTime < 156.0f)
		{
			m_tankRotation += 90.0f * deltaTime;
		}
		//std::cout << tankRotation << "\n";
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		m_tankRotation -= 90.0f * deltaTime;
		//std::cout << tankRotation << "\n";
	}
	RotationAngleCorrection();
}

Model Tank::GetBodyModel() const
{
	return m_bodyModel;
}

float Tank::GetTankRotation() const
{
	return m_tankRotation;
}

Model Tank::GetHeadModel() const
{
	return m_headModel;
}



void Tank::UpdateRotationRadians()
{
	m_tankRotationRadians = m_tankRotation * (M_PI / 180.0f);
}


void Tank::RotationAngleCorrection()
{
	if (m_tankRotation >= 156.0f)
		m_tankRotation = 156.0f;
	if (m_tankRotation < -158.0f)
		m_tankRotation = -158.0f;
}



