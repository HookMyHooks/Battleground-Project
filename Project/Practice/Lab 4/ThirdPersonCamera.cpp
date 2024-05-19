#include "ThirdPersonCamera.h"


ThirdPersonCamera::ThirdPersonCamera(const glm::vec3& targetPosition, float distanceToTarget, float pitch, float yaw)
    : targetPosition(targetPosition), distanceToTarget(distanceToTarget), pitch(pitch), yaw(yaw)
{
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    UpdateCameraPosition();
}

void ThirdPersonCamera::UpdateCameraPosition()
{
    // Calculate camera position using spherical coordinates
    position.x = targetPosition.x + distanceToTarget * cos(glm::radians(pitch)) * sin(glm::radians(yaw));
    position.y = targetPosition.y + distanceToTarget * sin(glm::radians(pitch));
    position.z = targetPosition.z + distanceToTarget * cos(glm::radians(pitch)) * cos(glm::radians(yaw));
}

void ThirdPersonCamera::SetTargetPosition(const glm::vec3& newTargetPosition)
{
    targetPosition = newTargetPosition;
    UpdateCameraPosition();
}

void ThirdPersonCamera::SetYaw(float newYaw)
{
    yaw = newYaw;
    UpdateCameraPosition();
}

void ThirdPersonCamera::SetPitch(float newPitch)
{
    pitch = newPitch;
    UpdateCameraPosition();
}

glm::mat4 ThirdPersonCamera::GetViewMatrix() const
{
    return glm::lookAt(position, targetPosition, up);
}

glm::vec3 ThirdPersonCamera::GetPosition() const
{
    return position;
}