// Copyright 2021 Mustafa Moiz.

#pragma once

#include "request.h"
#include "response.h"

namespace hypertext
{
	/**
	 * A client for sending HTTP requests.
	 */
	class Client
	{
	public:

		/**
		 * Send an HTTP request and get the response.
		 * Does not manipulate the request in any way,
		 * including by adding or removing headers,
		 * modifying or encoding the query parameters,
		 * or running other interference.
		 * Connection is discarded following request completion.
		 */
		Response dispatch(Request request);
	};
}
