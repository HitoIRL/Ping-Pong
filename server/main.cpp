#include <iostream>

#include <enet/enet.h>

enum class packetType
{
	assignId,
	updatePoisition
};

struct packet
{
	packetType type;
	uint16_t id;
	float y;
};

void send(const packet& packet, ENetPeer* peer, ENetHost* host)
{
	auto p = enet_packet_create(&packet, sizeof(packet), ENET_PACKET_FLAG_RELIABLE);
	enet_peer_send(peer, 0, p);
	//enet_host_flush(host);
}

void broadcast(const packet& packet, ENetHost* host)
{
	auto p = enet_packet_create(&packet, sizeof(packet), ENET_PACKET_FLAG_RELIABLE);
	enet_host_broadcast(host, 0, p);
	//enet_host_flush(host);
}

int main() // todo: into class
{
	if (enet_initialize())
	{
		std::cout << "failed to initialize enet\n";
		Sleep(5000);
		return -1;
	}
	atexit(enet_deinitialize);
	ENetAddress address;
	address.host = ENET_HOST_ANY;
	address.port = 3198;
	auto host = enet_host_create(&address, 2, 1, 0, 0);
	if (!host)
	{
		std::cout << "failed to create enet server\n";
		Sleep(5000);
		return -1;
	}
	ENetEvent event;

	std::cout << "listening...\n";

	uint16_t id = 0;

	while (true)
	{
		while (enet_host_service(host, &event, 1000))
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				std::cout << "client connected\n";
				send({ packetType::assignId, id }, event.peer, host);
				id++;
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				std::cout << "client disconnected\n";
				id--;
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				auto p = *reinterpret_cast<packet*>(event.packet->data);

				switch (p.type)
				{
				case packetType::updatePoisition:
					broadcast(p, host);
					break;
				}

				enet_packet_destroy(event.packet);
				break;
			}
		}
	}

	enet_host_destroy(host);
}