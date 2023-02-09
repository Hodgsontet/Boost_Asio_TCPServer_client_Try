#include "common_libraries.h"

class Session_Handler : public std::enable_shared_from_this<Session_Handler> {
public:

   Session_Handler(boost::asio::io_service& service)
: task_queue(service) ,session_soc(service), write_strand(service) {
    
}
void start()
{
  std::cout<<"starting session handler \n";
    async_read_until(session_soc,
                    data,
                    '\0',
                    [me = shared_from_this()]( boost::system::error_code const & ec, std::size_t bytes_transferred)
                    { 
                           me->read_handlr(ec,bytes_transferred);
                    }

    );
    
}
void read_handlr(boost::system::error_code const & ec, std::size_t bytes_transferred)
{
   /*if(ec)
    {   std::cout<<"error read error detected\n";
        std::cout<<ec.message()<<'\n';
      return;}*/

//std::cout<<"no error detected in read handler \n";
//std::cout<<ec.message()<<'\n';
 std::istream str(&data);
 std::string packet;
 
//std::cout<<"printing packets\n";
  std::getline(str,packet);
 // std::cout<<"packet size: "<<packet.size()<<'\n';
  
 if( (packet.size()==1) )
 {
  std::cout<<all_data.str();
  std::cout<<"all data\n";
    
 }
 else {
  all_data<<packet;
 }
 
 
 /*else
 {
  std::cout<<bytes_transferred<<" :bytes transfered\n";
   std::cout<<"packets empty\n";
 }*/
 

  async_read_until(session_soc,
                    data,
                    '#',
                    [me = shared_from_this()]( boost::system::error_code const & ec, std::size_t bytes_transferred)
                    { 
                           me->read_handlr(ec,bytes_transferred);
                    }

    );


}

boost::asio::ip::tcp::socket& socket()
{
      return session_soc;
}

private:
boost::asio::io_service& task_queue;
boost::asio::io_service::strand write_strand;
boost::asio::ip::tcp::socket session_soc;
boost::asio::streambuf data;
std::ostringstream all_data;
};