#include "ros/ros.h"
#include <string>
#include <map>
#include <sstream>
#include "XmlRpc.h"
#include "../include/ros_mmaster/mmasternode.h"

#define DEBUG

using namespace std;
using namespace XmlRpc;

MMasterNode mmaster;
XmlRpcServer s;

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

class registerSubscriber : public XmlRpcServerMethod
{
public:
  registerSubscriber(XmlRpcServer* s) : XmlRpcServerMethod("registerSubscriber", s) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result)
  {
    string keyboard_input;
    int nArgs = params.size();
    cout << "nargs " << nArgs;
    for (int i=0; i<nArgs; ++i)
      cout << "registerSubscriber " << params[i] << endl;
    //result = params[0];
    //cin >> keyboard_input;
    
    std::vector<XmlRpcValue> arrValues;
    
    XmlRpcValue v1, v2, v3;
    
    v1 = 1;
    v2 = "ola";
    cin >> keyboard_input;
    v3 = keyboard_input;
    
    arrValues.push_back(v1);
    arrValues.push_back(v2);
    arrValues.push_back(v3);

    result[0] = v1;
    result[1] = v2;
    result[2][0] = v3;
    
  }
} register_subscriber(&s);

/*
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
*/

int main(int argc, char **argv)
{

  ros::init(argc, argv, "mmaster");

  mmaster.setHostname("localhost");
  mmaster.setPort((rand() % 64512) + 1024);    // choose a random a port between 1024 and 65536																																									// ports below 1024 requires root privileges and
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

  
//  XmlRpc::setVerbosity(3);

  s.bindAndListen(mmaster.port());
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

  return 0;
}

