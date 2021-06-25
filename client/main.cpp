#include <iostream>

#include <enet/enet.h>

#include "opengl/window.hpp"
#include "player.hpp"

class client
{
public:
	client()
	{

	}
};

int main()
{
	// opengl
	auto window = std::make_unique<opengl::window>("ping pong");
	auto renderer = std::make_shared<opengl::renderer>(window->getProjection());
	auto input = std::make_shared<opengl::input>(window->getNative());

	// game
	auto player = std::make_unique<game::player>();

	while (window->refresh())
	{
		player->update(renderer, input);
		renderer->render();
	}
}