#version 460 core
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in vec3 vNormal;
layout(location = 3) in vec3 vTangent;
layout(location = 4) in vec3 vBitangent;

out vec2 fTexCoord;

uniform mat4 uMVP;

void main()
{
	gl_Position = uMVP * vec4(vPosition, 1.0f);
	fTexCoord = vTexCoord;
}
