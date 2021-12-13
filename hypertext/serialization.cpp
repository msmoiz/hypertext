// Copyright 2021 Mustafa Moiz.

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
}
