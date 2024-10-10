#version 460 core
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec3 vColor;

out vec3 color;

uniform mat4 uVP;

void main()
{
	gl_Position = uVP * vec4(vPosition, 1.0f);
	color = vColor;
}
