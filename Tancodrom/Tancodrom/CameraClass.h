#pragma once
#include <stdlib.h> // necesare pentru citirea shader-elor
#include <stdio.h>
#include <math.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glew.h>
#include <glfw3.h>
#include <GLM.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <gtx/quaternion.hpp>
#include <gtx/euler_angles.hpp>


#include <glfw3.h>

#include <iostream>

#pragma comment (lib, "glfw3dll.lib")
#pragma comment (lib, "glew32.lib")
#pragma comment (lib, "OpenGL32.lib")



class Camera
{
private:
    // Default camera values
    const float zNEAR = 0.1f;
    const float zFAR = 500.f;
    const float YAW = -90.0f;
    const float PITCH = 0.0f;
    const float FOV = 45.0f;
    glm::vec3 startPosition;
    glm::quat orientation;



public:
    Camera(const int width, const int height, const glm::vec3& position);



    void MoveFrontQuat(float deltaTime);

    void MoveBackwardQuat(float deltaTime);

    void MoveRightQuat(float deltaTime);

    void MoveLeftQuat(float deltaTime);

    void MoveUpQuat(float deltaTime);

    void MoveDownQuat(float deltaTime);

    void ResetCamera();



    void MouseControl(float xPos, float yPos);
    void ProcessMouseScroll(float FovY);


    void Set(const int width, const int height, const glm::vec3& position);


    const glm::mat4 GetViewMatrix() const
    {
        // Returns the View Matrix
        return glm::lookAt(position, position + forward, up);
    }

    const glm::mat4 GetProjectionMatrix() const
    {
        glm::mat4 Proj = glm::mat4(1);
        if (isPerspective) {
            float aspectRatio = ((float)(width)) / height;
            Proj = glm::perspective(glm::radians(FoVy), aspectRatio, zNear, zFar);
        }
        else {
            float scaleFactor = 2000.f;
            Proj = glm::ortho<float>(
                -width / scaleFactor, width / scaleFactor,
                -height / scaleFactor, height / scaleFactor, -zFar, zFar);
        }
        return Proj;
    }

private:
    void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);



    void UpdateCameraQuaternionVectors();

protected:
    const float cameraSpeedFactor = 200.0f;
    const float mouseSensitivity = 0.1f;

    // Perspective properties
    float zNear;
    float zFar;
    float FoVy;
    int width;
    int height;
    bool isPerspective;

    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;
    glm::vec3 worldUp;

    // Euler Angles
    float yaw;
    float pitch;

    bool bFirstMouseMove = true;
    float lastX = 0.f, lastY = 0.f;
};