/* 
 * File:   HttpClientConnection.hpp
 * Author: ankithbti
 *
 * Created on 19 April, 2015, 3:48 PM
 */

#ifndef HTTPCLIENTCONNECTION_HPP
#define	HTTPCLIENTCONNECTION_HPP

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/asio.hpp>

#include <HttpReply.hpp>
#include <HttpRequest.hpp>
#include <HttpReqParser.hpp>
#include <HttpReqHandlerInterface.hpp>

namespace httpServer
{

class HttpClientConnManager;

class HttpClientConnection : private boost::noncopyable, public boost::enable_shared_from_this<HttpClientConnection>
{
public:
    typedef boost::shared_ptr<HttpClientConnection> SmartPtr;
    typedef boost::shared_ptr<const HttpClientConnection> ConstSmartPtr;
    typedef boost::shared_ptr<boost::asio::ip::tcp::socket> SocketSmartPtr;
private:
    SocketSmartPtr _socket;
    boost::array<char, 8192> _buffer;
    std::string _clientId;

    boost::shared_ptr<HttpClientConnManager> _clientManager;
    
    HttpReqParser _reqParser;
    HttpRequest::SmartPtr _request;
    HttpReply::SmartPtr _reply;

    HttpReqHandlerInterface::SmartPtr _reqHandler;
    
    /// Perform an asynchronous read operation.
    void do_read();
    
    void asyncRead(boost::system::error_code ec, std::size_t bytes_transferred);

    /// Perform an asynchronous write operation.
    void do_write();
    
    void asyncWrite(boost::system::error_code ec, std::size_t bytes_transferred);
public:

    HttpClientConnection(SocketSmartPtr socket, boost::shared_ptr<HttpClientConnManager> manager, HttpReqHandlerInterface::SmartPtr reqHanlder);

    void start();
    void stop();

};

}

#endif	/* HTTPCLIENTCONNECTION_HPP */

