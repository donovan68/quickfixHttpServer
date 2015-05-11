/* 
 * File:   HttpReqHandlerInterface.hpp
 * Author: ankithbti
 *
 * Created on 11 May, 2015, 11:35 AM
 */

#ifndef HTTPREQHANDLERINTERFACE_HPP
#define	HTTPREQHANDLERINTERFACE_HPP

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/foreach.hpp>

#include <HttpRequest.hpp>
#include <HttpReply.hpp>

namespace httpServer
{

class HttpReqHandlerInterface : private boost::noncopyable
{
public:

    typedef boost::shared_ptr<HttpReqHandlerInterface> SmartPtr;
    typedef boost::shared_ptr<const HttpReqHandlerInterface> ConstSmartPtr;

    struct mapping
    {
        const char* extension;
        const char* mime_type;
    } mimemaps[6];

protected:

    std::string _docRoot;

protected:
    
    std::string extension_to_type(const std::string& extension)
    {
        BOOST_FOREACH(mapping m, mimemaps)
        {
            if (m.extension == extension)
            {
                return m.mime_type;
            }
        }

        return "text/plain";
    }

    /// Perform URL-decoding on a string. Returns false if the encoding was
    /// invalid.
    bool url_decode(const std::string& in, std::string& out);

public:

    explicit HttpReqHandlerInterface(const std::string& docRoot);
    
    virtual ~HttpReqHandlerInterface(){
        
    }
    
    /// Handle a request and produce a reply.
    void handleRequest(HttpRequest::ConstSmartPtr req, HttpReply::SmartPtr rep);

    virtual void handleGetRequest(HttpRequest::ConstSmartPtr req, HttpReply::SmartPtr rep) = 0;
    virtual void handlePostRequest(HttpRequest::ConstSmartPtr req, HttpReply::SmartPtr rep) = 0;
};
}


#endif	/* HTTPREQHANDLERINTERFACE_HPP */

