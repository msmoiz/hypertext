#pragma once

#include <exception>

namespace hypertext
{
	/**
	 * Base class for exceptions thrown by the hypertext
	 * library.
	 */
	class Exception final : public std::exception
	{
	public:
		
		explicit Exception(const std::string& what_arg) : std::exception{what_arg.c_str()} { }
	};
}
