#pragma once

#include <unordered_map>

#include "method.h"
#include "version.h"

namespace hypertext
{
	struct Request
	{
		Method method;
		std::string uri;
		Version version;
		std::unordered_map<std::string, std::string> headers;
		std::string body;
	};
}
