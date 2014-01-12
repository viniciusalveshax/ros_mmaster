using namespace std;
using namespace XmlRpc;
using namespace ros;

typedef struct {
  string host;
  int port;
} address;

class MMasterNode {

private:
  address my_address, next, prev, master_address;
  std::map<string,address> topics_providers_map;
  std::map<int,string> mmaster_addresses_map;
  boost::mutex mutex_mmaster_addresses;
  bool already_add_my_address;

public:
  string addMyAddress(string);
  string removeMyAddress(string);
  string myAddress(void);
  void   printServerInfo(void);
  string hostname(void) { return my_address.host; }
  void   setHostname(string new_hostname) { my_address.host = new_hostname; }
  int    port(void)     { return my_address.port; }
  void   setPort(int new_port) { my_address.port = new_port; }
  string search(XmlRpcValue&);
  int    hashFunction(string);
  address getMMasterOwner(int);
  bool   isEqualMyAddress(address);
  bool   readAddressMaster(void);
  string masterHost(void) { return master_address.host; }
  int    masterPort(void) { return master_address.port; }
  address string2Address(string);
  bool   string2Map(string);
  bool   alreadyAddMyAddress(void) { return already_add_my_address; }
  void   alreadyAddMyAddress(bool new_setting) { already_add_my_address=new_setting; }
};


// Method that add MMaster address to mmaster addresses list
string MMasterNode::addMyAddress(string mmaster_addresses)
{

ostringstream mmaster_addresses_final;

//addresses_map.insert(std::pair<int,string>(200, "ola"));

#ifdef DEBUG
cout << "add: Conseguiu inserir elemento no map" << endl;
#endif

this->string2Map(mmaster_addresses);

if (!this->alreadyAddMyAddress())
  {

  // My address is not on the list
  // Test if a take a not used port

  while(this->mmaster_addresses_map.count(this->port()) > 0)
    {
		
    // While a take a already used port go on and takes a new one

    #ifdef DEBUG
      cout << "add: Entrou no while2: Porta já existente" << endl;
    #endif

    srand(time(NULL));
    this->setPort((rand() % 64512) + 1024); // choose a random a port between 1024 and 65536																									
										// ports below 1024 requires root privileges and 
										// max port number is 65536
    }

  cout << "add: Add my host and port to address list" << endl;
  cout << "add: Hostname: " << this->hostname() << ", port: " << this->port() << endl;

  }
  
// Insert my own hostname and port to my list
this->mmaster_addresses_map.insert(std::pair<int,string>(this->port(),this->hostname()));

if (mmaster_addresses.size() == 0)
  // If size == 0, so I am the unique master. Return my own information
  mmaster_addresses_final << this->hostname() << ":" << this->port();
else
  if (this->alreadyAddMyAddress())
    // I already add my address on previous execution
    mmaster_addresses_final << mmaster_addresses;
  else
    // This is my first execution, add my address
    mmaster_addresses_final << mmaster_addresses << ";" << this->hostname() << ":" << this->port();

// On next executions if I found a port equal my port its because it's me
this->alreadyAddMyAddress(true);

#ifdef DEBUG
cout << "add: printing map " << endl;

// Code sample from http://www.cplusplus.com/reference/map/map/begin/
for (std::map<int,string>::iterator it=mmaster_addresses_map.begin(); it!=mmaster_addresses_map.end(); ++it)
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
cout << "myAddress " << myAddress() << endl;
#endif

// Discover my address position
address_position = mmaster_addresses.find(myAddress());
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
address << this->hostname() << ":" << this->port();
return address.str();
}
// End of method myAddress


void MMasterNode::printServerInfo(void)
{
  cout << "Hostname: " << this->hostname() << endl;
  cout << "Port: " << this->port() << endl;
  
  //TODO Print internal tables too
}

