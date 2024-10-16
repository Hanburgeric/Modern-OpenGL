#version 460 core
in vec3 fPosition;
in vec3 fNormal;

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
uniform vec3 uViewPosition;

void main()
{
	vec3 normal = normalize(fNormal);
	vec3 lightDirection = normalize(uLightPosition - fPosition);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	vec3 viewDirection = normalize(uViewPosition - fPosition);

	vec3 ambient = uLightColor * uMaterial.ambient;
	vec3 diffuse = uLightColor * uMaterial.diffuse * max(dot(normal, lightDirection), 0.0f);
	vec3 specular = uLightColor * uMaterial.specular * pow(max(dot(viewDirection, reflectionDirection), 0.0f), uMaterial.shininess);

	fColor = vec4((ambient + diffuse + specular), 1.0f);
}
