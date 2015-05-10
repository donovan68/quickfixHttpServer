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
#include <boost/thread.hpp>
#include <HttpClientConnManager.hpp>


namespace httpServer
{

class HttpServer : private boost::noncopyable
{
public:

    typedef boost::shared_ptr<HttpServer> SmartPtr;
    typedef boost::shared_ptr<const HttpServer> ConstSmartPtr;
private:
    std::string _serverPort;
    std::string _docRoot;
    boost::asio::io_service _ioService;
    boost::asio::ip::tcp::acceptor _acceptor;
    boost::shared_ptr<boost::asio::ip::tcp::socket> _socket;

    boost::shared_ptr<boost::thread> _ioServiceRunThread;
    mutable boost::mutex _startStopMutex;
    volatile bool _isAlive;
    
    boost::shared_ptr<HttpClientConnManager> _clientManager;

    void do_accept();
    void asyncAccept(boost::system::error_code ec);
    void runIoService();


public:

    HttpServer(const std::string& port, const std::string& docRoot);

    void start();
    void stop();

    bool isAlive()
    {
        boost::unique_lock<boost::mutex> lock(_startStopMutex);
        return _isAlive;
    }

};


}

#endif	/* HTTPSERVER_HPP */

