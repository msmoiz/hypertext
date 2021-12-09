#include "connection_manager.h"

#include <WinSock2.h>

#include "exceptions.h"

namespace hypertext
{
	ConnectionManager::ConnectionManager()
	{
		WSADATA wsa_data_throwaway;
		if (const auto err{WSAStartup(MAKEWORD(2, 2), &wsa_data_throwaway)}; err)
		{
			throw Exception{"Failed to initialize Windows socket subsystem with error code (" + std::to_string(err) + ")"};
		}
	}

	ConnectionManager::~ConnectionManager() noexcept
	{
		WSACleanup();
	}

	Connection ConnectionManager::spawn_connection(std::string hostname, const std::uint16_t port)
	{
		return {std::move(hostname), port};
	}
}
