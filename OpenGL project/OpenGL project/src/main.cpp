#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/include/vec3.hpp>
#include <iostream>
#include <fstream>

#include "main.h"

const char* triangleSource = "#version 460 core\n"
"layout(location = 0) in vec3 aPos;\n"
"void main() {\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0f);\n"
"}";

const char* triangleFrag = "#version 460 core\n"
"out vec4 fragColor;\n"
"void main() {\n"
"	fragColor = vec4(0.9f, 0.0f, 0.0f, 0.0f);\n"
"}";
static int WIDTH = 1920;
static int HEIGHT = 1080;

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

	glm::vec3 verticies[] = {
	glm::vec3(-0.5f, -0.5f, -0.3f),
	glm::vec3(0.5f, -0.5f, -0.2f),
	glm::vec3(0.0f,  0.5f, -0.9f)
	};



	//Doing the binding stuff here
	unsigned int vboID;
	unsigned int vaoID;

	glGenBuffers(1, &vboID);
	glGenVertexArrays(1, &vaoID);

	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	//Making the shader

	//Vertex Shader first
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	//string sourceCode = readFile("..\\resources\\shaders\\vertex\\triangle.glsl");
	//const GLchar* triangleSource = sourceCode.c_str();
	glShaderSource(vertexShader, 1, &triangleSource, NULL);
	glCompileShader(vertexShader);
	int didCompileSuccessfully;
	char infolog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &didCompileSuccessfully);
	if (!didCompileSuccessfully) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		cout << "Vertex shader did not compile successfully. See error log\n" << infolog << endl;
	}

	//Fragment Shader Next
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &triangleFrag, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &didCompileSuccessfully);
	if (!didCompileSuccessfully) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infolog);
		cout << "Fragment shader did not compile successfully. See error log\n" << infolog << endl;
	}

	//Linking them together...
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);


	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &didCompileSuccessfully);

	if (!didCompileSuccessfully) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infolog);
		cout << "Program did not compile successfully, see error log" << infolog << endl;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {

		//Sets it a light red or something
		glClearColor(250.0f / 255.0f, 119.0f / 255.0f, 110.0f / 255.0f, 1.0f);

		glClear(GL_COLOR_BUFFER_BIT);


		glUseProgram(shaderProgram);
		glBindVertexArray(vaoID);
		glDrawArrays(GL_TRIANGLES, 0, 3);

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

//static string readFile(const char* path) {
//	string resultingString;
//
//	ifstream in(path, ios::in | ios::binary);
//	if (in){
//		in.seekg(0, ios::end);
//		resultingString.resize(in.tellg());
//		in.seekg(0, ios::beg);
//		in.read(&resultingString[0], resultingString.size());
//		in.close();
//	}
//
//	return resultingString;
//}