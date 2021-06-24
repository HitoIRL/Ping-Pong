#include "input.hpp"

#include <GLFW/glfw3.h>

opengl::input::input(GLFWwindow* window) : window(window)
{

}

bool opengl::input::isPressed(keys key)
{
	return glfwGetKey(window, (int)key) == GLFW_PRESS;
}