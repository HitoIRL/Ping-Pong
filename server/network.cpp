#include "network.hpp"

#include <iostream>

network::server::server(const std::string& ip, uint16_t port) : freeId(0)
{
	enet_initialize();
	atexit(enet_deinitialize);

	address.host = ENET_HOST_ANY;
	address.port = 3198;

	host = enet_host_create(&address, 2, 1, 0, 0);
}

network::server::~server()
{
	enet_host_destroy(host);
}

void network::server::handle()
{
	while (enet_host_service(host, &event, 1000))
	{
		switch (event.type)
		{
		case ENET_EVENT_TYPE_CONNECT:
			std::cout << "client connected\n";
			send({ packetType::assignId, freeId }, event.peer);
			freeId++;
			break;
		case ENET_EVENT_TYPE_DISCONNECT:
			std::cout << "client disconnected\n";
			freeId--;
			break;
		case ENET_EVENT_TYPE_RECEIVE:
			auto p = *reinterpret_cast<packet*>(event.packet->data);

			switch (p.type)
			{
			case packetType::updatePosition:
				broadcast(p);
				break;
			}

			enet_packet_destroy(event.packet);
			break;
		}
	}
}

void network::server::send(const packet& packet, ENetPeer* peer) const
{
	auto p = enet_packet_create(&packet, sizeof(packet), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, p);
}

void network::server::broadcast(const packet& packet) const
{
	auto p = enet_packet_create(&packet, sizeof(packet), ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(host, 0, p);
}
