#pragma once
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>


class ThirdPersonCamera
{

private:
    glm::vec3 position;
    glm::vec3 targetPosition;
    glm::vec3 up;
    float distanceToTarget;
    float pitch;
    float yaw;



public:


    ThirdPersonCamera(const glm::vec3& targetPosition, float distanceToTarget, float pitch, float yaw);

    void UpdateCameraPosition();

    void SetTargetPosition(const glm::vec3& newTargetPosition);

    void SetYaw(float newYaw);

    void SetPitch(float newPitch);

    glm::mat4 GetViewMatrix() const;

    glm::vec3 GetPosition() const;

};

