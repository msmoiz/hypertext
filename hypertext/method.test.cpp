#include "method.h"

#include <catch2/catch.hpp>

using namespace hypertext;

TEST_CASE("HTTP method stringification method should return spec-compliant string")
{
	REQUIRE(to_spec_compliant_string(Method::Connect) == "CONNECT");
	REQUIRE(to_spec_compliant_string(Method::Delete) == "DELETE");
	REQUIRE(to_spec_compliant_string(Method::Get) == "GET");
	REQUIRE(to_spec_compliant_string(Method::Head) == "HEAD");
	REQUIRE(to_spec_compliant_string(Method::Options) == "OPTIONS");
	REQUIRE(to_spec_compliant_string(Method::Patch) == "PATCH");
	REQUIRE(to_spec_compliant_string(Method::Put) == "PUT");
	REQUIRE(to_spec_compliant_string(Method::Post) == "POST");
	REQUIRE(to_spec_compliant_string(Method::Trace) == "TRACE");
}
