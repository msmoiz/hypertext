#include <sstream>

#include "method.h"

#include <catch2/catch.hpp>

using namespace hypertext;

TEST_CASE("HTTP method stringification method should return spec-compliant string")
{
	std::stringstream ss;
	ss << Method::Get << " " << Method::Head << " " << Method::Options;	
	REQUIRE(ss.str() == "GET HEAD OPTIONS");
}
