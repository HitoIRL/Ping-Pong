#include <memory>

#include "opengl/window.hpp"
#include "opengl/renderer.hpp"

int main()
{
	auto window = std::make_unique<opengl::window>("ping pong");
	auto renderer = std::make_unique<opengl::renderer>(window->getProjection());

	while (window->refresh())
	{
		renderer->rect({ 20.0f, 20.0f }, { 16.0f, 16.0f }, { 1.0f, 1.0f, 1.0f });
		renderer->render();
	}
}