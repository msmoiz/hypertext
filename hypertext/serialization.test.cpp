// Copyright 2021 Mustafa Moiz.

#include <catch2/catch.hpp>

#include "serialization.h"

using namespace hypertext;

TEST_CASE("Request serialization works as expected")
{
	Request request = Request::build()
	                  .method(Method::Get)
	                  .resource("/test")
	                  .parameter("param", "value")
	                  .header("Header", "value");

	std::string output =
		"GET /test?param=value HTTP/1.1\r\n"
		"Header: value\r\n"
		"\r\n";

	REQUIRE(parse_request_to_string(request) == output);
}
