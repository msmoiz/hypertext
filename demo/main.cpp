#include <iostream>

#include "client.h"
#include "exceptions.h"

int main()
{
	using namespace hypertext;

	Request request = Request::build()
	                  .host("www.google.com")
	                  .port(80)
	                  .resource("/");

	try
	{
		Client client;
		const Response response{client.dispatch(std::move(request))};
		std::cout
			<< "API returned with " << std::endl
			<< "Status code: " << (int)response.status_code() << std::endl
			<< "Body: " << response.body() << std::endl;
	}
	catch (Exception& e)
	{
		std::cerr << "Encountered error while fetching response: " << e.what();
	}
	
	return 0;
}
