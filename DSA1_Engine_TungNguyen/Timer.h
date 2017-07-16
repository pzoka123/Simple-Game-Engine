#pragma once

#include <iostream>

#include <FreeImage.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

class Timer
{

public:
	float prev, curr, deltaT;

	Timer();
	~Timer();

	void Update();
};

