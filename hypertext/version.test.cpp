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
