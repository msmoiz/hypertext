#pragma once

#include "connection.h"

namespace hypertext
{
	/**
	 * Interface for managing TCP connections.
	 * Uses socket APIs provided by operating system.
	 */
	class ConnectionManager
	{
	public:
		
		ConnectionManager();
		ConnectionManager(const ConnectionManager& other) = delete;
		ConnectionManager& operator=(const ConnectionManager& other) = delete;
		ConnectionManager(ConnectionManager&& other) = default;
		ConnectionManager& operator=(ConnectionManager&& other) = default;
		~ConnectionManager() noexcept;

		Connection spawn_connection(std::string hostname, std::uint16_t port);
	};
}
