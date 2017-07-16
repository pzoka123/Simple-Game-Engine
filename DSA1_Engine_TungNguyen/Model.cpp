#include "Model.h"



Model::Model()
{
	vertCount = 0;
	vertArr = 0;
}


Model::~Model()
{
}

bool Model::buffer(std::string objFile)
{
	std::vector<glm::vec3> locations;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<VertInd> vertInds;

	std::ifstream file;
	std::string line;

	std::string label;
	float first, second, third;
	unsigned int num1, num2, num3;
	char slash;
	VertInd tempInd;

	file.open(objFile);
	if (file.is_open())
	{
		while (std::getline(file, line))
		{
			std::istringstream fileData(line);
			fileData >> label;

			if (label == "v")
			{
				fileData >> first >> second >> third;
				glm::vec3 tempVertLoc = { first, second, third };
				locations.push_back(tempVertLoc);
			}
			else if (label == "vt")
			{
				fileData >> first >> second;
				glm::vec2 tempVertTex = { first, second };
				uvs.push_back(tempVertTex);
			}
			else if (label == "vn")
			{
				fileData >> first >> second >> third;
				glm::vec3 tempVertNorm = { first, second, third };
				normals.push_back(tempVertNorm);
			}
			else if (label == "f")
			{
				for (int i = 0; i < 3; i++)
				{
					fileData >> num1 >> slash >> num2 >> slash >> num3;
					num1--;
					num2--;
					num3--;
					tempInd.locInd = num1;
					tempInd.uvInd = num2;
					tempInd.normInd = num3;
					vertInds.push_back(tempInd);
				}
			}
		}

		file.close();
	}

	vertCount = vertInds.size();


	// Duplicate vertices into a single buffer
	std::vector<Vertex> vertBufData(vertCount);

	for (unsigned int i = 1; i < vertCount; i++)
	{
		vertBufData[i] = { locations[vertInds[i].locInd],
						   uvs[		 vertInds[i].uvInd ],
						   normals[	vertInds[i].normInd]	};
	}

	GLuint vertBuf;

	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	glBufferData(
		GL_ARRAY_BUFFER,	// Where to copy to
		sizeof(Vertex) * vertCount,	// # bytes to copy
		&vertBufData[0],	// Where to copy from
		GL_STATIC_DRAW		// "hint" to OpenGL
	);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,		// Attribute index
		3,		// Number of components (x, y, z)
		GL_FLOAT,	// Type of data
		GL_FALSE,	// Should we normalize the data?
		sizeof(Vertex),	// Stride (Bytes per vertex)
		0		// Offset to this attribute
	);
	glBindVertexArray(9);		// unbind when finished editing

	glEnableVertexAttribArray(7);
	glVertexAttribPointer(
		7,		// Attribute index
		2,		// Number of components (x, y, z)
		GL_FLOAT,	// Type of data
		GL_FALSE,	// Should we normalize the data?
		sizeof(Vertex),	// Stride (Bytes per vertex)
		(void*)sizeof(glm::vec3)		// Offset to this attribute
	);
	glBindVertexArray(9);		// unbind when finished editing

	glEnableVertexAttribArray(8);
	glVertexAttribPointer(
		8,		// Attribute index
		3,		// Number of components (x, y, z)
		GL_FLOAT,	// Type of data
		GL_FALSE,	// Should we normalize the data?
		sizeof(Vertex),	// Stride (Bytes per vertex)
		(void*)(sizeof(float)*5)	// Offset to this attribute
	);
	glBindVertexArray(9);		// unbind when finished editing

	return true;
}

void Model::render()
{
	// Render game objects
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
}
