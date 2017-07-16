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

class Shader
{
	GLuint program, vprogram, fprogram, tempProgram;

public:
	std::string filenamev;
	std::string filenamef;

	Shader();
	~Shader();

	bool load();
	bool compile(GLenum shaderType, std::string filename);
	void use();
	void unload();
};

