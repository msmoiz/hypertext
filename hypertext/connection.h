#pragma once

#include <string>

namespace hypertext
{
	class Connection
	{
	public:
		
		~Connection();

		void send(std::string message);
		std::string receive();

	private:

		Connection(std::string hostname, std::uint16_t port);
		
		unsigned long long socket_;
		
		friend class ConnectionManager;
	};
}
