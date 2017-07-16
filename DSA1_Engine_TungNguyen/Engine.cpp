#include "Engine.h"

Timer Engine::timer;
GLFWwindow* Engine::GLFWwindowPtr;

Shader Engine::shader;
Camera Engine::camera;

std::vector<Model> Engine::gameModels;
std::vector<GameObject> Engine::gameObjects;
std::vector<Texture> Engine::textures;

Texture Engine::texture;

Engine::Engine()
{
}


Engine::~Engine()
{
}

bool Engine::Init()
{
	if (glfwInit() == GL_FALSE)
	{
		return false;
	}

	// Create a window
	GLFWwindowPtr = glfwCreateWindow(800, 600, "Tung Nguyen DSA1 Engine", NULL, NULL);

	// Make it the current context
	if (GLFWwindowPtr != nullptr)
	{
		glfwMakeContextCurrent(GLFWwindowPtr);
	}
	else
	{
		glfwTerminate();
		return false;
	}

	// Initialize GLEW
	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	// Background color - Cornflower blue
	glClearColor(0.392f, 0.584f, 0.929f, 1.0f);

	return true;
}

void Engine::LoadShader()
{
	shader.filenamev = "shaders/vShader.glsl";
	shader.filenamef = "shaders/fShader.glsl";

	if (shader.load())
	{
		shader.use();
	}
}

void Engine::LoadObjects()
{
	// Declare models
	// Box models
	Model groundModel;
	Model branchLeftModels[2];
	Model branchRightModels[2];
	Model goal;
	// Sphere models
	Model obstacleLeftModel;
	Model obstacleRightModel;
	Model sphere;

	// Put the models in a container
	gameModels.push_back(groundModel);
	for (int i = 0; i < 2; i++)
	{
		gameModels.push_back(branchLeftModels[i]);
		gameModels.push_back(branchRightModels[i]);
	}
	gameModels.push_back(goal);
	gameModels.push_back(obstacleLeftModel);
	gameModels.push_back(obstacleRightModel);
	gameModels.push_back(sphere);

	// Buffer the models
	for (int i = 0; i < 6; i++)
	{
		gameModels[i].buffer("models/box.obj");
	}
	for (int i = 6; i < 9; i++)
	{
		gameModels[i].buffer("models/sphere.obj");
	}

	// Declare objects
	GameObject ground;
	ground.transform.location = { 6, 0, 0 };
	ground.transform.rotation = { 0, 0, 0 };
	ground.transform.size = { 8, 1, 1 };
	ground.texFile = "textures/ground.png";
	ground.collider = GameObject::Aabb;
	ground.type = GameObject::Ground;

	GameObject branchesLeft[2];
	GameObject branchesRight[2];
	for (int i = 0; i < 2; i++)
	{
		branchesLeft[i].transform.location = { (i + 1) * 4, 0, -3 };
		branchesLeft[i].transform.rotation = { 0, 0, 0 };
		branchesLeft[i].transform.size = { 0.75, 1, 2 };
		branchesLeft[i].texFile = "textures/ground.png";
		branchesLeft[i].collider = GameObject::Aabb;
		branchesLeft[i].type = GameObject::Ground;

		branchesRight[i].transform.location = { (i + 1) * 4, 0, 3 };
		branchesRight[i].transform.rotation = { 0, 0, 0 };
		branchesRight[i].transform.size = { 0.75, 1, 2 };
		branchesRight[i].texFile = "textures/ground.png";
		branchesRight[i].collider = GameObject::Aabb;
		branchesRight[i].type = GameObject::Ground;
	}

	GameObject goalObj;
	goalObj.transform.location = { 13, 2.001, 0 };
	goalObj.transform.rotation = { 0, 0, 0 };
	goalObj.transform.size = { 0.2, 1, 1 };
	goalObj.texFile = "textures/goal.png";
	goalObj.collider = GameObject::Aabb;
	goalObj.type = GameObject::Wall;

	GameObject obstacleLeft;
	obstacleLeft.transform.location = { 4, 2, -4 };
	obstacleLeft.transform.rotation = { 0, 0, 0 };
	obstacleLeft.transform.size = { 0.5, 0.5, 0.5 };
	obstacleLeft.texFile = "textures/pokeball.png";
	obstacleLeft.collider = GameObject::Sphere;
	obstacleLeft.type = GameObject::Obstacle;

	obstacleLeft.rigidBody.vel = { 0, 0, 0 };
	obstacleLeft.rigidBody.force = { 0, 0, 0 };
	obstacleLeft.rigidBody.mass = 1;

	GameObject obstacleRight;
	obstacleRight.transform.location = { 8, 2, 4 };
	obstacleRight.transform.rotation = { 0, 0, 0 };
	obstacleRight.transform.size = { 0.5, 0.5, 0.5 };
	obstacleRight.texFile = "textures/pokeball.png";
	obstacleRight.collider = GameObject::Sphere;
	obstacleRight.type = GameObject::Obstacle;

	obstacleRight.rigidBody.vel = { 0, 0, 0 };
	obstacleRight.rigidBody.force = { 0, 0, 0 };
	obstacleRight.rigidBody.mass = 1;

	GameObject sphereObj;
	sphereObj.transform.location = { 0, 2, 0 };
	sphereObj.transform.rotation = { 0, 0, 0 };
	sphereObj.transform.size = { 0.5, 0.5, 0.5 };
	sphereObj.texFile = "textures/ball.png";
	sphereObj.collider = GameObject::Sphere;
	sphereObj.type = GameObject::Player;

	sphereObj.rigidBody.vel = { 0, 0, 0 };
	sphereObj.rigidBody.force = { 0, 0, 0 };
	sphereObj.rigidBody.mass = 1;

	// Put the game objects in a big group
	gameObjects.push_back(ground);
	for (int i = 0; i < 2; i++)
	{
		gameObjects.push_back(branchesLeft[i]);
		gameObjects.push_back(branchesRight[i]);
	}
	gameObjects.push_back(goalObj);
	gameObjects.push_back(obstacleLeft);
	gameObjects.push_back(obstacleRight);
	gameObjects.push_back(sphereObj);
}

