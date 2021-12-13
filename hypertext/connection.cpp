// Copyright 2021 Mustafa Moiz.

#include "connection.h"

#include <optional>

#include <WinSock2.h>
#include <WS2tcpip.h>

#include "exceptions.h"

namespace hypertext
{
	Connection::Connection(std::string hostname, const std::uint16_t port)
	{
		WSADATA wsa_data_throwaway;
		if (const int err{WSAStartup(MAKEWORD(2, 2), &wsa_data_throwaway)}; err)
		{
			throw Exception{"Failed to initialize Windows socket subsystem with error code (" + std::to_string(err) + ")"};
		}

		addrinfo hints{};
		hints.ai_family = AF_INET; // IPv4
		hints.ai_socktype = SOCK_STREAM; // TCP
		hints.ai_protocol = IPPROTO_TCP; // TCP
		addrinfo* addresses{};
		if (const int err = getaddrinfo(hostname.c_str(), std::to_string(port).c_str(), &hints, &addresses); err)
		{
			throw Exception{"Failed to obtain host IP address with error code (" + std::to_string(WSAGetLastError()) + ")"};
		}

		if (socket_ = socket(hints.ai_family, hints.ai_socktype, hints.ai_protocol); socket_ == INVALID_SOCKET)
		{
			throw Exception{"Failed to initialize socket with error code (" + std::to_string(WSAGetLastError()) + ")"};
		}
		
		if (const int err = connect(socket_, addresses[0].ai_addr, (int)addresses[0].ai_addrlen); err)
		{
			throw Exception{"Failed to establish connection with error code (" + std::to_string(WSAGetLastError()) + ")"};
		}

		freeaddrinfo(addresses);
	}

	Connection::Connection(Connection&& other) noexcept
	{
		other.should_cleanup_ = false;
	}

	Connection& Connection::operator=(Connection&& other) noexcept
	{
		other.should_cleanup_ = false;
		return *this;
	}

	Connection::~Connection() noexcept
	{
		try { release(); } catch (...) { /* swallowed, not safe to throw from dtor */ }
	}

	void Connection::send(std::string message) const
	{
		::send(socket_, message.c_str(), (int)message.length(), 0);
	}

	std::string Connection::receive() const
	{
		constexpr int buf_size{4000};
		char buffer[buf_size];
		int last_received{0};

		last_received = ::recv(socket_, buffer, buf_size - 1, 0);
		if (last_received == 0)
		{
			throw Exception{"Connection closed by server."};
		}
		
		buffer[last_received] = '\0';
		return buffer;
	}

	void Connection::release()
	{
		if (should_cleanup_)
		{
			should_cleanup_ = false;
			shutdown(socket_, SD_BOTH);
			closesocket(socket_);
			WSACleanup();
		}
	}
}
