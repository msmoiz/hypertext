#include "client.h"

#include <algorithm>
#include <optional>
#include <sstream>

#include "connection.h"
#include "serialization.h"

namespace hypertext
{
	Response Client::dispatch(const Request request)
	{
		Connection connection{request.host, request.port};

		auto raw_request = parse_request_to_string(request);
		connection.send(std::move(raw_request));
		
		std::string raw_response;
		std::optional<std::size_t> end_of_frontmatter;
		std::optional<std::size_t> expected_body_length;
		bool chunked_transfer{false};
		auto response = Response::build();
		do
		{
			raw_response.append(connection.receive());
			if (!end_of_frontmatter)
			{
				if (const auto pos = raw_response.find("\r\n\r\n"); pos != std::string::npos)
				{
					end_of_frontmatter = pos + 3;
					std::stringstream frontmatter{raw_response.substr(0, *end_of_frontmatter - 2)};
					std::string line;
					std::getline(frontmatter, line);
					{
						Version version;
						std::string status_code;
						std::string status_message;
						std::stringstream{line} >> version >> status_code >> status_message;
						response
							.version(version)
							.status_code(StatusCode{std::stoi(status_code)})
							.status_message(status_message);
					}
					while (std::getline(frontmatter, line))
					{
						std::string key, value;
						std::stringstream header_line{line.substr(0, line.length() - 1)};
						std::getline(header_line, key, ':');
						header_line.ignore(1);
						std::getline(header_line, value);
						response.header(key, value);

						std::transform(key.begin(), key.end(), key.begin(), [](auto c) { return std::tolower(c); });
						if (key == "content-length")
						{
							expected_body_length = std::stoi(value);
						}
						else if (key == "transfer-encoding" && value == "chunked")
						{
							chunked_transfer = true;
						}
					}
				}
			}

			if (end_of_frontmatter)
			{
				if (!chunked_transfer && !expected_body_length)
				{
					break;
				}

				if (chunked_transfer)
				{
					if (const auto pos = raw_response.find("0\r\n\r\n", *end_of_frontmatter); pos != std::string::npos)
					{
						std::stringstream chunks{raw_response.substr(*end_of_frontmatter + 1)};
						std::string body;
						std::string line;
						std::string chunk;
						std::size_t chunk_size;
						while (std::getline(chunks, line))
						{
							std::stringstream{line} >> std::hex >> chunk_size >> std::dec;
							chunk.resize(chunk_size);
							chunks.read(&chunk[0], chunk_size);
							chunks.ignore(2);
							body.append(chunk);
						}
						response.body(body);
						break;
					}
				}
				else if (expected_body_length && ((raw_response.length() - *end_of_frontmatter - 1) >= expected_body_length))
				{
					response.body(raw_response.substr(*end_of_frontmatter + 1));
					break;
				}
			}
		} while (true);

		connection.release();

		return response;
	}
}
