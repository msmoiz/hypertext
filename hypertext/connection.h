#pragma once

#include <string>

namespace hypertext
{
	class Connection
	{
	public:

		Connection(std::string hostname, std::uint16_t port);
		Connection(const Connection& other) = delete;
		Connection operator=(const Connection& other) = delete;
		Connection(Connection&& other) noexcept;
		Connection& operator=(Connection&& other) noexcept;
		~Connection() noexcept;

		void send(std::string message) const;
		std::string receive() const;
		void release();

	private:
		
		std::size_t socket_{0};
		bool should_cleanup_{true};
	};
}
