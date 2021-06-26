#pragma once

#include <string>

#include <enet/enet.h>

namespace network
{
	enum class packetType
	{
		assignId,
		updatePosition
	};

	struct packet
	{
		packetType type;
		uint16_t id;
		float y;
	};

	class server
	{
	public:
		server(const std::string& ip = "127.0.0.1", uint16_t port = 3198);
		~server();

		void handle();
	private:
		void send(const packet& packet, ENetPeer* peer) const;
		void broadcast(const packet& packet) const;

		ENetAddress address;
		ENetHost* host;
		ENetEvent event;
		uint16_t freeId;
	};
}