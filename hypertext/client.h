#pragma once

#include "connection_manager.h"
#include "request.h"
#include "response.h"

namespace hypertext
{
	/**
	 * A client for sending HTTP requests.
	 */
	class Client
	{
	public:
		
		Response dispatch(Request request);

	private:

		std::string parse_request_to_string(const Request& request) const;
		Response parse_response_from_string(std::string raw_response) const;

		ConnectionManager connection_manager_;
	};
}
