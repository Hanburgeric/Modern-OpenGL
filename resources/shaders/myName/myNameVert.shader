#version 460 core
layout(location = 0) in vec3 vPosition;
layout(location = 1) in vec2 vTexCoord;
layout(location = 2) in vec3 vNormal;
layout(location = 3) in vec3 vTangent;
layout(location = 4) in vec3 vBitangent;

out vec3 fPosition;
out vec3 normal;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(vPosition, 1.0f);
	fPosition = vec3(uView * uModel * vec4(vPosition, 1.0f));
	normal = mat3(transpose(inverse(uView * uModel))) * vNormal;
}
