/* 
 * File:   HttpReqParser.hpp
 * Author: ankithbti
 *
 * Created on 7 May, 2015, 11:51 PM
 */

#ifndef HTTPREQPARSER_HPP
#define	HTTPREQPARSER_HPP

#include <boost/shared_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <boost/tuple/tuple.hpp>

#include <HttpRequest.hpp>

namespace httpServer
{

class HttpReqParser : private boost::noncopyable
{
public:
    typedef boost::shared_ptr<HttpReqParser> SmartPtr;
    typedef boost::shared_ptr<const HttpReqParser> ConstSmartPtr;

    enum result_type
    {
        good, bad, indeterminate
    };

private:

    /// The current state of the parser.

    enum state
    {
        method_start,
        method,
        uri,
        http_version_h,
        http_version_t_1,
        http_version_t_2,
        http_version_p,
        http_version_slash,
        http_version_major_start,
        http_version_major,
        http_version_minor_start,
        http_version_minor,
        expecting_newline_1,
        header_line_start,
        header_lws,
        header_name,
        space_before_header_value,
        header_value,
        expecting_newline_2,
        expecting_newline_3
    } _state;

    /// Handle the next character of input.
    result_type consume(HttpRequest::SmartPtr req, char input);

    /// Check if a byte is an HTTP character.
    static bool is_char(int c);

    /// Check if a byte is an HTTP control character.
    static bool is_ctl(int c);

    /// Check if a byte is defined as an HTTP tspecial character.
    static bool is_tspecial(int c);

    /// Check if a byte is a digit.
    static bool is_digit(int c);

public:

    HttpReqParser();
    void reset();

    template <typename InputIterator>
    boost::tuple<result_type, InputIterator> parse(HttpRequest::SmartPtr req,
                                                 InputIterator begin, InputIterator end)
    {
        while (begin != end)
        {
            result_type result = consume(req, *begin++);
            if (result == good || result == bad)
                return boost::make_tuple(result, begin);
        }
        return boost::make_tuple(indeterminate, begin);
    }
};
}


#endif	/* HTTPREQPARSER_HPP */

