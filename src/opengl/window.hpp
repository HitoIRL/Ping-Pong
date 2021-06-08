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
		const glm::mat4& getProjection() const;
	private:
		GLFWwindow* glfw; // glfw window
		const glm::mat4 projection;
	};
}