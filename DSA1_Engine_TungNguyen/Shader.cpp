#include "Shader.h"



Shader::Shader()
{
}


Shader::~Shader()
{
}

bool Shader::load()
{
	bool vertexCompile = compile(GL_VERTEX_SHADER, filenamev);
	vprogram = tempProgram;
	bool fragmnetCompile = compile(GL_FRAGMENT_SHADER, filenamef);
	fprogram = tempProgram;

	if (!vertexCompile || !fragmnetCompile)
	{
		return false;
	}

	program = glCreateProgram();
	glAttachShader(program, vprogram);
	glAttachShader(program, fprogram);
	glLinkProgram(program);

	GLint result;
	GLint logLength;
	GLchar* logArray = nullptr;

	glGetProgramiv(program, GL_LINK_STATUS, &result);
	if (result != 0)
	{
		return true;
	}
	else
	{
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);

		logArray = new GLchar[logLength];
		glGetProgramInfoLog(program, logLength, 0, logArray);
	}

	glDeleteShader(program);
	delete[] logArray;

	return false;
}

bool Shader::compile(GLenum shaderType, std::string filename)
{
	std::ifstream instream(filename, std::ios::binary);		// open in binary mode
	if (!instream.is_open())
	{
		printf("Error opening file\n");
		return 0;
	}

	// get length of file
	instream.seekg(0, std::ios::end);	// go to end of file
	int length = (int)instream.tellg();		// what is file length?
	instream.seekg(0, std::ios::beg);	// go to beginning

										// read it all at once
	char* source = new char[length + 1];
	source[length] = '\0';
	instream.read(source, length);		// read to where, how many bytes?

										// close file
	instream.close();		// destructor does this if you forget to

	tempProgram = glCreateShader(shaderType);
	glShaderSource(tempProgram, 1, &source, 0);
	glCompileShader(tempProgram);

	GLint result;
	GLint logLength;
	GLchar* logArray = nullptr;

	glGetShaderiv(tempProgram, GL_COMPILE_STATUS, &result);
	if (result != 0)
	{
		return true;
	}
	else
	{
		glGetShaderiv(tempProgram, GL_INFO_LOG_LENGTH, &logLength);
	}

	logArray = new GLchar[logLength];

	glGetShaderInfoLog(tempProgram, logLength, 0, logArray);

	glDeleteShader(tempProgram);

	delete[] logArray;

	return false;
}

void Shader::use()
{
	glUseProgram(program);
}

void Shader::unload()
{
	glDeleteProgram(program);
	glDeleteShader(vprogram);
	glDeleteShader(fprogram);

	program = 0;
	vprogram = 0;
	fprogram = 0;
}
