#include <HttpClientConnection.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <HttpClientConnManager.hpp>

namespace httpServer
{

HttpClientConnection::HttpClientConnection(SocketSmartPtr socket, boost::shared_ptr<HttpClientConnManager> manager) :
_socket(socket),
_clientManager(manager),
_request(new HttpRequest()),
_reply(new HttpReply()),
_reqHandler(new DummyHttpReqHandler("/Users/ankithbti/Development/Cpp/httpServer"))
{

}

void HttpClientConnection::do_read()
{
    _socket->async_read_some(boost::asio::buffer(_buffer), boost::bind(&HttpClientConnection::asyncRead, shared_from_this(), _1, _2));
}

void HttpClientConnection::asyncRead(boost::system::error_code ec, std::size_t bytes_transferred)
{
    if (!ec)
    {
        HttpReqParser::result_type result;
        std::cout << "Req: " << _buffer.data() << std::endl ;
        boost::tie(result, boost::tuples::ignore) = _reqParser.parse(
                                                                     _request, _buffer.data(), _buffer.data() + bytes_transferred);

        //std::cout << " Bytes Read: " << bytes_transferred << std::endl ;
        if (result == HttpReqParser::good)
        {
            // Handle the req_ - whatever in the URL asked from user
            _reqHandler->handleRequest(_request, _reply);
            //do_write();
            //_reply = HttpReply::stock_reply(HttpReply::ok);
            do_write();

        }
        else if (result == HttpReqParser::bad)
        {
            HttpReply::stock_reply(HttpReply::bad_request, _reply);
            do_write();
        }
        else
        {
            // Keep Reading from socket
            do_read();
        }
    }
    else if (ec != boost::asio::error::operation_aborted)
    {
        //std::cout << " Error Message " << ec.message() << std::endl;
        _clientManager->stop(shared_from_this());
    }
    else
    {
        std::cout << " Error Message " << ec.message() << std::endl;
    }
}

void HttpClientConnection::do_write()
{
    boost::asio::async_write(*(_socket.get()), _reply->to_buffers(), boost::bind(&HttpClientConnection::asyncWrite, shared_from_this(), _1, _2));
}

void HttpClientConnection::asyncWrite(boost::system::error_code ec, std::size_t bytes_transferred)
{
    if (!ec)
    {
        // Initiate graceful connection closure.
        boost::system::error_code ignored_ec;
        _socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both,
                          ignored_ec);
    }

    if (ec != boost::asio::error::operation_aborted)
    {
        _clientManager->stop(shared_from_this());
    }

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
