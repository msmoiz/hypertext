#include "connection.h"

#include <algorithm>

#include <WinSock2.h>

namespace hypertext
{
	Connection::Connection(std::string hostname, std::uint16_t port)
	{
		// Create socket
		socket_ = socket(AF_INET , SOCK_STREAM , 0 );

		// Use DNS to get destination IP address
		hostent* host_details = gethostbyname(hostname.c_str());
		const auto addr_list = (struct in_addr **) host_details->h_addr_list;
		char ip[100];
		for(int i = 0; addr_list[i] != nullptr; i++) 
		{
			strcpy(ip , inet_ntoa(*addr_list[i]) );
		}

		sockaddr_in server;
		server.sin_addr.s_addr = inet_addr(ip);
		server.sin_family = AF_INET;
		server.sin_port = htons(port);

		// Initiate connection
		connect(socket_, (struct sockaddr *)&server, sizeof(server));
	}

	Connection::~Connection()
	{
		shutdown(socket_, SD_BOTH);
		closesocket(socket_);
	}

	void Connection::send(std::string message)
	{
		::send(socket_, message.c_str(), strlen(message.c_str()), 0);
	}

	std::string Connection::receive()
	{
		char server_reply[4000];
		int recv_size;
		recv_size = ::recv(socket_, server_reply, 4000, 0);
#undef min
		server_reply[std::min(recv_size, 4000 - 1)] = '\0';
		return server_reply;
	}
}
