/* 
 * File:   HttpHeader.hpp
 * Author: ankithbti
 *
 * Created on 7 May, 2015, 11:32 PM
 */

#ifndef HTTPHEADER_HPP
#define	HTTPHEADER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>

namespace httpServer {

class HttpHeader : private boost::noncopyable {
    
public:
    
    typedef boost::shared_ptr<HttpHeader> SmartPtr;
    typedef boost::shared_ptr<const HttpHeader> ConstSmartPtr;
    
    std::string _name;
    std::string _value;
    
};
}

#endif	/* HTTPHEADER_HPP */

