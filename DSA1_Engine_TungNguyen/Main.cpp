// include with < >: external library, not in project dir, we didn't make it
#include <iostream>
#include <vector>

// include with " ": headers we created, is in project dir
// #include "include\FreeImage.h"

#include <FreeImage.h>

#include <GL\glew.h>		// dont switch these
#include <GLFW\glfw3.h>		// dont switch these

#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

#include "Engine.h"


int main()
{
	Engine::Init();
	Engine::LoadShader();

	Engine::camera.start();

	Engine::LoadObjects();

	Engine::timer.curr = (float)glfwGetTime();

	Texture testTexture;
	testTexture.filename = "textures/TestTexture.png";
	testTexture.textID = Engine::LoadTextures("textures/TestTexture.png");
	Texture goal;
	goal.filename = "textures/goal.png";
	goal.textID = Engine::LoadTextures("textures/goal.png");
	Texture ground;
	ground.filename = "textures/ground.png";
	ground.textID = Engine::LoadTextures("textures/ground.png");
	Texture ball;
	ball.filename = "textures/ball.png";
	ball.textID = Engine::LoadTextures("textures/ball.png");
	Texture poke;
	poke.filename = "textures/pokeball.png";
	poke.textID = Engine::LoadTextures("textures/pokeball.png");

	Engine::textures.push_back(testTexture);
	Engine::textures.push_back(goal);
	Engine::textures.push_back(ground);
	Engine::textures.push_back(ball);
	Engine::textures.push_back(poke);

	Engine::GameLoop();

	glfwTerminate();

	return 0;
}