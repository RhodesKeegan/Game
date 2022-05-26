#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <GLM/include/vec3.hpp>
#include <iostream>
#include <fstream>

#include "main.h"

const char* triangleSource = "#version 460 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"out vec3 customColor;\n"
"void main() {\n"
"gl_Position = vec4(aPos, 1.0);\n"
"customColor = aColor;\n"
"}";

const char* triangleFrag = "#version 460 core\n"
"out vec4 fragColor;\n"
"in vec3 customColor;\n"
"void main() {\n"
"	fragColor = vec4(customColor, 1.0);\n"
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
	//pos                          //colors
	glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f),
	glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f),
	glm::vec3(0.5f,  0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f),
	glm::vec3(-0.5f, 0.5f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f)
	};

	unsigned int indicies[] = {
		2, 1, 3,
		1, 0, 3
	};

	//Doing the binding stuff here
	unsigned int vboID, vaoID, eboID;

	glGenBuffers(1, &eboID);
	glGenBuffers(1, &vboID);
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticies), verticies, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);

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


	//position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);

	while (!glfwWindowShouldClose(window)) {

		//Sets it a light red or something
		glClearColor(250.0f / 255.0f, 119.0f / 255.0f, 110.0f / 255.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glUseProgram(shaderProgram);

		//float time = glfwGetTime();
		//float greenValue = sin(time) / 2.0f + 0.5f;
		//int vertexLocation = glGetUniformLocation(shaderProgram, "customColor");
		//glUniform4f(vertexLocation, 0.0f, greenValue, 0.0f, 1.0f);


		glBindVertexArray(vaoID);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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