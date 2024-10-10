#version 460 core
layout(location = 0) in vec3 vPosition;

out vec3 texCoord;

uniform mat4 uVP;

void main()
{
	gl_Position = (uVP * vec4(vPosition, 1.0f)).xyww;
	texCoord = vPosition;
}
