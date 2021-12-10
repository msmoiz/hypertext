#include "client.h"

#include <sstream>

#include "connection.h"

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

	std::string Client::parse_request_to_string(const Request& request) const
	{
		static const char space = ' ';
		static const std::string http_newline = "\r\n";
		static const char parameter_lead = '?';
		static const char parameter_key_val_separator = '=';
		static const char parameter_delimiter = '&';
		static const std::string header_key_val_separator = ": ";
		
		std::stringstream raw_request;

		// Method
		raw_request	<< request.method << space;

		// Resource
		raw_request << request.resource();
		if (!request.parameters().empty())
		{
			raw_request << parameter_lead;
			for (auto it = request.parameters().begin(); it != request.parameters().end(); ++it)
			{
				raw_request << it->first << parameter_key_val_separator << it->second;
				if (it != --request.parameters().end())
				{
					raw_request << parameter_delimiter;
				}
			}
		}
		raw_request << space;

		// Version
		raw_request << request.version << http_newline;

		// Headers
		for (const auto& [key, value] : request.headers())
		{
			raw_request << key << header_key_val_separator << value << http_newline;
		}
		raw_request << http_newline;

		// Body
		raw_request << request.body();

		return raw_request.str();
	}

	Response Client::parse_response_from_string(std::string raw_response) const
	{
		std::stringstream ss_resp{raw_response};

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
