#include "client.h"

#include <sstream>

#include "connection.h"

namespace hypertext
{
	Response Client::dispatch(const Request request)
	{
		auto connection = connection_manager_.spawn_connection(request.host, request.port);

		std::stringstream ss;
		ss	<< to_spec_compliant_string(Method::Get) << " "
			<< request.resource();

		if (!request.parameters().empty())
		{
			ss << '?';
			for (auto it = request.parameters().begin(); it != request.parameters().end(); ++it)
			{
				ss << it->first << "=" << it->second;
				if (it != --request.parameters().end())
				{
					ss << "&";
				}
			}
		}

		ss << " " << to_spec_compliant_string(request.version) << "\r\n";

		for (const auto& header : request.headers())
		{
			ss << header.first << ": " << header.second << "\r\n";
		}
		
		ss << "\r\n" << request.body();
		
		connection.send(ss.str());
		const auto resp = connection.receive();
		
		return Response::build()
			.body(resp);
	}
}
