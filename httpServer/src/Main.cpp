#include <iostream>
#include <Add.hpp>

#include <HttpServer.hpp>

int main()
{
    Add obj;
    std::cout << " Add 2 + 3 = " << obj.add(2, 3) << std::endl;
    std::string port("1234");
    std::string docRoot("/Users/ankithbti/Development/Cpp");
    httpServer::HttpServer server(port, docRoot);
    server.start();

    try
    {
        while (true)
        {
            boost::this_thread::sleep(boost::posix_time::seconds(1));
        }
    }catch(const boost::thread_interrupted& err){
        std::cout << " Stopping the Server. " << std::endl ;
    }
    
    server.stop();

    return 0;
}
