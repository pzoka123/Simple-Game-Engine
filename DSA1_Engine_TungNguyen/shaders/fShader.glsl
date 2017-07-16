#version 430

uniform sampler2D myTexture;
in vec2 fragUV;

//out vec4 fragColor;
//in float red;
//layout (location = 4) uniform float time;

layout (location = 1) uniform vec3 lightLoc;
layout (location = 2) uniform vec3 camLoc;
in vec3 fragLoc;
in vec3 fragNorm;

void main()
{
	vec3 L = normalize(lightLoc - fragLoc);
	vec3 V = normalize(camLoc - fragLoc);
	vec3 H = normalize(L + V);
	vec3 N = normalize(fragNorm);

	float amb = 0.5;
	float dif = 0.5 * max(dot(L,N),0);
	float spec = 0.5 * pow(max(dot(H,N),0),16);
	float bright = amb + dif + spec;

	//float green = (sin(time)+1)/2;
	//fragColor = vec4(red, green, 0, 1);
	//vec4 baseColor = vec4(1, 0, 0, 1);
	vec4 baseColor = texture(myTexture, fragUV);
	
	gl_FragColor = vec4(bright * baseColor.rgb, baseColor.a);
	//gl_FragColor = texture(myTexture, fragUV);
	//gl_FragColor = vec4(fragUV, 1, 0);
}