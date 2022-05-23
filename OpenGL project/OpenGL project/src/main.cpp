#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

static int WIDTH = 800;
static int HEIGHT = 600;

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
}