//#define DEBUG

#include "ros/ros.h"
#include <string>
#include <map>
#include <sstream>
#include "XmlRpc.h"
#include "ros/xmlrpc_manager.h"
#include "../include/ros_mmaster/mmasternode.h"
#include <boost/thread.hpp>

using namespace std;
using namespace XmlRpc;

MMasterNode mmaster;
XmlRpcServer s;


class registerSubscriber : public XmlRpcServerMethod
{
public:
  registerSubscriber(XmlRpcServer* s) : XmlRpcServerMethod("registerSubscriber", s) {}

  void execute(XmlRpcValue& params, XmlRpcValue& result)
  {
    string keyboard_input, str_result;
    int nArgs = params.size();
    cout << "nargs " << nArgs;
    for (int i=0; i<nArgs; ++i)
      cout << "registerSubscriber " << params[i] << endl;
    //result = params[0];
    //cin >> keyboard_input;
    
    #ifdef DEBUG
      cout << "execute: chamando search" << endl;
    #endif
    
//    cin >> str_result;
    str_result = mmaster.search(params);

    

    #ifdef DEBUG
      cout << "execute: resultado da busca" << str_result << endl;
    #endif
    
    std::vector<XmlRpcValue> arrValues;
    
    XmlRpcValue v1, v2, v3;
    
    v1 = 1;
    v2 = "ola";
    v3 = str_result;
    
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

void xml_rpc_server_listen(void) {
  s.bindAndListen(mmaster.port());
  s.work(-1.0);
}

int main(int argc, char **argv)
{

  ros::init(argc, argv, "mmaster", ros::init_options::AnonymousName);

  if (!mmaster.readAddressMaster())
  {
	cout << "There is no ROS_MASTER environment variable. Exiting ..." << endl;
	exit(1);
  }

  mmaster.setHostname("localhost");
  
  srand(time(NULL));
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

  boost::thread xml_rpc_server_thread(xml_rpc_server_listen);

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

  // Shutdown XML RPC Server
  s.shutdown();

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
    // I am the last server, remove the param
    node_handle.deleteParam("/mmaster_addresses");

  return 0;
}

