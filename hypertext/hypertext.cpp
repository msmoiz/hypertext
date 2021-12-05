#include "hypertext.h"

#include <WinSock2.h>

namespace hypertext
{
	void init()
	{
		WSADATA wsa_data;
		WSAStartup(MAKEWORD(2, 2), &wsa_data);
	}

	void shutdown()
	{
		WSACleanup();
	}
}
