#pragma once

#include "opengl/renderer.hpp"
#include "opengl/input.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace game
{
	class netPlayer
	{
	public:
		netPlayer(const glm::vec2& position, const glm::vec2& size = { 4.0f, 125.0f }, const glm::vec3& color = { 1.0f, 1.0f, 1.0f });

		void render(const std::shared_ptr<opengl::renderer>& renderer);
		
		float getY() const;
		void setY(float y);
	protected:
		opengl::rect rect;
	};

	class player : public netPlayer
	{
	public:
		player(float speed = 10.0f);

		void update(const std::shared_ptr<opengl::input>& input);
		bool hasMoved() const;
	private:
		const float speed;
		float lastY;
		bool moved;
	};
}