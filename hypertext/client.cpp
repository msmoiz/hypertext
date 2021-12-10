#include "client.h"

#include "connection.h"
#include "serialization.h"

namespace hypertext
{
	Response Client::dispatch(const Request request)
	{
		Connection connection{request.host, request.port};

		auto raw_request = parse_request_to_string(request);
		connection.send(std::move(raw_request));
		auto raw_response = connection.receive();		

		connection.release();

		return parse_response_from_string(std::move(raw_response));
	}
}
