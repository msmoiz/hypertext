#pragma once

#include "request.h"
#include "response.h"

namespace hypertext
{
	std::string parse_request_to_string(const Request& request);
	Response parse_response_from_string(std::string raw_response);
}
