#pragma once

struct GLFWwindow;

enum class keys
{
	S = 83,
	W = 87
};

namespace opengl
{
	class input // todo: buttons enum
	{
	public:
		input(GLFWwindow* window);

		bool isPressed(keys key); // key
	private:
		GLFWwindow* window;
	};
}