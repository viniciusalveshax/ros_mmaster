#include "ros/ros.h"
#include "string"
#include <boost/thread.hpp>
#include <map>
#include <sstream>
#include "XmlRpc.h"

#define DEBUG

using namespace std;
using namespace XmlRpc;

class MMasterNode {

public:
  string host;
  int port;

string addMyAddress(string);
string removeMyAddress(string);
string myAddress(void);
void   printServerInfo(void);

};


bool thread_exit;
MMasterNode mmaster;
XmlRpcServer s;


// Method that add MMaster address to mmaster addresses list
string MMasterNode::addMyAddress(string mmaster_addresses)
{
int end = 0;
std::map<int,string> addresses_map;
int colon;
string address, tmp_hostname, tmp_mmaster_addresses;
std::pair<std::map<int,string>::iterator,bool> ret_value;
int tmp_port;
ostringstream mmaster_addresses_final;


#ifdef DEBUG
cout << "add: mmaster_addresses: " << mmaster_addresses << "." << endl;
cout << "add: mmaster_addresses size: " << mmaster_addresses.size() << endl;
#endif

tmp_mmaster_addresses = mmaster_addresses;

while (tmp_mmaster_addresses.size() != 0)
  {

  #ifdef DEBUG
  cout << "add: Entrou no while1" << endl;
  cout << "add: mmaster_addresses" << tmp_mmaster_addresses << endl;
  #endif

  // Find mmaster_address separator
  end = tmp_mmaster_addresses.find_first_of(";");

  #ifdef DEBUG
  cout << "add: Posição do ;" << end << endl;
  #endif

  // Get first address
  address = tmp_mmaster_addresses.substr(0,end);

  #ifdef DEBUG
  cout << "add: Primeiro endereço " << address << endl;
  #endif

  // Find colon separator
  colon = address.find_first_of(":");

  #ifdef DEBUG
  cout << "add: Posição do : " << colon << endl;
  #endif

  tmp_hostname = address.substr(0, colon);
  tmp_port = atoi(address.substr(colon+1, address.size()).c_str());

  #ifdef DEBUG
  cout << "add: address de : até o fim " << address.substr(colon+1, address.size()) << endl;
  cout << "add: Hostname: " << tmp_hostname << endl;
  cout << "add: Port: " << tmp_port << endl;
  #endif

  ret_value = addresses_map.insert(std::pair<int,string>(tmp_port,tmp_hostname));
  if (ret_value.second==false) {
    cout << "add: A error has ocurred: cannot update mmaster addresses list" << endl;
  }

	 if (end == string::npos)
	   break;

	 tmp_mmaster_addresses = tmp_mmaster_addresses.substr(end+1,tmp_mmaster_addresses.size());

	 } // end while

//addresses_map.insert(std::pair<int,string>(200, "ola"));

#ifdef DEBUG
cout << "add: Conseguiu inserir elemento no map" << endl;
#endif

while(addresses_map.count(this->port) > 0)
  {

  #ifdef DEBUG
  cout << "add: Entrou no while2: Porta já existente" << endl;
  #endif

  this->port = (rand() % 64512) + 1024; // choose a random a port between 1024 and 65536																									
										// ports below 1024 requires root privileges and 
										// max port number is 65536
  }

addresses_map.insert(std::pair<int,string>(this->port,this->host));

cout << "add: Add my host and port to address list" << endl;
cout << "add: Hostname: " << this->host << ", port: " << this->port << endl;

if (mmaster_addresses.size() == 0)
  mmaster_addresses_final << this->host << ":" << this->port;
else
  mmaster_addresses_final << mmaster_addresses << ";" << this->host << ":" << this->port;

#ifdef DEBUG
cout << "add: printing map " << endl;
for (std::map<int,string>::iterator it=addresses_map.begin(); it!=addresses_map.end(); ++it)
    std::cout << "add: " << it->first << " => " << it->second << endl;
#endif

return mmaster_addresses_final.str();

}
// End of method addMyAddress


// Method that remove MMaster address to mmaster addresses list
string MMasterNode::removeMyAddress(string mmaster_addresses)
{
int address_position, coma_position;
string before_addresses, after_addresses;

#ifdef DEBUG
cout << "myAddress " << mmaster.myAddress() << endl;
#endif

// Discover my address position
address_position = mmaster_addresses.find(mmaster.myAddress());
#ifdef DEBUG
cout << "address position " << address_position << endl;
#endif

// Get addresses before my address
before_addresses = mmaster_addresses.substr(0, address_position-1);
#ifdef DEBUG
cout << "before_addresses " << before_addresses << endl;
#endif

// Get next address separator after my address. The separator is a ';'
coma_position    = mmaster_addresses.find(";", address_position+1);

if (coma_position == -1) //So my address is the last
  {
  #ifdef DEBUG
  cout << "Returning before_addresses" << endl;
  #endif
  
  if (address_position == 0) // If address_position = 0 then I am the first
                             // and if the coma_position = -1 I am the last too
                             // so return a empty string
    {
	return "";
    }
  else
    {
    return before_addresses;
    }
  }

#ifdef DEBUG
cout << "coma position " << coma_position << endl;
#endif

// Get addresses after my address
after_addresses  = mmaster_addresses.substr(coma_position+1, mmaster_addresses.size());
#ifdef DEBUG
cout << "after_addresses " << after_addresses << endl;
#endif

if (address_position == 0) // So my address is the first
  {
  #ifdef DEBUG
  cout << "Returning after_addresses" << endl;
  #endif
  return after_addresses;
  }

#ifdef DEBUG
cout << "Returning before_addresses + after_addresses" << endl;
#endif
return before_addresses+";"+after_addresses;

}
// End of method removeMyAddress


// Method that return my address
string MMasterNode::myAddress(void)
{
ostringstream address;
address << this->host << ":" << this->port;
return address.str();
}
// End of method myAddress


void MMasterNode::printServerInfo(void)
{
  cout << "Hostname: " << this->host << endl;
  cout << "Port: " << this->port << endl;
}

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

