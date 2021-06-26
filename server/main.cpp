#include <memory>
#include <iostream>

#include "network.hpp"

int main() // todo: into class
{
	auto server = std::make_unique<network::server>();
	
	std::cout << "listening (default: 127.0.0.1:3198)\n";
	while (true)
		server->handle();
}