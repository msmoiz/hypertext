#include "version.h"

#include <unordered_map>

namespace hypertext
{
	std::string to_spec_compliant_string(const Version version)
	{
		static std::unordered_map<Version, std::string> string_by_version
		{
			{Version::OnePointOne, "1.1"},
		};

		return "HTTP/" + string_by_version[version];
	}
}
