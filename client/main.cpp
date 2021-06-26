#include <iostream>

#include "network.hpp"
#include "opengl/window.hpp"
#include "player.hpp"

int main()
{
	std::string ip;
	std::cout << "ip (default 127.0.0.1): ";
	getline(std::cin, ip);
	if (ip.empty())
		ip = "127.0.0.1";

	std::string port;
	std::cout << "port (default 3198): ";
	getline(std::cin, port);
	if (port.empty())
		port = "3198";

	std::cout << "trying to connect... (" << ip << ":" << port << ")\n";

	if (auto client = std::make_unique<network::client>(ip, stoi(port)); client->connect())
	{
		// opengl
		auto window = std::make_unique<opengl::window>("ping pong");
		auto renderer = std::make_shared<opengl::renderer>(window->getProjection());
		auto input = std::make_shared<opengl::input>(window->getNative());

		// game
		auto player = std::make_unique<game::player>();
		auto opponent = std::make_unique<game::netPlayer>(glm::vec2(window->getSize().x - 30.0f, 30.0f));

		while (window->refresh())
		{
			client->handle([&](uint16_t id, const network::packet& packet)
			{
				switch (packet.type)
				{
					case network::packetType::updatePosition:
						if (packet.id != id)
							opponent->setY(packet.y);
						break;
				}
			});

			if (player->hasMoved())
				client->send({ network::packetType::updatePosition, client->getId(), player->getY() });

			player->update(input);
			player->render(renderer);
			opponent->render(renderer);
			renderer->render();
		}
	}
}