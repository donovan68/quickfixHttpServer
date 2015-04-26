#include <HttpClientConnection.hpp>

namespace httpServer
{

HttpClientConnection::HttpClientConnection(SocketSmartPtr socket, boost::shared_ptr<HttpClientConnManager> manager) :
_socket(socket),
_clientManager(manager)
{

}

void HttpClientConnection::do_read()
{

}

void HttpClientConnection::do_write()
{

}

void HttpClientConnection::start()
{
    do_read();
}

void HttpClientConnection::stop()
{
    _socket->close();
}

}
