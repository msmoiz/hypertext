#include "method.h"

#include <unordered_map>

namespace hypertext
{
	std::string to_spec_compliant_string(const hypertext::Method method)
	{
		static std::unordered_map<Method, std::string> string_by_method
		{
			{Method::Connect, "CONNECT"},
			{Method::Delete, "DELETE"},
			{Method::Get, "GET"},
			{Method::Head, "HEAD"},
			{Method::Options, "OPTIONS"},
			{Method::Patch, "PATCH"},
			{Method::Post, "POST"},
			{Method::Put, "PUT"},
			{Method::Trace, "TRACE"}
		};

		return string_by_method[method];
	}
}
