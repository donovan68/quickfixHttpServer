#include <HttpServer.hpp>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>

#include "HttpClientConnection.hpp"

namespace httpServer
{

HttpServer::HttpServer(const std::string& port, const std::string& docRoot) : _serverPort(port),
_docRoot(docRoot),
_ioService(),
_acceptor(_ioService),
_socket(new boost::asio::ip::tcp::socket(_ioService)),
_isAlive(false),
_clientManager(new HttpClientConnManager())
{
    // Open the acceptor with the option to reuse the address (i.e. SO_REUSEADDR).
    boost::asio::ip::tcp::resolver resolver(_ioService);
    boost::asio::ip::tcp::resolver::query query("127.0.0.1", _serverPort);
    boost::asio::ip::tcp::endpoint endpoint = *resolver.resolve(query);
    _acceptor.open(endpoint.protocol());
    _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(endpoint);
    _acceptor.listen();

    do_accept();
}

void HttpServer::do_accept()
{
    std::cout << " Ready to accept connections on " + _serverPort << std::endl;
    _acceptor.async_accept(*_socket.get(), boost::bind(&HttpServer::asyncAccept, this, _1));
}

void HttpServer::asyncAccept(boost::system::error_code ec)
{
    if (!_acceptor.is_open())
    {
        std::cout << " Acceptor is not open to accept any new connection. " << std::endl;
        return;
    }

    if (!ec)
    {
        // Create new HttpClientConnection using the above socket
        std::cout << " New Client connection created. " << std::endl;
        HttpClientConnection::SmartPtr clientConn(new HttpClientConnection(_socket, _clientManager /* ,reqHandler_*/));
        _clientManager->start(clientConn);
        _socket = boost::shared_ptr<boost::asio::ip::tcp::socket>(new boost::asio::ip::tcp::socket(_ioService));

    }
    else
    {
        std::cout << " Error while accepting : " << ec.message() << std::endl;
    }

    // Ready to accept new request
    do_accept();
}

void HttpServer::runIoService()
{
    std::cout << " Starting IoServceRun Thread. " << std::endl;
    _ioService.run();
    std::cout << " Stopping IoServceRun Thread. " << std::endl;

}

void HttpServer::start()
{
    {
        boost::unique_lock<boost::mutex> lock(_startStopMutex);
        _isAlive = true;
    }

    _ioServiceRunThread = boost::shared_ptr<boost::thread>(new boost::thread(&HttpServer::runIoService, this));
}

void HttpServer::stop()
{
    {
        boost::unique_lock<boost::mutex> lock(_startStopMutex);
        _isAlive = false;
    }

    _ioServiceRunThread->interrupt();

    std::cout << " Stopped IoServceRun Thread. Now Closing Acceptor. " << std::endl;

    if (_acceptor.is_open())
    {
        _acceptor.close();
    }

    _clientManager->stopAll();
}



}
