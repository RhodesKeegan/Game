#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

static int WIDTH = 1920;
static int HEIGHT = 1080;

void viewPortHandler(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void keyHandler(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		std::cout << "You pressed the escape key buddy" << std::endl;
	}
}

int main(void) {
	glfwInit();

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