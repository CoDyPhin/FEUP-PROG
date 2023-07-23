#pragma once

#include <iostream>
#include <string>
#include <vector>


#include "defs.h"
#include "Date.h"

using namespace std;

class Packet{
 private:
  int id; // packet unique identifier
  vector<string> sites; // touristic sites to visit
  Date begin;  // begin date
  Date end;  // end date
  double pricePerPerson; // price per person
  unsigned maxPersons; // max slots
  unsigned soldTickets; // number of sold tickets
  
 public:
  Packet();
  Packet(int id, vector<string> sites, Date begin, Date end, double pricePerPerson, unsigned maxPersons, unsigned soldTickets);

  // GET methods
  int getId() const;
  vector<string> getSites() const;
  Date getBeginDate() const;
  Date getEndDate() const;
  double getPricePerPerson() const;
  unsigned getMaxPersons() const;
  unsigned getSoldTickets() const;

  // SET methods
  void setId(int id);  // to set negatve if "deprecated"
  void setSites(vector<string> sites);
  void setBeginDate(Date begin);
  void setEndDate(Date end);
  void setPricePerPerson(double pricePerPerson);
  void setMaxPersons(unsigned maxPersons);
  void setSoldTickets(unsigned soldTickets);



  // other methods

  vector<string> sitesToVector(string sites);
  friend ostream& operator<<(ostream& out, const Packet & packet);
};
