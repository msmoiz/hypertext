#include <sstream>

#include "version.h"

#include <catch2/catch.hpp>

using namespace hypertext;

TEST_CASE("HTTP version stringification method should return spec-compliant string")
{
	std::stringstream ss;
	ss << Version::OnePointOne;
	REQUIRE(ss.str() == "HTTP/1.1");
}

TEST_CASE("HTTP version deserialization method works as expected")
{
	std::stringstream ss{"HTTP/1.0"};
	Version version;
	ss >> version;
	REQUIRE(version == Version::OnePointOh);
}
