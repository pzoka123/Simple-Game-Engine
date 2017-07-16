#pragma once

#include <iostream>

#include <FreeImage.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

class Camera
{
	float sens = 0.005f;
	float zoom = 1.0f;
	
	int w, h;
	double x, y;

	float fov = 3.14f * 0.4f / zoom;
	float aspect;
	float zNear = 0.01f;
	float zFar = 1000.0f;

public:
	glm::mat4 worldView;
	glm::vec3 loc = { -2, 3, 0 }, vel;
	glm::mat3 rotMat;
	glm::vec3 rotAng;

	Camera();
	~Camera();

	void upload();
	void start();
	void turn(GLFWwindow* window);
	void move(GLFWwindow* window);
};

