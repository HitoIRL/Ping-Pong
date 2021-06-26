#pragma once

#include <string>
#include <functional>

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

	class client
	{
	public:
		client(const std::string& ip, uint16_t port);
		~client();

		bool connect();
		void handle(std::function<void(uint16_t id, const packet& packet)> callback);
		void send(const packet& packet) const;

		uint16_t getId() const;
	private:
		ENetAddress address;
		ENetHost* host;
		ENetPeer* peer;
		ENetEvent event;
		uint16_t id;
	};
}