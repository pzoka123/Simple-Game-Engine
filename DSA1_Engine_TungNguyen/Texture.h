#pragma once

#include <iostream>
#include <string>
#include <fstream>

#include <FreeImage.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

class Texture
{
public:
	char* filename;
	unsigned int textID;

	Texture();
	~Texture();

	virtual void use();
	virtual void load();
	void unload();
};

