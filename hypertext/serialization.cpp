#include "serialization.h"

#include <sstream>

namespace hypertext
{
	std::string parse_request_to_string(const Request& request)
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

	Response parse_response_from_string(std::string raw_response)
	{
		auto response = Response::build();
		
		std::stringstream ss_raw_response{raw_response};
		std::string buffer;

		// Status
		std::getline(ss_raw_response, buffer);
		{
			Version version;
			std::string status_code;
			std::string status_message;
			std::stringstream status_line{buffer};
			status_line >> version >> status_code >> status_message;
			response.version(version)
			        .status_code(StatusCode{std::stoi(status_code)})
			        .status_message(status_message);
		}

		// Headers
		while (ss_raw_response.peek() != '\r')
		{
			std::getline(ss_raw_response, buffer);
			std::stringstream header_line{buffer};

			std::string key, value;
			std::getline(header_line, key, ':');
			header_line.ignore(1); // Space following delimiter ':'
			header_line >> value;
			response.header(key, value);
		}
		ss_raw_response.ignore(2); // "\r\n"

		// Body
		std::string body{std::istreambuf_iterator{ss_raw_response}, {}};
		response.body(body);

		return response;
	}
}
