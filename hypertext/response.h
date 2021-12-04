#pragma once

#include <unordered_map>

#include "status_code.h"
#include "version.h"

namespace hypertext
{
	struct Response
	{
		Version version;
		StatusCode status_code;
		std::string status_message;
		std::unordered_map<std::string, std::string> headers;
		std::string body;
	};
}
