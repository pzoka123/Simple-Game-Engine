#pragma once

#include <iostream>

#include <FreeImage.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

#include "Shader.h"
#include "Camera.h"
#include "Model.h"
#include "Texture.h"
#include "Timer.h"
#include "GameObject.h"

class Engine
{
	//struct Transform
	//{
	//	glm::vec3 location, rotation, size;
	//	glm::mat4 modelWorld;
	//};
	//
	//struct Object
	//{
	//	Transform transform;
	//	char* texFile;
	//};

public:
	static Timer timer;
	static GLFWwindow* GLFWwindowPtr;

	static Shader shader;
	static Camera camera;

	static std::vector<Model> gameModels;
	static std::vector<GameObject> gameObjects;
	static std::vector<Texture> textures;

	static Texture texture;

	Engine();
	~Engine();

	static bool Init();
	static void LoadShader();
	static void LoadObjects();
	static int LoadTextures(char* filename);
	static void GameLoop();
};

