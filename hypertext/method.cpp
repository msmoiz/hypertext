// Copyright 2021 Mustafa Moiz.

#include "method.h"

#include <unordered_map>

namespace hypertext
{
	std::ostream& operator<<(std::ostream& stream, const Method method)
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

		return stream << string_by_method[method];
	}
}
