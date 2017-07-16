#version 430

layout (location = 0) in vec3 position;
layout (location = 7) in vec2 uv;
layout (location = 8) in vec3 norm;

out vec3 fragLoc;
out vec3 fragNorm;

//out float red;

out vec2 fragUV;

layout (location = 3) uniform float scale;

layout (location = 5) uniform mat4 worldView;

layout (location = 6) uniform mat4 modelWorld;

void main()
{
	fragUV = uv;
	fragLoc = position;
	fragNorm = norm;

	gl_Position = worldView * modelWorld * vec4(position * scale, 1);
	//red = (position.x + 1)/2;
}