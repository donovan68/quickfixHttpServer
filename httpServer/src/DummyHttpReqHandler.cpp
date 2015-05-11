#include <DummyHttpReqHandler.hpp>
#include <iostream>

#include <boost/lexical_cast.hpp>

#include <fstream>

namespace httpServer
{

void DummyHttpReqHandler::handleGetRequest(HttpRequest::ConstSmartPtr req, HttpReply::SmartPtr rep)
{
    std::cout << " GET REQ " << std::endl;
    std::string extension;
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

    // If path ends in slash (i.e. is a directory) then add "index.html".
    if (request_path[request_path.size() - 1] == '/')
    {

        rep->_status = HttpReply::ok;
        rep->_content = "<html><head><title>Hello World</title>"
                "<link rel='shortcut icon' type='image/x-icon' href='/favicon.ico' />"
                "</head>"
                "<body><h1>Hiiiii World</h1><br>"
                "<img src='fb_login.png' /></body></html>";
        extension = "html";

    }
    else
    {
        // Determine the file extension.
        std::size_t last_slash_pos = request_path.find_last_of("/");
        std::size_t last_dot_pos = request_path.find_last_of(".");

        if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos)
        {
            extension = request_path.substr(last_dot_pos + 1);
        }

        // Open the file to send back.
        std::string full_path = _docRoot + request_path;

        std::cout << " Full Path: " << full_path << std::endl;

        std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
        if (!is)
        {
            HttpReply::stock_reply(HttpReply::not_found, rep);
            return;
        }

        // Fill out the reply to be sent to the client.
        rep->_status = HttpReply::ok;
        char buf[512];
        while (is.read(buf, sizeof (buf)).gcount() > 0)
            rep->_content.append(buf, is.gcount());
    }
    rep->_headers.resize(2);
    rep->_headers[0] = HttpHeader::SmartPtr(new HttpHeader());
    rep->_headers[1] = HttpHeader::SmartPtr(new HttpHeader());
    rep->_headers[0]->_name = "Content-Length";
    rep->_headers[0]->_value = boost::lexical_cast<std::string>(rep->_content.size());
    rep->_headers[1]->_name = "Content-Type";
    rep->_headers[1]->_value = extension_to_type(extension);
}

void DummyHttpReqHandler::handlePostRequest(HttpRequest::ConstSmartPtr req, HttpReply::SmartPtr rep)
{
    std::cout << " POST REQ " << std::endl;
}



}
