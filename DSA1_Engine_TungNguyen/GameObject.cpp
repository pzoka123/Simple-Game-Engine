#include "GameObject.h"

#include "Engine.h"

#include <iostream>

GameObject::GameObject()
{
}


GameObject::~GameObject()
{
}

void GameObject::Update()
{
	if (type == Player)
	{
		Control();
	}
	else if (type == Obstacle)
	{
		ObsMove();
	}
	else if (type == Ground)
	{

	}
	else if (type == Wall)
	{

	}
}

void GameObject::Control()
{
	if (isGrounded == false)
	{
		rigidBody.force += gravity;
	}

	if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_S) == GLFW_PRESS)
	{
		rigidBody.force.x -= 3;
	}
	if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_W) == GLFW_PRESS && isCollidedFront == false)
	{
		rigidBody.force.x += 3;
	}
	if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_A) == GLFW_PRESS)
	{
		rigidBody.force.z -= 3;
	}
	if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_D) == GLFW_PRESS)
	{
		rigidBody.force.z += 3;
	}
	if (glfwGetKey(Engine::GLFWwindowPtr, GLFW_KEY_SPACE) == GLFW_PRESS && isGrounded == true)
	{
		rigidBody.vel.y += 3;
	}

	if (transform.location.y < -3)
	{
		transform.location = { 0, 3, 0 };
		rigidBody.force = { 0, 0, 0 };
		rigidBody.vel = { 0, 0, 0 };
	}

	rigidBody.force += rigidBody.vel * -0.5f;

	rigidBody.vel += rigidBody.force / rigidBody.mass * Engine::timer.deltaT;

	transform.location += rigidBody.vel * Engine::timer.deltaT;

	rigidBody.force = { 0, 0, 0 };
}

void GameObject::ObsMove()
{
	if (isGrounded == false)
	{
		rigidBody.force += gravity;
	}
	if (transform.location.z <= -4)
	{
		rigidBody.vel.z = 3;
	}
	else if (transform.location.z >= 4)
	{
		rigidBody.vel.z = -3;
	}
	rigidBody.vel.y += rigidBody.force.y / rigidBody.mass * Engine::timer.deltaT;
	transform.location += rigidBody.vel * Engine::timer.deltaT;
}

bool GameObject::CollidesWith(const GameObject &another)
{
	glm::vec3 distance = transform.location - another.transform.location;
	
	if (collider == Sphere && another.collider == Aabb)
	{
		// Collision between the player or obstacles and the ground
		if (another.type == Ground || transform.location.y > another.transform.location.y + another.transform.size.y)
		{
			glm::vec3 e = 1.0f * another.transform.size;
			glm::vec3 point = another.transform.location + glm::clamp(distance, -e, e);
			glm::vec3 Dp = transform.location - point;
			float distLength = glm::length(Dp);

			if (distLength > transform.size.y)
			{
				return false;
			}
			else
			{
				rigidBody.vel.y = 0;
				rigidBody.force.y = 0;
				return true;
			}
		}

		// Collision between the player and the goal
		if (transform.location.x < another.transform.location.x - another.transform.size.x || transform.location.x >  another.transform.location.x + another.transform.size.x)
		{
			glm::vec3 e = 1.0f * another.transform.size;
			glm::vec3 point = another.transform.location + glm::clamp(distance, -e, e);
			glm::vec3 Dp = transform.location - point;
			float distLength = glm::length(Dp);

			if (distLength > transform.size.x)
			{
				isCollidedFront = false;
				return false;
			}
			else
			{
				rigidBody.vel.x = -rigidBody.vel.x;
				rigidBody.force.x = -rigidBody.force.x;
				isCollidedFront = true;
				return true;
			}
		}
	}

	// Collision between the player and the obstacles
	if (collider == Sphere && another.collider == Sphere)
	{
		float distLength = glm::length(distance);
		if (distLength > transform.size.x + another.transform.size.x)
		{
			return false;
		}
		else
		{
			rigidBody.vel += distance;
			return true;
		}
	}

	return true;
}
