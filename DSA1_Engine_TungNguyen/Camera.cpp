#include "Camera.h"
#include "Engine.h"


Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::upload()
{
	glm::mat4 perspectiveMat = glm::perspective(fov, aspect, zNear, zFar);
	worldView = perspectiveMat * glm::lookAt(loc, loc + rotMat * glm::vec3(0, 0, -1), rotMat * glm::vec3(0, 1, 0));
	glUniformMatrix4fv(5, 1, GL_FALSE, &worldView[0][0]);
}

void Camera::start()
{
	worldView = glm::mat4();

	glfwGetWindowSize(glfwGetCurrentContext(), &w, &h);
	aspect = (float)w / (float)h;
}


void Camera::turn(GLFWwindow* window)
{
	glfwGetCursorPos(window, &x, &y);

	rotAng.y += sens * (w * 0.5f - (float)x);
	rotAng.x += sens * (h * 0.5f - (float)y);
	rotAng.x = glm::clamp(rotAng.x, -0.5f * 3.14f, 0.5f * 3.14f);
	glfwSetCursorPos(window, w * 0.5f, h * 0.5f);

	rotMat = (glm::mat3)glm::yawPitchRoll(rotAng.y, rotAng.x, rotAng.z);
}

void Camera::move(GLFWwindow* window)
{
	glm::vec3 camVel;
	glm::mat3 R = (glm::mat3)glm::yawPitchRoll(rotAng.y, rotAng.x, rotAng.z);

	if (glfwGetKey(window, GLFW_KEY_LEFT))
	{
		camVel += R * glm::vec3(-1, 0, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT))
	{
		camVel += R * glm::vec3(1, 0, 0);
	}
	if (glfwGetKey(window, GLFW_KEY_UP))
	{
		camVel += R * glm::vec3(0, 0, -1);
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN))
	{
		camVel += R * glm::vec3(0, 0, 1);
	}

	float speed = 3.0f;
	if (camVel != glm::vec3())
	{
		camVel = glm::normalize(camVel) * speed;
	}

	vel = camVel;

	loc += vel * Engine::timer.deltaT;
}
