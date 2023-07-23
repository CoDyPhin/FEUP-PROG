#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"
#include "Address.h"
#include "Client.h"
#include "Packet.h"

using namespace std;

class Agency{
 private:
  string name; // name of the  agency
  unsigned int VATnumber; // VAT number of the agency
  Address address; // address of the agency
  string URL; // URL of the agency Web site
  vector<Client> clients; // vector to store the existing clients
  vector<Packet> packets; // vector to store the existing packets
  
  string clientsFile; // clients file, needed for updating
  string packetsFile; // packets file, need for updating

  unsigned short int clientsInfoHasChanged; // flag that is set to "1" if at least one client has been changed/added/deleted
  unsigned short int packetsInfoHasChanged; // flag that is set to "1" if at least one packet has been changed/added/deleted
  unsigned int maxClientsId; // maximum value among all clients identifiers
  unsigned int maxPacketsId; // maximum value among all packets identifiers

 public:
  Agency(string fileName);

  // methods GET
  string getName() const;
  unsigned getVATnumber() const;
  Address getAddress() const;
  string getURL() const;
  vector<Client> getClients() const;
  vector<Packet> getPackets() const;

  string getClientsFile() const;
  string getPacketsFile() const;
  bool getClientInfoHasChanged() const;
  bool getPacketsInfoHasChanged() const;

  
  // methods SET
  void setName(string name);
  void setVATnumber(unsigned VATnumber);
  void setAddress(Address address);
  void setURL(string url);
  void setClients(vector<Client> & clients);
  void setPackets(vector<Packet> & packets);

  void setClientsFile(string clientfile);
  void setPacketsFile(string packetfile);
  void setClientInfoHasChanged(bool clientinfochanged);
  void setPacketsInfoHasChanged(bool packetinfochanged);

  // other methods */
  
  friend ostream& operator<<(ostream& out, const Agency & agency);

};
