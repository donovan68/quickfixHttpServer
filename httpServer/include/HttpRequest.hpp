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
    typedef boost::shared_ptr<HttpRequest> SmartPtr;
    typedef boost::shared_ptr<const HttpRequest> ConstSmartPtr;
    
public:
    
    std::string _method;
    std::string _uri;
    int _httpMajorVersion;
    int _httpMinorVersion;
    std::vector<HttpHeader::SmartPtr> _headers;
    std::string _PostData;
    
    HttpRequest();
    
    
};


}

#endif	/* HTTPREQUEST_HPP */

