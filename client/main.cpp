#include <iostream>

#include <enet/enet.h>

#include "opengl/window.hpp"
#include "player.hpp"

namespace test
{
	struct packet
	{
		uint16_t type;
	};

	class client
	{
	public:
		client(const std::string& ip = "127.0.0.1", uint16_t port = 3198)
		{
			enet_initialize();
			atexit(enet_deinitialize);

			enet_address_set_host(&address, "127.0.0.1");
			address.port = port;

			host = enet_host_create(NULL, 1, 1, 0, 0);
		}
		~client()
		{
			enet_peer_disconnect(peer, 0);

			while (enet_host_service(host, &event, 3000))
			{
				switch (event.type)
				{
				case ENET_EVENT_TYPE_RECEIVE:
					enet_packet_destroy(event.packet);
					break;
				case ENET_EVENT_TYPE_DISCONNECT:
					std::cout << "disconnected\n";
					break;
				}
			}

			enet_host_destroy(host);
		}

		bool connect()
		{
			peer = enet_host_connect(host, &address, 1, 0);

			if (enet_host_service(host, &event, 5000))
			{
				switch (event.type)
				{
				case ENET_EVENT_TYPE_CONNECT:
					std::cout << "connected to server\n";
					break;
				}
			}
			else
			{
				enet_peer_reset(peer);
				std::cout << "failed to connect\n";
				return false;
			}

			return true;
		}

		void send(const packet& packet)
		{
			enet_peer_send(peer, 0, enet_packet_create(&packet, sizeof(packet), ENET_PACKET_FLAG_RELIABLE));
		}

		void handle()
		{
			while (enet_host_service(host, &event, 0))
			{
				switch (event.type)
				{
				case ENET_EVENT_TYPE_RECEIVE:
					std::cout << "packet received\n";
					break;
				}
			}
		}
	private:
		ENetAddress address;
		ENetHost* host;
		ENetPeer* peer;
		ENetEvent event;
	};
}

int main()
{
	if (auto client = std::make_unique<test::client>(); client->connect())
	{
		// opengl
		auto window = std::make_unique<opengl::window>("ping pong");
		auto renderer = std::make_shared<opengl::renderer>(window->getProjection());
		auto input = std::make_shared<opengl::input>(window->getNative());

		// game
		auto player = std::make_unique<game::player>();

		client->send({ 3 });
		while (window->refresh())
		{
			client->handle();

			player->update(renderer, input);
			renderer->render();
		}
	}
}