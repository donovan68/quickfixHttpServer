#include <HttpReqHandlerInterface.hpp>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <Constants.hpp>

namespace httpServer
{

HttpReqHandlerInterface::HttpReqHandlerInterface(const std::string& docRoot) : _docRoot(docRoot)
{
    mimemaps[0].extension = "gif";
    mimemaps[0].mime_type = "image/gif";
    mimemaps[1].extension = "htm";
    mimemaps[1].mime_type = "text/htm";
    mimemaps[2].extension = "html";
    mimemaps[2].mime_type = "text/html";
    mimemaps[3].extension = "jpg";
    mimemaps[3].mime_type = "image/jpeg";
    mimemaps[4].extension = "png";
    mimemaps[4].mime_type = "image/png";
    mimemaps[5].extension = "ico";
    mimemaps[5].mime_type = "image/x-icon";
    mimemaps[6].extension = "xml";
    mimemaps[6].mime_type = "text/xml";
    mimemaps[7].extension = "json";
    mimemaps[7].mime_type = "application/json";
}

void HttpReqHandlerInterface::handleRequest(HttpRequest::ConstSmartPtr req, HttpReply::SmartPtr rep)
{
    // Decode url to path.
    std::string request_path;
    if (!url_decode(req->_uri, request_path))
    {
        HttpReply::stock_reply(HttpReply::bad_request, rep);
        return;
    }

    // Request path must be absolute and not contain "..".
    if (request_path.empty() || request_path[0] != '/'
            || request_path.find("..") != std::string::npos)
    {
        HttpReply::stock_reply(HttpReply::bad_request, rep);
        return;
    }
    
    //std::cout << " From ReqHandler. URI: " << req->_uri << " , Req_Path: " << request_path << " , Method: " << req->_method << std::endl ;
    //HttpReply::stock_reply(HttpReply::created, rep);
    
    //std::cout << " Params: " << req->_headers.size() << std::endl;
    
//    BOOST_FOREACH(HttpHeader::SmartPtr header, req->_headers){
//        std::cout << " HeaderName: " << header->_name << " , Value: " << header->_value << std::endl ;
//    }
//    std::cout << " Content: " << req->_PostData << std::endl ;
    
    if(boost::iequals(req->_method, HTTP_GET_METHOD_STRING)){
        handleGetRequest(req, rep);
    }else if(boost::iequals(req->_method, HTTP_POST_METHOD_STRING)){
        handlePostRequest(req, rep);
    }else if(boost::iequals(req->_method, HTTP_PUT_METHOD_STRING)){
        handlePutRequest(req, rep);
    }else if(boost::iequals(req->_method, HTTP_DELETE_METHOD_STRING)){
        handleDeleteRequest(req, rep);
    }
}

bool HttpReqHandlerInterface::url_decode(const std::string& in, std::string& out)
{
    out.clear();
    out.reserve(in.size());
    for (std::size_t i = 0; i < in.size(); ++i)
    {
        if (in[i] == '%')
        {
            if (i + 3 <= in.size())
            {
                int value = 0;
                std::istringstream is(in.substr(i + 1, 2));
                if (is >> std::hex >> value)
                {
                    out += static_cast<char> (value);
                    i += 2;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else if (in[i] == '+')
        {
            out += ' ';
        }
        else
        {
            out += in[i];
        }
    }
    return true;
}





}
