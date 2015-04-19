/* 
 * File:   HttpClientConnManager.hpp
 * Author: ankithbti
 *
 * Created on 19 April, 2015, 3:44 PM
 */

#ifndef HTTPCLIENTCONNMANAGER_HPP
#define	HTTPCLIENTCONNMANAGER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <HttpClientConnection.hpp>
#include <set>

namespace httpServer
{

class HttpClientConnManager : private boost::noncopyable
{
public:
    typedef boost::shared_ptr<HttpClientConnManager> SmartPtr;
    typedef std::set<HttpClientConnection::ConstSmartPtr> ClientConnections;
private:

    ClientConnections _clientConnections;

public:

    void start(HttpClientConnection::ConstSmartPtr clientConn);
    void stop(HttpClientConnection::ConstSmartPtr clientConn);
    void stopAll();

};
}

#endif	/* HTTPCLIENTCONNMANAGER_HPP */

