// Copyright 2021 Mustafa Moiz.

#pragma once

#include <ostream>

namespace hypertext
{
	/**
	 * Enumeration of methods supported by the HTTP specification,
	 * as specified by the following sources:
	 * - https://datatracker.ietf.org/doc/html/rfc7231#section-4
	 * - https://datatracker.ietf.org/doc/html/rfc5789#section-2
	 */
	enum class Method
	{
		Connect,
		Delete,
		Get,
		Head,
		Options,
		Patch,
		Post,
		Put,
		Trace
	};

	/**
	 * Converts the method to an HTTP-compliant,
	 * all-uppercase string.
	 */
	std::ostream& operator<<(std::ostream& stream, Method method);
}
