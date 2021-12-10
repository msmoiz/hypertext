#pragma once

#include <iostream>

namespace hypertext
{
	/**
	 * Enumeration of supported HTTP specification versions.
	 */
	enum class Version
	{
		OnePointOh,
		OnePointOne,
		Two,
		Three
	};

	/**
	 * Converts the version to an HTTP-compliant,
	 * prefixed string in the form HTTP/{version},
	 * where version is numeric.
	 */
	std::ostream& operator<<(std::ostream& stream, Version version);

	/**
	 * Parses the version from an HTTP-compliant,
	 * prefixed string in the form HTTP/{version},
	 * where version is numeric.
	 */
	std::istream& operator>>(std::istream& stream, Version& version);
}
