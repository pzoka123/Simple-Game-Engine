#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>

#include <FreeImage.h>
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\euler_angles.hpp>

class Model
{
private:
	unsigned int vertCount;
	GLuint vertArr;

public:
	Model();
	~Model();

	virtual bool buffer(std::string objFile);
	virtual void render();
};

struct Vertex
{
	glm::vec3 location;
	glm::vec2 uv;
	glm::vec3 normal;
};

struct VertInd
{
	unsigned int locInd, uvInd, normInd;
};

