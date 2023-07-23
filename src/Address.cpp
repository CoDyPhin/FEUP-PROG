#include "Address.h"


Address::Address(){
}

Address::Address(string nstreet, unsigned short ndoorNumber, string nfloor, string npostalCode, string nlocation){

	street = nstreet;
	doorNumber = ndoorNumber;
	floor = nfloor;
	postalCode = npostalCode;
	location = nlocation;
}

Address::Address(string address)
{
	int pos = address.find('/');
	string aux, doorNumberSTR;
	street = address.substr(0, pos - 1);
	aux = address.substr(pos + 1, address.npos);
	pos = aux.find('/');
	doorNumberSTR = aux.substr(0, pos - 1);
	aux = aux.substr(pos + 1, aux.npos);
	pos = aux.find('/');
	floor = aux.substr(0, pos - 1);
	aux = aux.substr(pos + 1, aux.npos);
	pos = aux.find('/');
	postalCode = aux.substr(0, pos - 1);
	aux = aux.substr(pos + 1, aux.npos);
	pos = aux.find('/');
	location = aux.substr(0, pos - 1);
	if (doorNumberSTR[0] == ' ')
		doorNumberSTR = doorNumberSTR.substr(1, doorNumberSTR.npos);
	doorNumber = stoi(doorNumberSTR, nullptr, 10);
	if (floor[0] == ' ')
		floor = floor.substr(1, floor.npos);
	if (postalCode[0] == ' ')
		postalCode = postalCode.substr(1, postalCode.npos);
	if (location[0] == ' ')
		location = location.substr(1, location.npos);
	if (street[0] == ' ')
		street = street.substr(1, street.npos);
}

  // metodos GET


string Address::getStreet() const{

	return street;
}

unsigned short Address::getDoorNumber() const{

	return doorNumber;
}

string Address::getFloor() const{
  
	return floor;
}

string Address::getPostalCode() const{

	return postalCode;
}

string Address::getLocation() const{

	return location;
}


  // metodos SET

void Address::setStreet(string nstreet){

	street = nstreet;
}

void Address::setDoorNumber(unsigned short ndoorNumber){

	doorNumber = ndoorNumber;
}

void Address::setFloor(string nfloor){

	floor = nfloor;
}

void Address::setPostalCode(string npostalCode){

	postalCode = npostalCode;
}

void Address::setLocation(string  nlocation){

	location = nlocation;
}


/*********************************
 * Mostrar Address
 ********************************/  

// discplyes an address in a nice format
ostream& operator<<(ostream& out, const Address & address){

	out << address.street << " / " << to_string(address.doorNumber) << " / " << address.floor << " / " << address.postalCode << " / " << address.location;
	return out;
}
