/* 
 * File:   HttpServer.hpp
 * Author: ankithbti
 *
 * Created on 19 April, 2015, 3:23 PM
 */

#ifndef HTTPSERVER_HPP
#define	HTTPSERVER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/asio.hpp>


namespace httpServer
{

class HttpServer : private boost::noncopyable
{
public:

    typedef boost::shared_ptr<HttpServer> SmartPtr;
    typedef boost::shared_ptr<const HttpServer> ConstSmartPtr;
private:
    boost::asio::io_service _ioService;
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::asio::ip::tcp::socket _socket_;


public:

    HttpServer(const int port, const std::string& docRoot);

    void start();
    void stop();
    void isAlive();

};


}

#endif	/* HTTPSERVER_HPP */

