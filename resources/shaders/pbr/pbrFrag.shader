#version 460 core
in vec2 fTexCoord;

out vec4 fColor;

uniform sampler2D uTexDiffuse1;

void main()
{
	fColor = texture(uTexDiffuse1, fTexCoord);
}
