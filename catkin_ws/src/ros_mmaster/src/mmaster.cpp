#include "ros/ros.h"
#include <string>
#include <boost/thread.hpp>
#include <map>
#include <sstream>
#include "XmlRpc.h"
#include "../include/ros_mmaster/mmasternode.h"

#define DEBUG

using namespace std;
using namespace XmlRpc;

bool thread_exit;
MMasterNode mmaster;
XmlRpcServer s;

// Function to solve names requisitions
void resolve_names(void)
{

boost::posix_time::seconds workTime(5);  

// Wait a requisition
//while(thread_exit == false)
//{
  cout << "resolve: Executing thread to solve names ..." << endl; 
//  boost::this_thread::sleep(workTime);

  XmlRpc::setVerbosity(1);

#ifdef DEBUG
  cout << "resolve: MMaster port: " << mmaster.port << endl;
#endif

  s.bindAndListen(mmaster.port);

  s.work(-1.0);

/*  

  if (message == "quit")
  // TODO
  // if a mmaster node has quit then ...
  // update mmaster next and prev address

  if (message == "solve")
  // TODO
  // consult internal table
    if (haveResult)
      // TODO
      // send a reply with result
    else 
      {
      // TODO
      // consult other masters
      if (should_i_know)
        //TODO
        // i am responsible by the result but a i dont have info
        // send reply to centralized Master node        
        // get info
      else
        // forward requisition to another mmaster node
        // get info
      // now i have the necessary info
      // send a reply with result
      }
*/

//}

}
// End of resolve_names function


// No arguments, result is "Hello".
class Hello : public XmlRpcServerMethod
{
public:
  Hello(XmlRpcServer* s) : XmlRpcServerMethod("Hello", s) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result)
  {
    result = "Hello";
  }

  std::string help() { return std::string("Say hello"); }

} hello(&s);    // This constructor registers the method with the server


// One argument is passed, result is "Hello, " + arg.
class HelloName : public XmlRpcServerMethod
{
public:
  HelloName(XmlRpcServer* s) : XmlRpcServerMethod("HelloName", s) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result)
  {
    std::string resultString = "Hello, ";
    resultString += std::string(params[0]);
    result = resultString;
  }
} helloName(&s);


// Original sample code by XmlRPC++
// http://xmlrpcpp.sourceforge.net/faq.html
class Sum : public XmlRpcServerMethod
{
public:
  Sum(XmlRpcServer* s) : XmlRpcServerMethod("Sum", s) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result)
  {
    int nArgs = params.size();
    double sum = 0.0;
    for (int i=0; i<nArgs; ++i)
      sum += double(params[i]);
    result = sum;
  }
} sum(&s);


//TODO
class setPrevious : public XmlRpcServerMethod
{
public:
  setPrevious(XmlRpcServer* s) : XmlRpcServerMethod("setPrevious", s) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result)
  {
    int nArgs = params.size();
    double sum = 0.0;
    for (int i=0; i<nArgs; ++i)
      sum += double(params[i]);
    result = sum;
  }
} set_previous(&s);


int main(int argc, char **argv)
{

//  XmlRpc::setVerbosity(5);

//  s.bindAndListen(3333);

//exit(1);

  ros::init(argc, argv, "mmaster");

  mmaster.host = "localhost";
  mmaster.port = (rand() % 64512) + 1024;    // choose a random a port between 1024 and 65536
																																													// ports below 1024 requires root privileges and
 																																												// max port number is 65536
  ros::NodeHandle node_handle;
  string mmaster_addresses;

  if (node_handle.hasParam("/mmaster_addresses"))
				{
    #ifdef DEBUG
    cout << "main: Existe o parâmetro /mmaster_addresses" << endl;
    #endif

    // There is another mmaster running, get their address and atach my address
	node_handle.getParam("/mmaster_addresses", mmaster_addresses);

    }

  #ifdef DEBUG
  cout << "main: mmaster_addresses before addMyAddress:" << mmaster_addresses << endl;
  #endif

  node_handle.setParam("/mmaster_addresses", mmaster.addMyAddress(mmaster_addresses));

//  boost::thread resolve_names_thread(resolve_names);

  s.bindAndListen(mmaster.port);
  s.work(-1.0);

  #ifdef DEBUG
  cout << "main: Vou entrar no laço de leitura do teclado" << endl;
  #endif

  string keyboard_input;
  
  while(true)
    {
    cin >> keyboard_input;
    if (keyboard_input == "exit")
      {
		  cout << "main: Finishing this master" << endl; 
		  break;
      }
    if (keyboard_input == "print")
      {
         mmaster.printServerInfo();
      }
    }

  thread_exit=true;

  // Get updated list from parameter server
  node_handle.getParam("/mmaster_addresses", mmaster_addresses);

  // TODO
  // send a notification to others masters to notify that i am leaving

  mmaster_addresses = mmaster.removeMyAddress(mmaster_addresses);

  if (mmaster_addresses != "")
    {
    // Remove my address from parameter server
    node_handle.setParam("/mmaster_addresses", mmaster_addresses);
    }
  else
    node_handle.deleteParam("/mmaster_addresses");

  // Finalize thread who solve names
//  resolve_names_thread.join();

  return 0;
}

