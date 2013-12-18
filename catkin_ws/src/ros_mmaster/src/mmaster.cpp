#include "ros/ros.h"
#include "string"
#include <boost/thread.hpp>
#include <map>

using namespace std;

class MMasterNode {
string host;
int port;

string addMyAddress(string); //TODO

};

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

cout << "Add my host and port                        xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx                                                                                                                                                                                                                                                                

}

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

  node_handle.setParam("/mmaster_addresses", mmaster.addMyAddress(mmaster_address));

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
  node_handle.setParam("/mmaster_addresses", mmaster.removeMyAddress(mmaster_address));

  // Finalize thread who solve names
  resolve_names_thread.join();

  return 0;
}

