// Copyright 2021 Mustafa Moiz.

#include <iostream>

#include "client.h"
#include "exceptions.h"

int main()
{
	using namespace hypertext;

	Request request = Request::build()
	                  .host("jsonplaceholder.typicode.com")
	                  .header("Host", "jsonplaceholder.typicode.com")
	                  .resource("/todos/1");

	try
	{
		std::cout << "Sending request to " << request.host() << request.resource() << std::endl;
		
		Client client;
		const Response response{client.dispatch(std::move(request))};
		
		std::cout
			<< "Received response " << (int)response.status_code() << " (" << response.status_message() << ")" << std::endl
			<< "--------------" << std::endl
			<< response.body() << std::endl;
	}
	catch (Exception& e)
	{
		std::cerr << "Encountered error while fetching response: " << e.what();
	}

	return 0;
}
