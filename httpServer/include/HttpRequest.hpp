/* 
 * File:   HttpRequest.hpp
 * Author: ankithbti
 *
 * Created on 7 May, 2015, 11:23 PM
 */

#ifndef HTTPREQUEST_HPP
#define	HTTPREQUEST_HPP

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <HttpHeader.hpp>
#include <vector>

namespace httpServer {

class HttpRequest : private boost::noncopyable {
public:
    boost::shared_ptr<HttpRequest> SmartPtr;
    boost::shared_ptr<const HttpRequest> ConstSmartPtr;
    
private:
    
    std::string _method;
    std::string _uri;
    int _httpMajorVersion;
    int _httpMinorVersion;
    std::vector<HttpHeader> _headers;
    
public:
    HttpRequest();
    
    
};


}

#endif	/* HTTPREQUEST_HPP */

