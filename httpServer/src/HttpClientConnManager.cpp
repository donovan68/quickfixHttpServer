#include <HttpClientConnManager.hpp>
#include <boost/foreach.hpp>
namespace httpServer
{

void HttpClientConnManager::start(HttpClientConnection::ConstSmartPtr clientConn)
{
    _clientConnections.insert(clientConn);
}

void HttpClientConnManager::stop(HttpClientConnection::ConstSmartPtr clientConn)
{
    _clientConnections.erase(clientConn);
}

void HttpClientConnManager::stopAll()
{

    BOOST_FOREACH(HttpClientConnection::ConstSmartPtr clientConn, _clientConnections)
    {

    }
    _clientConnections.clear();
}


}
