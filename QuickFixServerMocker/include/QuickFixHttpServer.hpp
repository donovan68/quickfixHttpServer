/* 
 * File:   QuickFixHttpServer.hpp
 * Author: ankithbti
 *
 * Created on 7 June, 2015, 8:04 PM
 */

#ifndef QUICKFIXHTTPSERVER_HPP
#define	QUICKFIXHTTPSERVER_HPP

#include <HttpReqHandlerInterface.hpp>
#include <Application.h>

namespace qfHttpServer {

    class QuickFixHttpServer : public httpServer::HttpReqHandlerInterface {
    public:
        typedef boost::shared_ptr<QuickFixHttpServer> SmartPtr;

    private:
        Application &_application;
    public:

        explicit QuickFixHttpServer(const std::string& docRoot, Application& app) : httpServer::HttpReqHandlerInterface(docRoot), _application(app) {

        }

        virtual void handleGetRequest(httpServer::HttpRequest::ConstSmartPtr req, httpServer::HttpReply::SmartPtr rep);
        virtual void handlePostRequest(httpServer::HttpRequest::ConstSmartPtr req, httpServer::HttpReply::SmartPtr rep);
        virtual void handlePutRequest(httpServer::HttpRequest::ConstSmartPtr req, httpServer::HttpReply::SmartPtr rep);
        virtual void handleDeleteRequest(httpServer::HttpRequest::ConstSmartPtr req, httpServer::HttpReply::SmartPtr rep);



    };


}

#endif	/* QUICKFIXHTTPSERVER_HPP */

