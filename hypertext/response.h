#pragma once

#include <unordered_map>

#include "status_code.h"
#include "version.h"
#include "utils/value.h"

namespace hypertext
{
	/**
	 * Represents an HTTP response.
	 */
	struct Response
	{
		template<typename T>
		using Value = Value<T, class ResponseBuilder>;

		static class ResponseBuilder build();

		/**
		 * Version of HTTP used by the response.
		 * Defaults to Version::OnePointOne.
		 */
		Value<Version> version{Version::OnePointOne};

		/**
		 * Status code returned by the response.
		 * Defaults to StatusCode::Okay.
		 */
		Value<StatusCode> status_code{StatusCode::Okay};

		/**
		 * Status message returned by the response.
		 */
		Value<std::string> status_message;

		/**
		 * Headers returned by the response.
		 */
		Value<std::unordered_map<std::string, std::string>> headers;

		/**
		 * Body returned by the response.
		 */
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
