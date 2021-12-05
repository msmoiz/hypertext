#pragma once

#include <string>

namespace hypertext
{
	class Connection
	{
	public:
		
		Connection(std::string hostname, std::uint16_t port);
		~Connection();

		void send(std::string message);
		std::string receive();

	private:

		unsigned long long socket_;
	};
}
