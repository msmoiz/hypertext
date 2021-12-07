#pragma once

#include <unordered_map>

#include "status_code.h"
#include "version.h"
#include "utils/value.h"

namespace hypertext
{
	struct Response
	{
		template<typename T>
		using Value = Value<T, class ResponseBuilder>;

		static class ResponseBuilder build();

		Value<Version> version{Version::OnePointOne};
		Value<StatusCode> status_code{StatusCode::Okay};
		Value<std::string> status_message;
		Value<std::unordered_map<std::string, std::string>> headers;
		Value<std::string> body;

	private:
		
		Response() = default;
		friend class ResponseBuilder;
	};

	class ResponseBuilder
	{
	public:

		ResponseBuilder& version(const Version version) { *response_.version = version; return *this; }
		ResponseBuilder& status_code(const StatusCode status_code) { *response_.status_code = status_code; return *this; }
		ResponseBuilder& status_message(std::string status_message) { *response_.status_message = std::move(status_message); return *this; }
		ResponseBuilder& header(std::string key, std::string value) { (*response_.headers)[std::move(key)] = std::move(value); return *this; }
		ResponseBuilder& body(std::string body) { *response_.body = std::move(body); return *this; }

		operator Response() { return std::move(response_); }
		
	private:

		Response response_;
	};

	inline ResponseBuilder Response::build()
	{
		return ResponseBuilder{};
	}
}
