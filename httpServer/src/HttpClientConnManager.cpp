#include <HttpClientConnManager.hpp>
#include <boost/foreach.hpp>
namespace httpServer
{

void HttpClientConnManager::start(HttpClientConnection::SmartPtr clientConn)
{
    _clientConnections.insert(clientConn);
    clientConn->start();
}

void HttpClientConnManager::stop(HttpClientConnection::SmartPtr clientConn)
{
    _clientConnections.erase(clientConn);
}

void HttpClientConnManager::stopAll()
{

    BOOST_FOREACH(HttpClientConnection::SmartPtr clientConn, _clientConnections)
    {
        clientConn->stop();
    }
    _clientConnections.clear();
}


}
