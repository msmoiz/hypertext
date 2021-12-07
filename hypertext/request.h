#pragma once

#include <unordered_map>
#include <utility>

#include "method.h"
#include "version.h"
#include "utils/value.h"

namespace hypertext
{
	class Request
	{
	public:

		template<typename T>
		using Value = Value<T, class RequestBuilder>;

		static class RequestBuilder build();

		Value<Method> method{Method::Get};
		Value<std::string> uri;
		Value<Version> version{Version::OnePointOne};
		Value<std::unordered_map<std::string, std::string>> headers;
		Value<std::string> body;

	private:

		Request() = default;
		friend class RequestBuilder;
	};

	class RequestBuilder
	{
	public:

		RequestBuilder& method(const Method method) { *request_.method = method; return *this; }
		RequestBuilder& uri(std::string uri) { *request_.uri = std::move(uri); return *this; }
		RequestBuilder& version(const Version version) { *request_.version = version; return *this; }
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
