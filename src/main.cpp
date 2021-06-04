#include <memory>

#include "opengl/window.hpp"

int main()
{
	auto window = std::make_unique<opengl::window>("ping pong");

	while (window->refresh()) 
	{

	}
}