string MMasterNode::search(XmlRpcValue& params)
{
  std::map<string,address>::iterator it;
  address provider_address, mmaster_owner_address;
  string topic_name;
  ostringstream provider_address_tmp;
  
  topic_name = string(params[1]);
  
  #ifdef DEBUG
      cout << "search: começando a busca por " << topic_name << endl;
  #endif
  
  it = topics_providers_map.find(topic_name);
  
  if (it != topics_providers_map.end())
  {
    // Found response in internal table
    cout << "search: Encontrei " << topic_name << " na minha tabela interna" << endl;
      
    provider_address = it->second;
    provider_address_tmp << provider_address.host << ":" << provider_address.port;
    return provider_address_tmp.str();
  }    
  
  cout << "search: Não encontrei na minha tabela interna" << endl;
  
  // get the mmaster node responsable by the topic
  mmaster_owner_address = this->getMMasterOwner(this->hashFunction(topic_name));
 
  XmlRpcValue result;  
//  XmlRpc::setVerbosity(5);
  
  // am i responsable by the topíc?
  if (this->isEqualMyAddress(mmaster_owner_address))
    {

    cout << "search: eu deveria saber a resposta. Repassando para o master" << endl;

    // yes, i am responsable, but i dont have the result
    // so, i will consult the Master node
    // TODO get master node and port
    string tmp_string = "127.0.0.1";
//    XmlRpcClient *c = XMLRPCManager::instance()->getXMLRPCClient(tmp_string, this->masterPort(), "/");
    XmlRpcClient c(tmp_string.c_str(), this->masterPort());
    c.execute("registerSubscriber", params, result);
      
    }
  else
    {

    cout << "search: eu não precisava ter a resposta, consultando outro mmaster na porta " << mmaster_owner_address.port << endl;

    // no, there is another node responsable
    // so, i will forward requisition
    XmlRpcClient *c = XMLRPCManager::instance()->getXMLRPCClient(mmaster_owner_address.host.c_str(), mmaster_owner_address.port, "/");
    c->execute("registerSubscriber", params, result);
    }
 
  address topic_owner;
   
  #ifdef DEBUG
    cout << "search: result size " << result.size() << endl;
  #endif
 
  topics_providers_map.insert(std::pair<string,address>(topic_name,string2Address(string(result[2][0]))));
    
  cout << "search: resultado da busca: " << topic_name << "->" << string(result[2][0]) << endl;
  
  return string(result[2][0]);
}

int MMasterNode::hashFunction(string topic_name)
{
  unsigned int accumulator;
  
  char* topic_name_c_str = new char[topic_name.length()+1];
    strcpy (topic_name_c_str, topic_name.c_str());

  for (int j=0, i=1; j<(topic_name.length()+1); j++, i+=1000)
  {
    accumulator+=(int)topic_name_c_str[j] * i;
  }
    
  accumulator = accumulator % 64512;
  
  accumulator+= 1024; // accumulator has a value between 1024 and 65536
  
  #ifdef DEBUG
    cout << "hashFunction: " << topic_name << "->" << accumulator << endl;
  #endif
  
  return accumulator;
}

address MMasterNode::getMMasterOwner(int hash_code) {
  std::map<int,string>::reverse_iterator myit;
  
  int responsable_port;
  
  /* Discover who is the unique mmaster that has the responsability for the hash code 
   A node has a unique port number. His port number say the hash codes he must resolve.
   He is responsable by all hashes with a value equal or higher that his own port number.
   Ex: Given the mmasters m1, m2 and m3 that have ports 2000, 40000 and 60000 respectively:
   m3 is responsible by all hashes between 60000 and 1999, m1 is responsable by 2000 until
   39999 and m2 is responsable by 40000 until 59999
  */
  
  myit=this->mmaster_addresses_map.rbegin();
  responsable_port = myit->first;
  
  for (map<int,string>::iterator it=this->mmaster_addresses_map.begin(); it!=this->mmaster_addresses_map.end(); ++it)  
  {
    if (hash_code >= it->first)
    {
      responsable_port = it->first;
    }
    if (it->first > hash_code)
      break;
  }

  address responsable_address;
  
  #ifdef DEBUG
    cout << "getMasterOwner: O responsável por " << hash_code << " é " << responsable_port << endl;
  #endif
  
  responsable_address.port = responsable_port;
  responsable_address.host = (this->mmaster_addresses_map).find(responsable_port)->second;

  return responsable_address;

}

