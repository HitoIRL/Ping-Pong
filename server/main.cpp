#include <iostream>

#include <enet/enet.h>

struct packet
{
	uint16_t type;
};

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

	while (true)
	{
		while (enet_host_service(host, &event, 1000))
		{
			switch (event.type)
			{
			case ENET_EVENT_TYPE_CONNECT:
				std::cout << "client connected\n";
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				std::cout << "client disconnected\n";
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				packet* pa = (packet*)&event.data;

				std::cout << (*pa).type << "\n";

				enet_packet_destroy(event.packet);
				break;
			}
		}
	}

	enet_host_destroy(host);
}