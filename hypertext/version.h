#pragma once

#include <ostream>

namespace hypertext
{
	/**
	 * Enumeration of supported HTTP specification versions.
	 */
	enum class Version
	{
		OnePointOne
	};

	/**
	 * Converts the version to an HTTP-compliant,
	 * prefixed string in the form HTTP/{version},
	 * where version is numeric.
	 */
	std::ostream& operator<<(std::ostream& stream, Version version);
}
