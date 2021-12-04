#pragma once

#include <string>

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
	std::string to_spec_compliant_string(Version version);
}
