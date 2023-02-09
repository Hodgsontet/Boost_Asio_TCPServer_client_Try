#include <iostream>
#include <latch>
#include <chrono>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/chrono.hpp>

void completn_hanlr(int num)
{   
   // printf(" timer %d  got access\n", num);
    //printf("5 seconds reached\n");
    //printf("process....\n");
    //printf(" timer %d exiting access\n", num);
      std::cout<<"timer "<<num<<"got access\n";
      std::cout<<"processing ....\n";
      std::cout<<"timer "<<num<<"exiting \n";

}
int main() {
    boost::asio::io_service io;
    auto strt =std::chrono::system_clock::now();
   // std::cout << "Hello from Boost Asio!" << std::endl;
//////TIMERWORK STUFF///////    
/* boost::asio::deadline_timer timer(io, boost::posix_time::seconds(5));
timer.async_wait([](auto vn){
  std::cout<<" 5 seconds up!!!!!\n";
});

//std::cout<< strt <<" : task processor\n";
*/

 /*boost::asio::deadline_timer timer1(io, boost::posix_time::seconds(5));
timer1.async_wait([](auto vn){
  //std::cout<<" acess!!!!!\n";
  completn_hanlr(1);
});

 boost::asio::deadline_timer timer2(io, boost::posix_time::seconds(5));
timer2.async_wait([](auto vn){
  //std::cout<<" 5 seconds up!!!!!\n";
  completn_hanlr(2);
});

*//////////////////////

io.post([]()
{
   for(int i = 0; i<2000000;i++)
    {
        
        printf("[work]\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1));;
    }
});
io.post([]()
{
    for(int i = 0; i<2000000;i++)
    {
        std::cout<<'\t';
        std::cout<<'\t';
        printf("{job2work}\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
});
 
 io.post([]()
{
    for(int i = 0; i<5000000;i++)
    {
        std::cout<<'\t';
        std::cout<<'\t';
        std::cout<<'\t';
        printf("|job3work|\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
});

std::latch m_latch(3);
std::thread t([&](){
   
printf("thread 1 ariving and waiting...\n\n");
 m_latch.arrive_and_wait();
io.run();

});
std::thread t1([&](){
printf("thread 2 ariving and waiting...\n\n");
 m_latch.arrive_and_wait();
    io.run();
    
    });

std::thread t3([&](){
printf("thread 3 ariving and waiting...\n\n");
 m_latch.arrive_and_wait();
    io.run();
    
    });

t.join();
t1.join();
t3.join();
auto end =std::chrono::system_clock::now();
 auto tme = std::chrono::duration_cast<std::chrono::seconds>(end-strt);
std::cout<<tme.count()<<  " : done.\n";

return 0;
}