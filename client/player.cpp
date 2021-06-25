#include "player.hpp"

game::player::player(float speed, const glm::vec2& size, const glm::vec3& color) : speed(speed), rect({ 15.0f, 15.0f }, size, color), lastY(rect.position.y), moved(false)
{

}

void game::player::update(const std::shared_ptr<opengl::renderer>& renderer, const std::shared_ptr<opengl::input>& input)
{
	moved = false;

	// currently hardcoded
	if (input->isPressed(keys::W) && rect.position.y < 580.0f)
		rect.position.y += speed;
	else if (input->isPressed(keys::S) && rect.position.y > 15.0f)
		rect.position.y -= speed;

	renderer->add(rect);

	if (lastY != rect.position.y)
		moved = true;

	lastY = rect.position.y;
}

const opengl::rect& game::player::getRect() const
{
	return rect;
}

bool game::player::hasMoved() const
{
	return moved;
}
