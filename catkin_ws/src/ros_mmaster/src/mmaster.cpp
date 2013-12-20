#include "ros/ros.h"
#include "string"
#include <boost/thread.hpp>
#include <map>
#include <sstream>

using namespace std;

bool thread_exit;

class MMasterNode {

public:
  string host;
  int port;

string addMyAddress(string);
string removeMyAddress(string);
string myAddress(void);

};

// Method that add MMaster address to mmaster addresses list
string MMasterNode::addMyAddress(string mmaster_addresses)
{
int end = 0;
std::map<int,string> addresses_map;
int colon;
string address, tmp_hostname;
std::pair<std::map<int,string>::iterator,bool> ret_value;
int tmp_port;

while (mmaster_addresses != "")
  {

  // Find mmaster_address separator
	 end = mmaster_addresses.find_first_of(";");

  // Get first address
  address = mmaster_addresses.substr(0,end);

  // Find colon separator
  colon = address.find_first_of(":");

  tmp_hostname = address.substr(0, colon-1);
  tmp_port = atoi(address.substr(colon, address.size()).c_str());

  ret_value = addresses_map.insert(std::pair<int,string>(tmp_port,tmp_hostname));
  if (ret_value.second==false) {
    cout << "A error has ocurred: cannot update mmaster addresses list" << endl;
  }

	 if (end == string::npos)
	   break;

	 mmaster_addresses = mmaster_addresses.substr(end+1,mmaster_addresses.size());

	 }

while(addresses_map.count(this->port) > 0)
  {
  this->port = (rand() % 64512) + 1024; // choose a random a port between 1024 and 65536
																																								// ports below 1024 requires root privileges and
 																																							// max port number is 65536
  }

addresses_map.insert(std::pair<int,string>(this->port,this->host));

cout << "Add my host and port to address list";
cout << "Hostname: " << this->host << ", port: " << this->port << endl;

}
// End of method addMyAddress


// Method that remove MMaster address to mmaster addresses list
string MMasterNode::removeMyAddress(string mmaster_addresses)
{
int address_position, coma_position;
string before_addresses, after_addresses;

// Discover my address position
address_position = mmaster_addresses.find_first_of(MMasterNode::myAddress());

// Get addresses before my address
before_addresses = mmaster_addresses.substr(0, address_position-1);

// Get next address separator after my address. The separator is a ';'
coma_position    = mmaster_addresses.find_first_of(";", address_position+1);

// Get addresses after my address
after_addresses  = mmaster_addresses.substr(coma_position+1, mmaster_addresses.size());

return before_addresses+after_addresses;

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



// Function to solve names requisitions
void resolve_names(void)
{

boost::posix_time::seconds workTime(5);  

// Wait a requisition
while(thread_exit == false)
{
  cout << "Executing thread to solve names ..." << endl; 
  boost::this_thread::sleep(workTime);

}

}
// End of resolve_names function


int main(int argc, char **argv)
{

  ros::init(argc, argv, "mmaster");

  MMasterNode mmaster;
  mmaster.host = "localhost";
  mmaster.port = (rand() % 64512) + 1024; // choose a random a port between 1024 and 65536
																																													// ports below 1024 requires root privileges and
 																																												// max port number is 65536
  ros::NodeHandle node_handle;
  string mmaster_addresses;
  if (node_handle.hasParam("/mmaster_addresses"))
				{
    // There is another mmaster running, get their address and atach my address
				node_handle.getParam("/mmaster_addresses", mmaster_addresses);
    }

  node_handle.setParam("/mmaster_addresses", mmaster.addMyAddress(mmaster_addresses));

  boost::thread resolve_names_thread(resolve_names);

  string keyboard_input;
  while(1)
    {
    cin >> keyboard_input;
    if (keyboard_input == "exit")
      {
      cout << "Finishing this master" << endl;
    	 break;
      }
    }

  thread_exit=true;

  // Get updated list from parameter server
		node_handle.getParam("/mmaster_addresses", mmaster_addresses);

  // Remove my address from parameter server
  node_handle.setParam("/mmaster_addresses", mmaster.removeMyAddress(mmaster_addresses));

  // Finalize thread who solve names
  resolve_names_thread.join();

  return 0;
}

