#include "common_libraries.h"
#include "session_handler.h"

// g++-11 asioTry.cpp -std=c++2a -L /usr/lib/ -lboost_system -lboost_thread -lpthread -lboost_system -lboost_chrono

template<typename handler>
class Asio_Tcp_Server
{
public:

  Asio_Tcp_Server(int prt) : port(prt),io_queue(), soc_acceptor(io_queue){}
void handle_new_session(std::shared_ptr<handler>new_sesh, const boost::system::error_code&  error)
{
  std::cout<<"handling new session\n";
    if(error)
    {
      std::cout<<"error detected session\n";
      std::cout<<error.message()<<'\n';
        return;
    }
        new_sesh->start();
        std::cout<<"making shared ptr to handle new sesh \n";
        std::shared_ptr<handler> sesh_handl = std::make_shared<handler>(io_queue);
        std::cout<<"calling async accept \n";
        soc_acceptor.async_accept(sesh_handl->socket(),  
                                  [=](const boost::system::error_code& ec)
                                  {
                                    handle_new_session(sesh_handl,ec);
                                  }      
                                        
                             );  

}
 // add threads later
   void start()
   {
    std::shared_ptr<handler> session = std::make_shared<handler>(io_queue);
     boost::asio::ip::address address = boost::asio::ip::address::from_string("127.0.0.1");

    boost::asio::ip::tcp::endpoint ep(address,port);
    boost::system::error_code ec;
    soc_acceptor.open(ep.protocol(),ec);
    soc_acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    
    soc_acceptor.bind(ep,ec);

    if (ec)
{
  std::cout<<"bind error caught\n";
  std::cout<<ec.message()<<'\n';
  return;
}
else
{
    soc_acceptor.listen();
    std::cout<<"posting async accept\n";
    soc_acceptor.async_accept(session->socket(),  
                                  [=](const boost::system::error_code& ec)
                                  {
                                    handle_new_session(session,ec);
                                    std::cout<<"accepted";
                                  }      
                                        
                                        );
  
}
      // the session contains a popinter that takes care of the connection with tha client
            
   }
  
   void run()
   {
    io_queue.run();
    soc_acceptor.close();
   }
private:
int port;
boost::asio::io_context io_queue;
boost::asio::ip::tcp::acceptor soc_acceptor; 

//add thread pool   

};
