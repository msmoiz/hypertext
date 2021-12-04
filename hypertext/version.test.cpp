#include "version.h"

#include <catch2/catch.hpp>

using namespace hypertext;

TEST_CASE("HTTP version stringification method should return spec-compliant string")
{
	REQUIRE(to_spec_compliant_string(Version::OnePointOne) == "HTTP/1.1");
}
