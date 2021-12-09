#include "version.h"

#include <unordered_map>

namespace hypertext
{
	std::ostream& operator<<(std::ostream& stream, const Version version)
	{
		static std::unordered_map<Version, std::string> string_by_version
		{
			{Version::OnePointOne, "1.1"},
		};

		return stream << "HTTP/" << string_by_version[version];
	}
}
