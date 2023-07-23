#include "Packet.h"

Packet::Packet()
{
}

Packet::Packet(int nid, vector<string> nsites, Date inicio, Date fim, double precoPessoa, unsigned maxPessoas, unsigned bilhetesVendidos){

	id = nid;
	sites = nsites;
	begin = inicio;
	end = fim;
	pricePerPerson = precoPessoa;
	maxPersons = maxPessoas;
	soldTickets = bilhetesVendidos;
}

  // metodos GET

int Packet::getId() const{

	return id;
}

vector<string> Packet::getSites() const{

	return sites;
}

Date Packet::getBeginDate() const{

	return begin;
}

Date Packet::getEndDate() const{

	return end;
}

double Packet::getPricePerPerson() const{

	return pricePerPerson;
}

unsigned Packet::getMaxPersons() const{

	return maxPersons;
}

unsigned Packet::getSoldTickets() const
{
	return soldTickets;
}

  // metodos SET

void Packet::setId(int nid){

	id = nid;
}

void Packet::setSites(vector<string> nsites){

	sites = nsites;
}

void Packet::setBeginDate(Date nbegin){

	begin = nbegin;
}

void Packet::setEndDate(Date nend){

	end = nend;
}

void Packet::setPricePerPerson(double npricePerPerson){

	pricePerPerson = npricePerPerson;
}

void Packet::setMaxPersons(unsigned nmaxPersons){

	maxPersons = nmaxPersons;
}

void Packet::setSoldTickets(unsigned nsoldTickets)
{
	soldTickets = nsoldTickets;
}

vector<string> Packet::sitesToVector(string sites)
{
	vector<string> result;
	string main_location;
	if (sites.find("-") != sites.npos) {
		sites += ",";
		main_location = sites.substr(0, sites.find_first_of("-"));
		while (main_location.size() > 0 && main_location.at(main_location.size()-1) == ' ')
			main_location.pop_back();
		result.push_back(main_location);
		sites.erase(0, sites.find_first_of("-") + 1);
		while (sites != "") {
			string spot = sites.substr(0, sites.find_first_of(","));
			spot = spot.substr(spot.find_first_not_of(" "), spot.npos);
			result.push_back(spot);
			sites.erase(0, sites.find_first_of(",") + 1);
		}
	}
	else {
		result.push_back(sites);
	}
	return result;
}


/*********************************
 * Show Packet information
 ********************************/  

// shows a packet content 
ostream& operator<<(ostream& out, const Packet & packet){

	out << packet.sites.at(0);
	return out;
}
