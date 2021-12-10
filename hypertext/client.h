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
		
		Response dispatch(Request request);
	};
}
