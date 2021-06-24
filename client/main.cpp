#include <memory>

#include <iostream>

#include "opengl/window.hpp"
#include "opengl/renderer.hpp"
#include "opengl/input.hpp"

namespace game
{
	class player // todo: change to network player
	{
	public:
		player(float speed = 5.0f, const glm::vec2& size = { 4.0f, 125.0f }, const glm::vec3& color = { 1.0f, 1.0f, 1.0f }) : speed(speed), rect({ 15.0f, 15.0f }, size, color)
		{

		}

		void update(const std::shared_ptr<opengl::renderer>& renderer, const std::shared_ptr<opengl::input>& input)
		{
			if (input->isPressed(keys::W))
				rect.position.y += speed;
			else if (input->isPressed(keys::S))
				rect.position.y -= speed;

			renderer->add(rect);
		}
	private:
		const float speed;
		opengl::rect rect;
	};
}

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