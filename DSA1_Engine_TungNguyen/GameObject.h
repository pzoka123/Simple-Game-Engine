#pragma once

#include <iostream>

#include <FreeImage.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

class GameObject
{
	struct Transform
	{
		glm::vec3 location, rotation, size;
		glm::mat4 modelWorld;
	};

	struct RigidBody
	{
		glm::vec3 vel, force;
		float mass;
	};

public:
	Transform transform;
	RigidBody rigidBody;
	char* texFile;
	
	glm::vec3 gravity = { 0, -3, 0 };
	bool isGrounded;
	bool isCollidedFront = false;

	enum Type {
		Player,
		Obstacle,
		Ground,
		Wall,
	};
	Type type;

	enum Collider {
		Colliderless,
		Aabb,
		Sphere,
	};
	Collider collider;

	GameObject();
	~GameObject();

	void Update();
	void Control();
	void ObsMove();
	bool CollidesWith(const GameObject &another);
};

