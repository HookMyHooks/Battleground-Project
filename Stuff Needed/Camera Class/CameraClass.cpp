#define GLM_ENABLE_EXPERIMENTAL
#include "CameraClass.h"
#include <gtx/rotate_vector.hpp>

Camera::Camera(const int width, const int height, const glm::vec3& position)
{
	startPosition = position;
	Set(width, height, position);
	orientation = glm::quat(1, 0, 0, 0);
}


void Camera::ProcessMouseScroll(float FovY)
{
	this->FoVy -= FovY;


}


void Camera::MoveFrontQuat(float deltaTime)
{
	float cameraSpeed = cameraSpeedFactor * deltaTime;
	position += forward * cameraSpeed;
	UpdateCameraQuaternionVectors();
}






void Camera::MoveBackwardQuat(float deltaTime)
{
	float cameraSpeed = cameraSpeedFactor * deltaTime;
	position -= forward * cameraSpeed;
	UpdateCameraQuaternionVectors();
}



void Camera::MoveRightQuat(float deltaTime)
{
	float cameraSpeed = cameraSpeedFactor * deltaTime;
	position += right * cameraSpeed;
	UpdateCameraQuaternionVectors();


}

}

void Camera::MoveLeftQuat(float deltaTime)
{
	float cameraSpeed = cameraSpeedFactor * deltaTime;
	position -= right * cameraSpeed;
	UpdateCameraQuaternionVectors();

}



void Camera::MoveUpQuat(float deltaTime)
{
	float cameraSpeed = cameraSpeedFactor * deltaTime;
	position += up * cameraSpeed;
	UpdateCameraQuaternionVectors();
}


void Camera::MoveDownQuat(float deltaTime)
{
	float cameraSpeed = cameraSpeedFactor * deltaTime;
	position -= up * cameraSpeed;
	UpdateCameraQuaternionVectors();

}

void Camera::ResetCamera()
{
	position = startPosition;
	yaw = YAW;
	pitch = PITCH;
	FoVy = FOV;
	orientation = glm::quat(1, 0, 0, 0);
	UpdateCameraVectors();
}


void Camera::Set(const int width, const int height, const glm::vec3& position)
{
	this->isPerspective = true;
	this->yaw = YAW;
	this->pitch = PITCH;

	this->FoVy = FOV;
	this->width = width;
	this->height = height;
	this->zNear = zNEAR;
	this->zFar = zFAR;

	this->worldUp = glm::vec3(0, 1, 0);
	this->position = position;

	lastX = width / 2.0f;
	lastY = height / 2.0f;
	bFirstMouseMove = true;

	UpdateCameraVectors();
}


void Camera::MouseControl(float xPos, float yPos)
{

	if (bFirstMouseMove)
	{
		lastX = xPos;
		lastY = yPos;
		bFirstMouseMove = false;
	}
	float xChange = (xPos - lastX) * mouseSensitivity;
	float yChange = (yPos - lastY) * mouseSensitivity;
	lastX = xPos;
	lastY = yPos;



	ProcessMouseMovement(-xChange, -yChange);
}

void Camera::ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch)
{	

// Convert mouse offsets to radians
	xOffset *= mouseSensitivity;
	yOffset *= mouseSensitivity;

	// Create quaternions representing rotation around right and worldUp vectors
	glm::quat pitchQuat = glm::angleAxis(glm::radians(yOffset), right);
	glm::quat yawQuat = glm::angleAxis(glm::radians(xOffset), worldUp);

	// Update orientation quaternion by multiplying with pitch and yaw quaternions
	orientation = glm::normalize(yawQuat * pitchQuat * orientation);

	// Constrain pitch if necessary
	if (constrainPitch) {
		// Ensure pitch stays within [-89, 89] degrees
		float dotProduct = glm::dot(glm::normalize(orientation * glm::vec3(1.0f, 0.0f, 0.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
		pitch = glm::degrees(asinf(glm::clamp(dotProduct, -1.0f, 1.0f)));
	}
	
	UpdateCameraQuaternionVectors();

}


void Camera::UpdateCameraQuaternionVectors()
{

	// Calculate the forward vector by rotating the world forward vector by the orientation quaternion
	forward = glm::rotate(orientation, glm::vec3(0.0f, 0.0f, -1.0f));

	// Calculate the right vector by rotating the world right vector by the orientation quaternion
	right = glm::rotate(orientation, glm::vec3(1.0f, 0.0f, 0.0f));

	// Calculate the up vector by rotating the world up vector by the orientation quaternion
	up = glm::rotate(orientation, glm::vec3(0.0f, 1.0f, 0.0f));

	// Normalize the vectors
	forward = glm::normalize(forward);
	right = glm::normalize(right);
	up = glm::normalize(up);
}
