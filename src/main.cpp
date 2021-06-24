#include <memory>

#include "opengl/window.hpp"
#include "opengl/renderer.hpp"

namespace game
{
	class player
	{
	public:
		player(const glm::vec2& size, const glm::vec3& color) : size(size), color(color), position(15.0f, 15.0f)
		{

		}

		void update(const std::shared_ptr<opengl::renderer>& renderer)
		{
			// todo: input (movement)
			renderer->rect(position, size, color);
		}
	private:
		const glm::vec2 size;
		const glm::vec3 color;
		glm::vec2 position;
	};
}

int main()
{
	// opengl
	auto window = std::make_unique<opengl::window>("ping pong");
	auto renderer = std::make_shared<opengl::renderer>(window->getProjection());

	// game
	auto player = std::make_unique<game::player>(glm::vec2(4.0f, 125.0f), glm::vec3(1.0f, 1.0f, 1.0f));

	while (window->refresh())
	{
		player->update(renderer);
		renderer->render();
	}
}