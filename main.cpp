#include "asio_server.h"


using namespace std;

int main()
{  
    Asio_Tcp_Server<Session_Handler> s(8081);
    s.start();
    s.run();
    return 0;
}