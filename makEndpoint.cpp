#include<boost/asio.hpp>
#include <bits/stdc++.h>


using namespace std;
using namespace boost;
int main(int argc, char const *argv[])
{
	//****************client end point
	system::error_code ec;
	asio::io_service ios;
	// create an endpoint
	//auto will probably resolve to type boost::asio::ip::address
	auto  address = asio::ip::address::from_string("93.184.216.34", ec);

	// check that ec isnt throwing an exception ill ignore for now
	/*  endpoint can be made in three ways
    1. ip::tcp::endpoint()
    2. ip::tcp::endpoint(protocol,port) used by servers to specify protocol  and port
    3. ip::tcp::endpoint(addr,port) used by clients to connect to a spot
	we can also use dns resolver to resolve a website to an ip well looka t that later

	*/

	auto port = 80;

	 asio::ip::tcp::endpoint ep(address, port);
 cout << ep.address().to_string() << ":" << ep.port(); 
 asio::ip::tcp::socket sock(ios);
   sock.open(asio::ip::tcp::v4() ,ec);
   if(ec.value() != 0) {
 // Failed to open the socket.
 cout<< "Failed to open the socket! Error code = "<< ec.value() << ". Message: " << ec.message();
 return ec.value();
 }
   // passive sockets are the same exceptin boost the are 
   //called acceptors		

 //<< "/" << ep.protocol() << '\n';
	 //******************server endpoint ***********
     // endpoint becomes generic any

 //*******************creating sockets************//
/*boost acts as a wrapper for the berckley sockets api but still 
utilizes similar techniques 
   assign(protocol,socket): This function assigns a raw (native) socket to 
this socket instance. Use it when dealing with legacy code (that is, the native 
sockets are already created).

• open(protocol): This function opens a socket with the given IP protocol 
(v4 or v6). You'll use this mainly for UDP/ICMP sockets, or for server sockets.

• bind(endpoint): This function binds to this address.

• connect(endpoint): This function synchronously connects to the address.

• async_connect(endpoint): This function asynchronously connects to 
the address.

• is_open(): This function returns true if the socket is open.

• close(): This function closes the socket. Any asynchronous operations 
on this socket are canceled immediately and will complete with 
error::operation_aborted error code.

• shutdown(type_of_shutdown): This function disables send operations, 
receive operations, or both, starting now.

• cancel(): This function cancels all asynchronous operations on this socket. 
The asynchronous operations on this socket will all finish immediately with 
the error::operation_aborted error code.*/
	return 0;
}