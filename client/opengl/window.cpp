#include "window.hpp"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>

opengl::window::window(const std::string& title, const glm::uvec2& size) : projection(glm::ortho(0.0f, static_cast<float>(size.x), 0.0f, static_cast<float>(size.y))), size(size)
{
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfw = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(glfw);
	glfwSwapInterval(1); // vsync

	gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)); // init glad

	glViewport(0, 0, size.x, size.y);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
}

opengl::window::~window()
{
	glfwTerminate();
}

bool opengl::window::refresh()
{
	glfwSwapBuffers(glfw);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwPollEvents();

	return !glfwWindowShouldClose(glfw);
}

const glm::mat4& opengl::window::getProjection() const
{
	return projection;
}

GLFWwindow* opengl::window::getNative() const
{
	return glfw;
}

const glm::uvec2& opengl::window::getSize() const
{
	return size;
}
