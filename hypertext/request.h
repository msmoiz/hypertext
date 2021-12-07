#pragma once

#include <unordered_map>
#include <utility>

#include "method.h"
#include "version.h"
#include "utils/value.h"

namespace hypertext
{
	/**
	 * Represents an HTTP request.
	 */
	class Request
	{
	public:

		template<typename T>
		using Value = Value<T, class RequestBuilder>;

		static class RequestBuilder build();

		/**
		 * The HTTP method to use.
		 * Defaults to Method::Get.
		 */
		Value<Method> method{Method::Get};

		/**
		 * The host to send the request to.
		 * Can be a hostname or IPv4 address.
		 */
		Value<std::string> host;

		/**
		 * Port on the host to send the request to.
		 * Defaults to 80.
		 */
		Value<int> port{80};

		/**
		 * Resource targeted by the request.
		 * Defaults to "/" (i.e., root).
		 */
		Value<std::string> resource{"/"};

		/**
		 * Parameters to send with the request.
		 * Will be sent without manipulation,
		 * which means users must manually encode these entries.
		 */
		Value<std::unordered_map<std::string, std::string>> parameters;

		/**
		 * Version of HTTP to use for the request.
		 * Defaults to Version::OnePointOne.
		 */
		Value<Version> version{Version::OnePointOne};

		/**
		 * Headers to send with the request.
		 * Will be sent without manipulation.
		 */
		Value<std::unordered_map<std::string, std::string>> headers;

		/**
		 * Body to send with the request.
		 * Will be sent without manipulation.
		 */
		Value<std::string> body;

	private:

		Request() = default;
		friend class RequestBuilder;
	};

	class RequestBuilder
	{
	public:

		RequestBuilder& method(const Method method) { *request_.method = method; return *this; }
		RequestBuilder& host(std::string host) { *request_.host = std::move(host); return *this; }
		RequestBuilder& port(const int port) { *request_.port = port; return *this; }
		RequestBuilder& resource(std::string resource) { *request_.resource = std::move(resource); return *this; }
		RequestBuilder& version(const Version version) { *request_.version = version; return *this; }
		RequestBuilder& parameter(std::string key, std::string value) { (*request_.parameters)[std::move(key)] = std::move(value); return *this; }
		RequestBuilder& header(std::string key, std::string value) { (*request_.headers)[std::move(key)] = std::move(value); return *this; }
		RequestBuilder& body(std::string body) { *request_.body = std::move(body); return *this; }
		
		operator Request() { return std::move(request_); }
		
	private:

		Request request_;
	};

	inline RequestBuilder Request::build()
	{
		return RequestBuilder{};
	}
}
