#include <QuickFixHttpServer.hpp>
#include <iostream>
#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>
#include <fstream>
#include <vector>

namespace qfHttpServer {

    void QuickFixHttpServer::handleGetRequest(httpServer::HttpRequest::ConstSmartPtr req, httpServer::HttpReply::SmartPtr rep) {
        std::cout << " GET REQ " << std::endl;
        std::string extension;
        // Decode url to path.
        std::string request_path;
        if (!url_decode(req->_uri, request_path)) {
            httpServer::HttpReply::stock_reply(httpServer::HttpReply::bad_request, rep);
            return;
        }

        // Request path must be absolute and not contain "..".
        if (request_path.empty() || request_path[0] != '/'
                || request_path.find("..") != std::string::npos) {
            httpServer::HttpReply::stock_reply(httpServer::HttpReply::bad_request, rep);
            return;
        }

        // If path ends in slash (i.e. is a directory) then add "index.html".
        if (request_path[request_path.size() - 1] == '/') {

            rep->_status = httpServer::HttpReply::ok;

            rep->_content = "<html><head><title>Hello World</title>"
                    "<link rel='shortcut icon' type='image/x-icon' href='/favicon.ico' />"
                    "</head>"
                    "<body><h1>Hiiiii World</h1><br>"
                    "<img src='fb_login.png' /></body>";
            rep->_content += "<h2>Sessions</h2><ul>";
            BOOST_FOREACH(std::string s, _application.getSessionIDSet()){
                rep->_content += "<li>";
                rep->_content += s;
                if(_application.getSession(s) != NULL){
                    rep->_content += " - <font color='green'>Connected</font> ";
                }else{
                    rep->_content += " - <font color='red'>disconnected</font>";
                }
                rep->_content += "</li>";
            }
            rep->_content += "</ul>";
            rep->_content += "</html>";
            extension = "html";

        } else {
            // Determine the file extension.
            std::size_t last_slash_pos = request_path.find_last_of("/");
            std::size_t last_dot_pos = request_path.find_last_of(".");

            if (last_dot_pos != std::string::npos && last_dot_pos > last_slash_pos) {
                extension = request_path.substr(last_dot_pos + 1);
            }

            // Open the file to send back.
            std::string full_path = _docRoot + request_path;

            std::cout << " Full Path: " << full_path << std::endl;

            std::ifstream is(full_path.c_str(), std::ios::in | std::ios::binary);
            if (!is) {
                httpServer::HttpReply::stock_reply(httpServer::HttpReply::not_found, rep);
                return;
            }

            // Fill out the reply to be sent to the client.
            rep->_status = httpServer::HttpReply::ok;
            char buf[512];
            while (is.read(buf, sizeof (buf)).gcount() > 0)
                rep->_content.append(buf, is.gcount());
        }
        rep->_headers.resize(2);
        rep->_headers[0] = httpServer::HttpHeader::SmartPtr(new httpServer::HttpHeader());
        rep->_headers[1] = httpServer::HttpHeader::SmartPtr(new httpServer::HttpHeader());
        rep->_headers[0]->_name = "Content-Length";
        rep->_headers[0]->_value = boost::lexical_cast<std::string>(rep->_content.size());
        rep->_headers[1]->_name = "Content-Type";
        rep->_headers[1]->_value = extension_to_type(extension);
    }

    void QuickFixHttpServer::handleDeleteRequest(httpServer::HttpRequest::ConstSmartPtr req, httpServer::HttpReply::SmartPtr rep) {

    }

    void QuickFixHttpServer::handlePostRequest(httpServer::HttpRequest::ConstSmartPtr req, httpServer::HttpReply::SmartPtr rep) {

    }

    void QuickFixHttpServer::handlePutRequest(httpServer::HttpRequest::ConstSmartPtr req, httpServer::HttpReply::SmartPtr rep) {

    }

}
