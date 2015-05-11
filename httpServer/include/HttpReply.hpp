/* 
 * File:   HttpReply.hpp
 * Author: ankithbti
 *
 * Created on 7 May, 2015, 11:40 PM
 */

#ifndef HTTPREPLY_HPP
#define	HTTPREPLY_HPP

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <vector>
#include <boost/asio.hpp>

#include <HttpHeader.hpp>

namespace httpServer
{

const char name_value_separator[] = {':', ' '};
const char crlf[] = {'\r', '\n'};

class HttpReply : private boost::noncopyable
{
public:
    typedef boost::shared_ptr<HttpReply> SmartPtr;
    typedef boost::shared_ptr<const HttpReply> ConstSmartPtr;

    /// The status of the reply.

    enum status_type
    {
        ok = 200,
        created = 201,
        accepted = 202,
        no_content = 204,
        multiple_choices = 300,
        moved_permanently = 301,
        moved_temporarily = 302,
        not_modified = 304,
        bad_request = 400,
        unauthorized = 401,
        forbidden = 403,
        not_found = 404,
        internal_server_error = 500,
        not_implemented = 501,
        bad_gateway = 502,
        service_unavailable = 503
    } _status;

    /// The headers to be included in the reply.
    std::vector<HttpHeader::SmartPtr> _headers;

    /// The content to be sent in the reply.
    std::string _content;

    /// Convert the reply into a vector of buffers. The buffers do not own the
    /// underlying memory blocks, therefore the reply object must remain valid and
    /// not be changed until the write operation has completed.
    std::vector<boost::asio::const_buffer> to_buffers();

    /// Get a stock reply.
    static void stock_reply(status_type status, HttpReply::SmartPtr);


};
}

#endif	/* HTTPREPLY_HPP */

