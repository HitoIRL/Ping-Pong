#include "player.hpp"

game::netPlayer::netPlayer(const glm::vec2& position, const glm::vec2& size, const glm::vec3& color) : rect(position, size, color)
{

}

void game::netPlayer::render(const std::shared_ptr<opengl::renderer>& renderer)
{
	renderer->add(rect);
}

float game::netPlayer::getY() const
{
	return rect.position.y;
}

void game::netPlayer::setY(float y)
{
	rect.position.y = y;
}

game::player::player(float speed) : netPlayer({ 15.0f, 15.0f }), speed(speed), lastY(rect.position.y), moved(false)
{

}

void game::player::update(const std::shared_ptr<opengl::input>& input)
{
	moved = false;

	// currently hardcoded
	if (input->isPressed(keys::W) && rect.position.y < 580.0f)
		rect.position.y += speed;
	else if (input->isPressed(keys::S) && rect.position.y > 15.0f)
		rect.position.y -= speed;

	if (lastY != rect.position.y)
		moved = true;

	lastY = rect.position.y;
}

bool game::player::hasMoved() const
{
	return moved;
}