/* 
 * File:   DummyHttpReqHandler.hpp
 * Author: ankithbti
 *
 * Created on 11 May, 2015, 12:23 PM
 */

#ifndef DUMMYHTTPREQHANDLER_HPP
#define	DUMMYHTTPREQHANDLER_HPP

#include <HttpReqHandlerInterface.hpp>

namespace httpServer{

class DummyHttpReqHandler : public HttpReqHandlerInterface {
    
public:
    
    typedef boost::shared_ptr<DummyHttpReqHandler> SmartPtr;
    
private:
    
public:
    
    explicit DummyHttpReqHandler(const std::string& docRoot) : HttpReqHandlerInterface(docRoot){
        
    }
    
    virtual void handleGetRequest(HttpRequest::ConstSmartPtr req, HttpReply::SmartPtr rep);
    virtual void handlePostRequest(HttpRequest::ConstSmartPtr req, HttpReply::SmartPtr rep);


};

}

#endif	/* DUMMYHTTPREQHANDLER_HPP */

