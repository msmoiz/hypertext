#include "connection_manager.h"

#include <WinSock2.h>

namespace hypertext
{
	ConnectionManager::ConnectionManager()
	{
		WSADATA wsa_data_throwaway;
		WSAStartup(MAKEWORD(2, 2), &wsa_data_throwaway);
	}

	ConnectionManager::~ConnectionManager()
	{
		WSACleanup();
	}

	Connection ConnectionManager::spawn_connection(std::string hostname, const std::uint16_t port)
	{
		return {std::move(hostname), port};
	}
}
