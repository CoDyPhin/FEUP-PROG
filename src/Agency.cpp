#include "Agency.h"
#include "Client.h"
#include "Packet.h"
#include "Date.h"
#include "Address.h"
#include <fstream>

Agency::Agency(string fileName){
	using namespace std;
	ifstream AgencyFile;
	string AgencyFileLine;
	Client client;
	string nome, nif, morada, fam, boughtpacks, totalvalue;
	vector<string> ids;
	string aux = "";
	ifstream ClientFile;
	string ClientFileLine;
	ifstream PackFile;
	string PackFileLine;
	Packet packet;
	string identif, local, start, fim, preco, vagas, vendas;
	AgencyFile.open(fileName);
	int i = 0;
	int j = 0;
	int k = 0;
	if (AgencyFile.is_open() != true)
	{
		cout << "Could not open the agency file." << endl;
		exit(EXIT_FAILURE);
	}
	else
	{
		while (getline(AgencyFile, AgencyFileLine))
		{
			switch (i)
			{
			case (0):
				name = AgencyFileLine;
				break;
			case (1):
				VATnumber = stoi(AgencyFileLine, nullptr, 10);
				break;
			case (2):
				URL = AgencyFileLine;
				break;
			case (3):
				address = AgencyFileLine;
				break;
			case (4):
				setClientsFile(AgencyFileLine);
				ClientFile.open(AgencyFileLine);
				j = 0;
				if (ClientFile.is_open() == false)
				{
					cout << "Could not open the agency file." << endl;
					exit(EXIT_FAILURE);
				}
				else
				{
					while (getline(ClientFile, ClientFileLine))
					{
						if (ClientFileLine == "::::::::::")
						{
							client = Client(nome, stoi(nif, nullptr, 10), stoi(fam, nullptr, 10), Address(morada), ids, stoi(totalvalue, nullptr, 10));
							clients.push_back(client);
							j = 0;
						}
						else
						{
							switch (j)
							{
							case (0):
								nome = ClientFileLine;
								break;
							case (1):
								nif = ClientFileLine;
								break;
							case (2):
								fam = ClientFileLine;
								break;
							case (3):
								morada = ClientFileLine;
								break;
							case (4):
								boughtpacks = ClientFileLine;
								ids.clear();
								boughtpacks += ";";
								for (unsigned int i = 0; i < boughtpacks.length(); i++)
								{
									if (isdigit(boughtpacks[i]))
										aux += boughtpacks[i];
									else
									{
										if (aux.length() >= 1)
											ids.push_back(aux);
										aux = "";
									}
								}
								break;
							case (5):
								totalvalue = ClientFileLine;
								break;
							}
							j = j + 1;
						}
					}
					client = Client(nome, stoi(nif, nullptr, 10), stoi(fam, nullptr, 10), Address(morada), ids, stoi(totalvalue, nullptr, 10));
					clients.push_back(client);
				}
				ClientFile.close();
				break;
			case (5):
				setPacketsFile(AgencyFileLine);
				PackFile.open(AgencyFileLine);
				k = 0;
				if (PackFile.is_open() == false)
				{
					cout << "Could not open the packs file." << endl;
					exit(EXIT_FAILURE);
				}
				else
				{
					while (getline(PackFile, PackFileLine))
					{
						if (PackFileLine == "::::::::::")
						{
							packet = Packet((unsigned)stoi(identif, nullptr, 10), packet.sitesToVector(local), Date(start), Date(fim), stod(preco), (unsigned)stoi(vagas, nullptr, 10), (unsigned)stoi(vendas, nullptr, 10));
							packets.push_back(packet);
							k = 0;
						}
						else
						{
							switch (k)
							{
							case (0):
								identif = PackFileLine;
								break;
							case (1):
								local = PackFileLine;
								break;
							case (2):
								start = PackFileLine;
								break;
							case (3):
								fim = PackFileLine;
								break;
							case (4):
								preco = PackFileLine;
								break;
							case (5):
								vagas = PackFileLine;
								break;
							case (6):
								vendas = PackFileLine;
							}
							k = k + 1;
						}
					}
					packet = Packet((unsigned)stoi(identif, nullptr, 10), packet.sitesToVector(local), Date(start), Date(fim), stod(preco), (unsigned)stoi(vagas, nullptr, 10), (unsigned)stoi(vendas, nullptr, 10));
					packets.push_back(packet);
				}
				PackFile.close();
				break;
			}
			i = i + 1;
		}
	}
	AgencyFile.close();
}

  // metodos GET
string Agency::getName() const{

	return name;
}

unsigned Agency::getVATnumber() const{

	return VATnumber;
}

Address Agency::getAddress() const{

	return address;
}

string Agency::getURL() const{

	return URL;
}

vector<Client> Agency::getClients() const{

	return clients;
}

vector<Packet> Agency::getPackets() const{

	return packets;
}

string Agency::getClientsFile() const
{
	return clientsFile;
}

string Agency::getPacketsFile() const
{
	return packetsFile;
}

bool Agency::getClientInfoHasChanged() const
{
	return clientsInfoHasChanged;
}

bool Agency::getPacketsInfoHasChanged() const
{
	return packetsInfoHasChanged;
}

  
  // SET Methods

void Agency::setName(string nname){

	name = nname;
}

void Agency::setVATnumber(unsigned nVATnumber){

	VATnumber = nVATnumber;
}

void Agency::setAddress(Address naddress){

	address = naddress;
}
  void Agency::setURL(string nurl){

	  URL = nurl;
}
  void Agency::setClients(vector<Client> & nclients){

	  clients = nclients;
  }
  void Agency::setPackets(vector<Packet> & npackets){

	  packets = npackets;
}

  void Agency::setClientsFile(string clientfile)
  {
	  clientsFile = clientfile;
  }

  void Agency::setPacketsFile(string packetfile)
  {
	  packetsFile = packetfile;
  }

  void Agency::setClientInfoHasChanged(bool clientinfochanged)
  {
	  clientsInfoHasChanged = clientinfochanged;
  }

  void Agency::setPacketsInfoHasChanged(bool packetinfochanged)
  {
	  packetsInfoHasChanged = packetinfochanged;
  }

/*********************************
 * Mostrar Loja
 ********************************/  

// mostra o conteudo de uma agencia
ostream& operator<<(ostream& out, const Agency & agency){

	out << agency.name;
	return out;
}
