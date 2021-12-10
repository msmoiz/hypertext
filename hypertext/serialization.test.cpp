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

TEST_CASE("Response deserialization works as expected")
{
	std::string input =
		"HTTP/1.1 200 Okay\r\n"
		"Access-Control-Allow-Origin: *\r\n"
		"\r\n"
		"A simple string";

	Response response = parse_response_from_string(std::move(input));

	REQUIRE(response.version() == Version::OnePointOne);
	REQUIRE(response.status_code() == StatusCode::Okay);
	REQUIRE(response.status_message() == "Okay");
	REQUIRE(response.headers().size() == 1);
	REQUIRE(response.headers().at("Access-Control-Allow-Origin") == "*");
	REQUIRE(response.body() == "A simple string");
}
