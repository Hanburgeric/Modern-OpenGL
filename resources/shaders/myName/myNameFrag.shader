#version 460 core
in vec3 fPosition;
in vec3 normal;

out vec4 fColor;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};

uniform Material uMaterial;
uniform vec3 uLightPosition;
uniform vec3 uLightColor;

void main()
{
	vec3 fNormal = normalize(normal);
	vec3 lightDirection = normalize(uLightPosition - fPosition);
	vec3 reflectionDirection = reflect(-lightDirection, fNormal);

	vec3 ambient = uLightColor * uMaterial.ambient;
	vec3 diffuse = uLightColor * uMaterial.diffuse * max(dot(fNormal, lightDirection), 0.0f);
	vec3 specular = uLightColor * uMaterial.specular * pow(max(dot(normalize(-fPosition), reflectionDirection), 0.0f), uMaterial.shininess);

	fColor = vec4((ambient + diffuse + specular) * vec3(0.5f, 0.5f, 0.5f), 1.0f);
}
