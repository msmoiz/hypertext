#include "version.h"

#include <unordered_map>
#include <string>

namespace hypertext
{
	std::ostream& operator<<(std::ostream& stream, const Version version)
	{
		static std::unordered_map<Version, std::string> string_by_version
		{
			{Version::OnePointOh, "1.0"},
			{Version::OnePointOne, "1.1"},
			{Version::Two, "2"},
			{Version::Three, "3"},
		};

		return stream << "HTTP/" << string_by_version[version];
	}

	std::istream& operator>>(std::istream& stream, Version& version)
	{
		static std::unordered_map<std::string, Version> version_by_string
		{
			{"1.0", Version::OnePointOh},
			{"1.1", Version::OnePointOne},
			{"2", Version::Two},
			{"3", Version::Three},
		};

		std::string buffer;
		stream >> buffer;
		version = version_by_string[buffer.substr(5)];

		return stream;
	}
}
