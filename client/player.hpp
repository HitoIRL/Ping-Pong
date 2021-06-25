#pragma once

#include "opengl/renderer.hpp"
#include "opengl/input.hpp"

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

namespace game
{
	class player
	{
	public:
		player(float speed = 5.0f, const glm::vec2& size = { 4.0f, 125.0f }, const glm::vec3& color = { 1.0f, 1.0f, 1.0f });

		void update(const std::shared_ptr<opengl::renderer>& renderer, const std::shared_ptr<opengl::input>& input);
		const opengl::rect& getRect() const;
		bool hasMoved() const;
	private:
		const float speed;
		opengl::rect rect;
		float lastY;
		bool moved;
	};
}