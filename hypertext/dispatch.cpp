#include "dispatch.h"

#include <WinSock2.h>

#include "connection.h"

namespace hypertext
{
	Response dispatch(Request request)
	{
		Connection connection{request.uri, 3000};
		
		connection.send(request.body);
		const auto resp = connection.receive();
		
		return Response
		{
			Version::OnePointOne,
			StatusCode::Okay,
			resp
		};
	}
}
