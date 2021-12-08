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

		for (const auto& [key, value] : request.headers())
		{
			ss << key << ": " << value << "\r\n";
		}
		
		ss << "\r\n" << request.body();
		
		connection.send(ss.str());
		const auto resp = connection.receive();
		std::stringstream ss_resp{resp};

		auto response = Response::build();
		
		std::string buffer;
		std::getline(ss_resp, buffer);
		{
			std::string status_message;
			std::string status_code;
			std::string version;
			std::stringstream stream{buffer};
			stream >> version >> status_code >> status_message;
			response.version(Version::OnePointOne)
					.status_code(StatusCode{std::stoi(status_code)})
					.status_message(status_message);
		}
		
		std::unordered_map<std::string, std::string> headers;
		while (ss_resp.peek() != '\r')
		{
			std::string key, value;
			std::string buf;
			std::getline(ss_resp, buf);
			std::stringstream ss_r{buf};
			std::getline(ss_r, key, ':');
			ss_r.ignore(1);
			ss_r >> value;
			response.header(key, value);
		}

		ss_resp.ignore(2);

		std::string body{std::istreambuf_iterator{ss_resp}, {}};
		response.body(body);
		
		return response;
	}
}