bool MMasterNode::isEqualMyAddress(address test_address)
{
  if ( (this->my_address.host == test_address.host) && (this->my_address.port == test_address.port) )
    return true;
  else
    return false;
}

bool MMasterNode::readAddressMaster(void)
{
  char* path;
  path = getenv("ROS_MASTER_URI");
  if (path==NULL)
    return false;
  
  string rosmaster_env_string(path);
  this->master_address = string2Address(rosmaster_env_string);

  #ifdef DEBUG
    cout << "readAddressMaster: " << this->master_address.host << ' ' << this->master_address.port << endl;
  #endif

  return true;
}

address MMasterNode::string2Address(string str)
{
  int coma_position = str.find_last_of(':');
  address new_address;
  new_address.host = str.substr(0, coma_position);
  new_address.port = atoi(str.substr(coma_position+1, str.size()).c_str());
  
  #ifdef DEBUG
    cout << "string2address: Converti " << str << endl;
    cout << "string2address: em ... " << new_address.host << ' ' << new_address.port << endl;
  #endif
  
  return new_address;
}

bool MMasterNode::string2Map(string mmaster_addresses)
{

int end = 0;
int colon;
string address, tmp_hostname, tmp_mmaster_addresses;
std::pair<std::map<int,string>::iterator,bool> ret_value;
int tmp_port;
tmp_mmaster_addresses = mmaster_addresses;

#ifdef DEBUG
cout << "string2Map: mmaster_addresses: " << mmaster_addresses << "." << endl;
cout << "string2Map: mmaster_addresses size: " << mmaster_addresses.size() << endl;
#endif

this->mutex_mmaster_addresses.lock();
this->mmaster_addresses_map.clear();

while (tmp_mmaster_addresses.size() != 0)
  {

  #ifdef DEBUG
//  cout << "string2Map: Entrou no while1" << endl;
//  cout << "string2Map: mmaster_addresses" << tmp_mmaster_addresses << endl;
  #endif

  // Find mmaster_address separator
  end = tmp_mmaster_addresses.find(";");

  #ifdef DEBUG
//  cout << "string2Map: Posição do ;" << end << endl;
  #endif

  // Get first address
  address = tmp_mmaster_addresses.substr(0,end);

  #ifdef DEBUG
//  cout << "string2Map: Primeiro endereço " << address << endl;
  #endif

  // Find colon separator
  colon = address.find(":");

  #ifdef DEBUG
//  cout << "string2Map: Posição do : " << colon << endl;
  #endif

  tmp_hostname = address.substr(0, colon);
  tmp_port = atoi(address.substr(colon+1, address.size()).c_str());

  #ifdef DEBUG
//  cout << "string2Map: address de : até o fim " << address.substr(colon+1, address.size()) << endl;
//  cout << "string2Map: Hostname: " << tmp_hostname << endl;
//  cout << "string2Map: Port: " << tmp_port << endl;
  #endif

  ret_value = this->mmaster_addresses_map.insert(std::pair<int,string>(tmp_port,tmp_hostname));
  if (ret_value.second==false) {
    cout << "string2Map: A error has ocurred: cannot update mmaster addresses list" << endl;
  }

  if (end == string::npos)
    break;

  tmp_mmaster_addresses = tmp_mmaster_addresses.substr(end+1,tmp_mmaster_addresses.size());

} // end while
	 
this->mutex_mmaster_addresses.unlock();	 

return true;
	 
}
