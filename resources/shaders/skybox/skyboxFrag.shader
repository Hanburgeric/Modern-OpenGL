#version 460 core
in vec3 texCoord;

out vec4 fColor;

uniform samplerCube uSkybox;

void main()
{
	fColor = texture(uSkybox, texCoord);
}
