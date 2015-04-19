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

namespace httpServer
{

class HttpClientConnection : private boost::noncopyable
{
public:
    typedef boost::shared_ptr<HttpClientConnection> SmartPtr;
    typedef boost::shared_ptr<const HttpClientConnection> ConstSmartPtr;
private:

public:

    HttpClientConnection();


};

}

#endif	/* HTTPCLIENTCONNECTION_HPP */

