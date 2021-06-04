#pragma once

#include <string>

#include <glm/vec2.hpp>
#include <glm/mat4x2.hpp>

struct GLFWwindow;

namespace opengl
{
	class window
	{
	public:
		window(const std::string& title, const glm::uvec2& size = { 1280, 720 });
		~window();

		bool refresh();
	private:
		GLFWwindow* glfw; // glfw window
		const glm::mat4x2 projection;
	};
}