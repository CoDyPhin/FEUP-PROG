#include "Client.h"
#include "Agency.h"
#include "Packet.h"
#include "Date.h"
#include "Address.h"

Client::Client()
{
}

Client::Client(string nname, unsigned nVATnumber, unsigned short nfamilySize, Address naddress){
  
	name = nname;
	VATnumber = nVATnumber;
	familySize = nfamilySize;
	address = naddress;
	strpackets = { "" };
	totalPurchased = 0;
}

//Client::Client(string nname, unsigned nVATnumber, unsigned short nfamilySize, Address naddress, vector<Packet> & npackets, unsigned ntotalPurchased){
//  
//	name = nname;
//	VATnumber = nVATnumber;
//	familySize = nfamilySize;
//	address = naddress;
//	packets = npackets;
//	totalPurchased = ntotalPurchased;
//}

Client::Client(string nname, unsigned nVATnumber, unsigned short nfamilySize, Address naddress, vector<string> & npackets, unsigned ntotalPurchased) {

	name = nname;
	VATnumber = nVATnumber;
	familySize = nfamilySize;
	address = naddress;
	strpackets = npackets;
	totalPurchased = ntotalPurchased;
}

  // GET methods

string Client::getName() const{
  
	return name;
}
  
unsigned Client::getVATnumber() const{
  
	return VATnumber;
}

unsigned short Client::getFamilySize() const{
  
	return familySize;
}

Address Client::getAddress() const{
  
	return address;
}

//vector<Packet> Client::getPacketList() const{
//  
//	return packets;
//}

vector<string> Client::getSTRPacketList() const
{
	return strpackets;
}

unsigned Client::getTotalPurchased() const{
  
	return totalPurchased;
}
  
  // metodos SET
	  
void Client::setName(string nname){
  
	name = nname;
}

void Client::setVATnumber(unsigned nVATnumber){
  
	VATnumber = nVATnumber;
}

void Client::setFamilySize(unsigned short nfamilySize){
  
	familySize = nfamilySize;
}
void Client::setAddress(Address naddress){
  
	address = naddress;
}
//void Client::setPacketList(vector<Packet> & npackets){
//  
//	packets = npackets;
//}

void Client::setSTRPacketList(vector<string>& packets)
{
	strpackets = packets;
}
void Client::setTotalPurchased(unsigned ntotalPurchased){
  
	totalPurchased = ntotalPurchased;
}
  
  // outros metodos

ostream& operator<<(ostream& out, const Client & client){

	out << client.name;
	return out;
}
