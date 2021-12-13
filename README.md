# Hypertext

Hypertext is a tiny library for sending HTTP requests.

![Screenshot](https://i.imgur.com/UfXDi3g.png)

It supports arbitrary hosts, ports, headers, query parameters, and bodies for requests. For responses, it handles both fixed length and chunked bodies. It depends on nothing but the Winsock library for sockets interfaces and [Catch](https://github.com/catchorg/Catch2) for testing. This library suffices for quick-and-dirty use cases but is not ready for production at this time. Among other things, the library is missing:

* Support for SSL/TLS-based communication (i.e., HTTPS)
* Timeouts to limit long-running requests
* Retries for robust error handling
* Better exception structure and documentation

I might get around to those features one day. Maybe, but maybe not. In the meantime, for production settings, you are probably better off using [libcurl](https://github.com/curl/curl).
