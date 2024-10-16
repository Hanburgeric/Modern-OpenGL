#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Camera.h"
#include "InputManager.h"
#include "Model.h"
#include "Shader.h"
#include "Skybox.h"

//Global variables
unsigned int SCREEN_WIDTH = 1280;
unsigned int SCREEN_HEIGHT = 720;

//GLFW callback functions
void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

//Input class
InputManager inputManager;

int main()
{
	//Initializes GLFW
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creates a window
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Modern OpenGL", nullptr, nullptr);
	if (!window)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Initializes window
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, cursor_pos_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, key_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

	//Initializes GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		glfwTerminate();
		return -1;
	}

	//Enables GL capabilities
	glEnable(GL_DEPTH_TEST);

	//Initializes ImGui
	ImGuiContext* ctx = ImGui::CreateContext();
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init();
	ImGui_ImplGlfw_InitForOpenGL(window, true);

	//Initializes camera
	Camera debugCamera(glm::vec3(15.0f, 10.0f, 30.0f), glm::vec3(0.0f, 1.0f, 0.0f), 240.0f, 350.0f, 45.0f, 0.1f, 500.0f);

	//Axis
	float vertices[] = {
		//Positions					//Colors
		-50.0f,	  0.0f,	  0.0f,		1.0f, 0.0f, 0.0f,
		 50.0f,	  0.0f,	  0.0f,		1.0f, 0.0f, 0.0f,
		  0.0f,	-50.0f,	  0.0f,		0.0f, 1.0f, 0.0f,
		  0.0f,	 50.0f,	  0.0f,		0.0f, 1.0f, 0.0f,
		  0.0f,	  0.0f, -50.0f,		0.0f, 0.0f, 1.0f,
		  0.0f,	  0.0f,	 50.0f,		0.0f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0, 1,
		2, 3,
		4, 5
	};

	int numVertices = (sizeof(vertices) / sizeof(float)) / (sizeof(indices) / sizeof(unsigned int));

	Shader axisShader;
	axisShader.pushShader(GL_VERTEX_SHADER, "../resources/shaders/axis/axisVert.shader");
	axisShader.pushShader(GL_FRAGMENT_SHADER, "../resources/shaders/axis/axisFrag.shader");
	axisShader.createProgram();

	unsigned int axisVAO;
	glGenVertexArrays(1, &axisVAO);
	glBindVertexArray(axisVAO);

	unsigned int axisVBO;
	glGenBuffers(1, &axisVBO);
	glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	unsigned int axisIBO;
	glGenBuffers(1, &axisIBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, axisIBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, numVertices * sizeof(float), (const void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, numVertices * sizeof(float), (const void*)(3 * sizeof(float)));

	//Imported models
	Shader lightbulbShader;
	lightbulbShader.pushShader(GL_VERTEX_SHADER, "../resources/shaders/lightbulb/lightbulbVert.shader");
	lightbulbShader.pushShader(GL_FRAGMENT_SHADER, "../resources/shaders/lightbulb/lightbulbFrag.shader");
	lightbulbShader.createProgram();
	Model lightbulb("../resources/models/lightbulb/lightbulb.obj", true);
	glm::vec3 lightbulbPosition(0.0f, 0.0f, 0.0f);
	glm::vec3 lightbulbColor(1.0f, 1.0f, 1.0f);

	Shader myNameShader;
	myNameShader.pushShader(GL_VERTEX_SHADER, "../resources/shaders/myName/myNameVert.shader");
	myNameShader.pushShader(GL_FRAGMENT_SHADER, "../resources/shaders/myName/myNameFrag.shader");
	myNameShader.createProgram();
	Model myName("../resources/models/myName/myName.obj", true);
	bool isPhysicsOn = false;
	glm::vec3 myNameAcceleration(0.0f, -9.807f, 0.0f);
	glm::vec3 myNameVelocity(0.0f, 0.0f, 0.0f);
	glm::vec3 myNamePosition(0.0f, 0.0f, 0.0f);
	glm::vec3 myNameAmbient(0.24725f, 0.1995f, 0.0745f);
	glm::vec3 myNameDiffuse(0.75164f, 0.60648f, 0.22648f);
	glm::vec3 myNameSpecular(0.628281f, 0.555802f, 0.366065f);
	float myNameShininess(0.4f * 128.0f);

	Shader pbrShader;
	pbrShader.pushShader(GL_VERTEX_SHADER, "../resources/shaders/pbr/pbrVert.shader");
	pbrShader.pushShader(GL_FRAGMENT_SHADER, "../resources/shaders/pbr/pbrFrag.shader");
	pbrShader.createProgram();
	Model divergenceMeter("../resources/models/divergenceMeter/scene.gltf", true);
	glm::vec3 pbrPosition(0.0f, 0.0f, -10.0f);

	//Skybox
	Shader skyboxShader;
	skyboxShader.pushShader(GL_VERTEX_SHADER, "../resources/shaders/skybox/skyboxVert.shader");
	skyboxShader.pushShader(GL_FRAGMENT_SHADER, "../resources/shaders/skybox/skyboxFrag.shader");
	skyboxShader.createProgram();
	Skybox skybox("../resources/cubemaps/skybox/", ".jpg");
	bool isSkyboxOn = true;

	//Time step variables
	double currTime = glfwGetTime();
	double prevTime = 0.0f;
	float deltaTime = 0.0f;

	//Main loop
	while (!glfwWindowShouldClose(window))
	{
		currTime = glfwGetTime();
		deltaTime = currTime - prevTime;
		prevTime = currTime;

		//Input handling
		debugCamera.handleInput(inputManager);

		//Updating
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		inputManager.update();
		debugCamera.update();

		if (isPhysicsOn)
		{
			myNameVelocity += myNameAcceleration * deltaTime;
			myNamePosition += myNameVelocity * deltaTime;
		}

		ImGui::Begin("Performance Data");
		ImGui::Text("%0.1f FPS", ImGui::GetIO().Framerate);
		ImGui::End();

		ImGui::Begin("Physics");
		ImGui::Checkbox("On/Off", &isPhysicsOn);
		if (ImGui::Button("Reset"))
		{
			myNameVelocity = glm::vec3(0.0f);
			myNamePosition = glm::vec3(0.0f);
		}
		ImGui::End();

		ImGui::Begin("Light Settings");
		ImGui::SliderFloat3("Position", &lightbulbPosition[0], -50.0f, 50.0f);
		ImGui::ColorEdit3("Color", &lightbulbColor[0]);
		ImGui::End();

		ImGui::Begin("Material Settings");
		ImGui::SliderFloat3("Ambient", &myNameAmbient[0], 0.0f, 1.0f);
		ImGui::SliderFloat3("Diffuse", &myNameDiffuse[0], 0.0f, 1.0f);
		ImGui::SliderFloat3("Specular", &myNameSpecular[0], 0.0f, 1.0f);
		ImGui::SliderFloat("Shininess", &myNameShininess, 0.001f, 256.0f);
		ImGui::End();

		ImGui::Begin("Skybox");
		ImGui::Checkbox("On/Off", &isSkyboxOn);
		ImGui::End();

		//Rendering
		ImGui::Render();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glm::mat4 projection = debugCamera.getProjectionMatrix((float)SCREEN_WIDTH / (float)SCREEN_HEIGHT);
		glm::mat4 view = debugCamera.getViewMatrix();

		//Axis
		axisShader.bind();
		axisShader.setUniformMatrix4fv("uVP", projection * view);
		glBindVertexArray(axisVAO);
		glDrawElements(GL_LINES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, (const void*)0);

		//Imported models
		lightbulbShader.bind();
		glm::mat4 lightbulbModel = glm::translate(glm::scale(glm::mat4(1.0f), glm::vec3(0.25f)), 4.0f * lightbulbPosition);
		lightbulbShader.setUniformMatrix4fv("uMVP", projection * view * lightbulbModel);
		lightbulbShader.setUniform3fv("uColor", lightbulbColor);
		lightbulb.render(lightbulbShader);

		myNameShader.bind();
		glm::mat4 myNameModel = glm::translate(glm::mat4(1.0f), myNamePosition);
		myNameShader.setUniformMatrix4fv("uProjection", projection);
		myNameShader.setUniformMatrix4fv("uView", view);
		myNameShader.setUniformMatrix4fv("uModel", myNameModel);
		myNameShader.setUniform3fv("uMaterial.ambient", myNameAmbient);
		myNameShader.setUniform3fv("uMaterial.diffuse", myNameDiffuse);
		myNameShader.setUniform3fv("uMaterial.specular", myNameSpecular);
		myNameShader.setUniform1f("uMaterial.shininess", myNameShininess);
		myNameShader.setUniform3fv("uLightPosition", lightbulbPosition);
		myNameShader.setUniform3fv("uLightColor", lightbulbColor);
		myNameShader.setUniform3fv("uViewPosition", debugCamera.getPosition());
		myName.render(myNameShader);

		pbrShader.bind();
		glm::mat4 divergenceMeterModel = glm::translate(glm::mat4(1.0f), pbrPosition);
		pbrShader.setUniformMatrix4fv("uMVP", projection * view * divergenceMeterModel);
		divergenceMeter.render(pbrShader);

		//Skybox
		if (isSkyboxOn)
		{
			skyboxShader.bind();
			skyboxShader.setUniformMatrix4fv("uVP", projection * glm::mat4(glm::mat3(view)));
			skybox.render(skyboxShader);
		}

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		glfwSwapBuffers(window);

		//Event polling
		glfwPollEvents();
	}

	//Terminates ImGui
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext(ctx);

	//Terminates GLFW
	glfwTerminate();

	return 0;
}

void cursor_pos_callback(GLFWwindow* window, double xpos, double ypos)
{
	inputManager.cursorPosEvent(xpos, ypos);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	glViewport(0, 0, width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	inputManager.keyEvent(key, action);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	inputManager.mouseButtonEvent(button, action);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	inputManager.scrollEvent(xoffset, yoffset);
}
