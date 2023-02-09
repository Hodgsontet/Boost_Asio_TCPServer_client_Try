#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <string>
#include <iostream>
#include <boost/asio.hpp>

int main()
{
    boost::property_tree::ptree order;
   
    order.put("symbol", "dodge");
    order.put("order_type","market order");
    order.put("side","buy");
    order.put("timestamp" , "1478203017");
    order.put("delim","#");
    std::stringstream oss;
    boost::property_tree::write_json(oss, order);
     
    std::string json = oss.str();
 // std::string str = "sendingordermessge";
    std::cout << json << std::endl;
     boost::asio::io_service io_serv;
//socket creation
    boost::system::error_code error;
      boost::asio::ip::tcp::socket sock(io_serv);
       boost::asio::const_buffer buff = boost::asio::buffer(json, json.size());
       std::cout<<json.size()<<'\n';
     sock.connect(boost::asio::ip::tcp::endpoint( boost::asio::ip::address::from_string("127.0.0.1"), 8081 ));
      boost::asio::write( sock, buff , error );
     if( !error ) {
        std::cout << "order message sent succefuly!" << std::endl;
     }
     else {
        std::cout << "send failed: " << error.message() << std::endl;
     }
     ////////////////////////////////
    /*  char response[1024];
  boost::asio::read(sock, boost::asio::buffer(response, 1024));

  std::cout << response << std::endl;
*/
    return 0;
}