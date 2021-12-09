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
		ConnectionManager(ConnectionManager&& other) noexcept;
		ConnectionManager& operator=(ConnectionManager&& other) noexcept;
		~ConnectionManager() noexcept;

		Connection spawn_connection(std::string hostname, std::uint16_t port);

	private:

		bool should_cleanup_{true};
	};
}
