#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/include/vec3.hpp>
#include <iostream>
#include <fstream>

#include "main.h"

static int WIDTH = 1920;
static int HEIGHT = 1080;

static std::string readFile(const char* path);

using namespace std;

int main(int argc, char* argv[]) {
	glfwInit();

	//Setting the window to fullscreen
	glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello World", NULL, NULL);

	if (!window) {
	
		glfwTerminate();

	}
	

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Could not load GLAD" << std::endl;
		EXIT_FAILURE;
	}

	glViewport(0, 0, WIDTH, HEIGHT);


	//Setting up the callback functions
	glfwSetFramebufferSizeCallback(window, viewPortHandler);
	glfwSetKeyCallback(window, keyHandler);


	while (!glfwWindowShouldClose(window)) {

		//Sets it a light red or something
		//glClearColor(250.0f / 255.0f, 119.0f / 255.0f, 110.0f / 255.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	EXIT_SUCCESS;
}

void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		cout << "You pressed the escape key buddy" << endl;
	}
}

void viewPortHandler(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void makeTriangles() {
	glm::vec3 vertices[] = {
		glm::vec3(-0.5f, -0.5f, 0.0f),
		glm::vec3(0.5f, -0.5f, 0.0f),
		glm::vec3(0.0f,  0.5f, 0.0f)
	};


	//Doing the binding stuff here
	unsigned int vboID;

	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	//Making the shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	string sourceCode = readFile("../resources/shaders/vertex/triangle.glsl");


	const GLchar* triangleSource = sourceCode.c_str();
	glShaderSource(vertexShader, 1, &triangleSource, NULL);
	glCompileShader(vertexShader);


}

static string readFile(const char* path) {
	string resultingString;

	ifstream in(path, std::ios::in | std::ios::binary);
	if (in){
		in.seekg(0, std::ios::end);
		resultingString.resize(in.tellg());
		in.seekg(0, std::ios::beg);
		in.read(&resultingString[0], resultingString.size());
		in.close();
	}

	return resultingString;
}