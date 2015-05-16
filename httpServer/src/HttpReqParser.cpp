#include <HttpReqParser.hpp>
#include <string>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

namespace httpServer
{

HttpReqParser::HttpReqParser() : _state(method_start), _contentLength(0)
{

}

bool HttpReqParser::is_char(int c)
{
    return c >= 0 && c <= 127;
}

HttpReqParser::result_type HttpReqParser::consume(HttpRequest::SmartPtr req, char input)
{
    //std::cout << " State: " << _state << std::endl;
    switch (_state)
    {
    case method_start:
        if (!is_char(input) || is_ctl(input) || is_tspecial(input))
        {
            return bad;
        }
        else
        {
            _state = method;
            req->_method.push_back(input);
            return indeterminate;
        }
        break;
    case method:
        if (input == ' ')
        {
            _state = uri;
            return indeterminate;
        }
        else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
        {
            return bad;
        }
        else
        {
            req->_method.push_back(input);
            return indeterminate;
        }
        break;
    case uri:
        if (input == ' ')
        {
            _state = http_version_h;
            return indeterminate;
        }
        else if (is_ctl(input))
        {
            return bad;
        }
        else
        {
            req->_uri.push_back(input);
            return indeterminate;
        }
        break;
    case http_version_h:
        if (input == 'H')
        {
            _state = http_version_t_1;
            return indeterminate;
        }
        else
        {
            return bad;
        }
        break;
    case http_version_t_1:
        if (input == 'T')
        {
            _state = http_version_t_2;
            return indeterminate;
        }
        else
        {
            return bad;
        }
        break;
    case http_version_t_2:
        if (input == 'T')
        {
            _state = http_version_p;
            return indeterminate;
        }
        else
        {
            return bad;
        }
        break;
    case http_version_p:
        if (input == 'P')
        {
            _state = http_version_slash;
            return indeterminate;
        }
        else
        {
            return bad;
        }
        break;
    case http_version_slash:
        if (input == '/')
        {
            req->_httpMajorVersion = 0;
            req->_httpMinorVersion = 0;
            _state = http_version_major_start;
            return indeterminate;
        }
        else
        {
            return bad;
        }
        break;
    case http_version_major_start:
        if (is_digit(input))
        {
            req->_httpMajorVersion = req->_httpMajorVersion * 10 + input - '0';
            _state = http_version_major;
            return indeterminate;
        }
        else
        {
            return bad;
        }
        break;
    case http_version_major:
        if (input == '.')
        {
            _state = http_version_minor_start;
            return indeterminate;
        }
        else if (is_digit(input))
        {
            req->_httpMajorVersion = req->_httpMajorVersion * 10 + input - '0';
            return indeterminate;
        }
        else
        {
            return bad;
        }
        break;
    case http_version_minor_start:
        if (is_digit(input))
        {
            req->_httpMinorVersion = req->_httpMinorVersion * 10 + input - '0';
            _state = http_version_minor;
            return indeterminate;
        }
        else
        {
            return bad;
        }
        break;
    case http_version_minor:
        if (input == '\r')
        {
            _state = expecting_newline_1;
            return indeterminate;
        }
        else if (is_digit(input))
        {
            req->_httpMinorVersion = req->_httpMinorVersion * 10 + input - '0';
            return indeterminate;
        }
        else
        {
            return bad;
        }
        break;
    case expecting_newline_1:
        if (input == '\n')
        {
            _state = header_line_start;
            return indeterminate;
        }
        else
        {
            return bad;
        }
        break;
    case header_line_start:
        if (input == '\r')
        {
            _state = expecting_newline_3;
            return indeterminate;
        }
        else if (!req->_headers.empty() && (input == ' ' || input == '\t'))
        {
            _state = header_lws;
            return indeterminate;
        }
        else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
        {
            return bad;
        }
        else
        {
            req->_headers.push_back(HttpHeader::SmartPtr(new HttpHeader()));
            req->_headers.back()->_name.push_back(input);
            _state = header_name;
            return indeterminate;
        }
        break;
    case header_lws:
        if (input == '\r')
        {
            _state = expecting_newline_2;
            return indeterminate;
        }
        else if (input == ' ' || input == '\t')
        {
            return indeterminate;
        }
        else if (is_ctl(input))
        {
            return bad;
        }
        else
        {
            _state = header_value;
            req->_headers.back()->_value.push_back(input);
            return indeterminate;
        }
        break;
    case header_name:
        if (input == ':')
        {
            _state = space_before_header_value;
            return indeterminate;
        }
        else if (!is_char(input) || is_ctl(input) || is_tspecial(input))
        {
            return bad;
        }
        else
        {
            req->_headers.back()->_name.push_back(input);
            return indeterminate;
        }
        break;
    case space_before_header_value:
        if (input == ' ')
        {
            _state = header_value;
            return indeterminate;
        }
        else
        {
            return bad;
        }
        break;
    case header_value:
        if (input == '\r')
        {
            _state = expecting_newline_2;
            return indeterminate;
        }
        else if (is_ctl(input))
        {
            return bad;
        }
        else
        {
            req->_headers.back()->_value.push_back(input);
            return indeterminate;
        }
        break;
    case expecting_newline_2:
        if (input == '\n')
        {
            _state = header_line_start;
            return indeterminate;
        }
        else
        {
            return bad;
        }
        break;
    case expecting_newline_3:
        if (input == '\n')
        {

            BOOST_FOREACH(HttpHeader::SmartPtr header, req->_headers)
            {
                if (boost::iequals(header->_name, "Content-Length"))
                {
                    _contentLength = boost::lexical_cast<int>(header->_value);
                }
            }
            if (_contentLength > 0)
            {
                _state = content_start;
                return indeterminate;
            }
            else
            {
                return good;
            }
        }
        else
        {
            return bad;
        }
        break;
    case content_start:
        //std::cout << " In Content Start: " << input << std::endl;
        if (_contentLength > 0)
        {
            req->_PostData.push_back(input);
            --_contentLength;
        }
        else
        {
            return good;
        }
        _state = read_content;
        return indeterminate;
        break;
    case read_content:
        //std::cout << " In read content len: " << _contentLength << " , Data: " << req->_PostData << std::endl;
        if (_contentLength > 1)
        {
            req->_PostData.push_back(input);
            --_contentLength;
            return indeterminate;
        }
        else if (_contentLength > 0)
        {
            req->_PostData.push_back(input);
            --_contentLength;
            return good;
        }
        else
        {
            return good;
        }
        break;
    default:
        return bad;
    }
}

bool HttpReqParser::is_ctl(int c)
{
    return (c >= 0 && c <= 31) || (c == 127);
}

bool HttpReqParser::is_digit(int c)
{
    return c >= '0' && c <= '9';
}

bool HttpReqParser::is_tspecial(int c)
{
    switch (c)
    {
    case '(': case ')': case '<': case '>': case '@':
    case ',': case ';': case ':': case '\\': case '"':
    case '/': case '[': case ']': case '?': case '=':
    case '{': case '}': case ' ': case '\t':
        return true;
    default:
        return false;
    }
}

void HttpReqParser::reset()
{
    _state = method_start;
}

}