int Engine::LoadTextures(char* filename)
{
	Engine::texture.filename = filename;
	Engine::texture.load();

	return Engine::texture.textID;
}

void Engine::GameLoop()
{
	// Game loop until the user closes the window
	while (!glfwGetKey(GLFWwindowPtr, GLFW_KEY_ESCAPE))
	{
		timer.Update();
		// Process queued window, mouse & keyboard callback events
		glfwPollEvents();

		glfwSetInputMode(GLFWwindowPtr, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		// Clear the canvas
		//glClear(GL_COLOR_BUFFER_BIT);

		// Wireframe mode
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUniform1f(3, 1.0f);

		// Render the game objects
		for (size_t i = 0; i < gameObjects.size(); i++)
		{
			glm::mat4 myObject = glm::translate(gameObjects[i].transform.location) * glm::yawPitchRoll(0.0f, 0.0f, 0.0f) * glm::scale(gameObjects[i].transform.size);
			gameObjects[i].transform.modelWorld = myObject;
			glUniformMatrix4fv(6, 1, GL_FALSE, &gameObjects[i].transform.modelWorld[0][0]);

			for (size_t j = 0; j < textures.size(); j++)
			{
				if (gameObjects[i].texFile == textures[j].filename)
				{
					glBindTexture(GL_TEXTURE_2D, textures[j].textID);
				}
			}

			gameModels[i].render();
			glBindVertexArray(0);
		}
		
		// Check for ground collisions
		int isPlayerGrounded = 0;
		int isObstacleGrounded = 0;
		for (size_t i = 0; i < 5; i++)
		{
			if (gameObjects[8].CollidesWith(gameObjects[i]))
			{
				isPlayerGrounded++;
			}
			for (size_t j = 6; j < 8; j++)
			{
				if (gameObjects[j].CollidesWith(gameObjects[i]))
				{
					isObstacleGrounded++;
				}
			}
		}
		if (isPlayerGrounded == 0)
		{
			gameObjects[8].isGrounded = false;
		}
		else
		{
			gameObjects[8].isGrounded = true;;
		}
		for (size_t i = 6; i < 8; i++)
		{
			if (isObstacleGrounded == 0)
			{
				gameObjects[i].isGrounded = false;
			}
			else
			{
				gameObjects[i].isGrounded = true;
			}
		}

		// Check for other collisions and update other game objects
		for (size_t i = 5; i < gameObjects.size() - 1; i++)
		{
			gameObjects[8].CollidesWith(gameObjects[i]);
			gameObjects[i].Update();
		}
		
		// Update player control
		gameObjects[8].Update();

		// Make camera stick to the player
		camera.loc = { gameObjects[8].transform.location.x - 2, gameObjects[8].transform.location.y + 1.5, gameObjects[8].transform.location.z };

		//Upload light and camera locations
		glUniform3f(1, 0, 1, 2);
		glUniform3f(2, camera.loc.x, camera.loc.y, camera.loc.z);
		
		// Update the camera
		//camera.move(GLFWwindowPtr);
		camera.turn(GLFWwindowPtr); // Let the player look around using the mouse
		camera.upload();

		// Swap the front (what the screen displays) and the back (what OpenGL draws to) buffer
		glfwSwapBuffers(GLFWwindowPtr);
	}
}
