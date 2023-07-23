#include "Menus.h"
#include "Agency.h"
#include "Address.h"
#include <map>

void mainMenu(Agency &agency)
{
	firstMenu(agency);
}

string AddressToString(Address adrs)
{
	return (adrs.getStreet() + " / " + to_string(adrs.getDoorNumber()) + " / " + adrs.getFloor() + " / " + adrs.getPostalCode() + " / " + adrs.getLocation());
}

string toStringPackets(vector<string> vector)
{
	string aux;
	for (unsigned int i = 0; i < vector.size(); i++)
	{
		aux += (vector.at(i) + "; ");
	}
	return (aux.substr(0, aux.size()-2));
}

string toStringSites(vector<string> vector)
{
	string aux = "";
	if (vector.size() == 1) return vector.at(0);
	else
	{
		aux += vector.at(0);
		aux += " - ";
		for (unsigned int i = 1; i < vector.size(); i++)
		{
			aux += vector.at(i) + ", ";
		}
		return aux.substr(0, aux.size() - 2);
	}
}

vector<string> toVectorSites(string sites)
{
	vector <string> result;
	string main_location;
	if (sites.find("-") != string::npos) {
		sites += ",";
		main_location = sites.substr(0, sites.find_first_of("-"));
		result.push_back(main_location);
		sites.erase(0, sites.find_first_of("-") + 1);
		while (sites != "") {
			string spot = sites.substr(0, sites.find_first_of(","));
			result.push_back(spot);
			sites.erase(0, sites.find_first_of(",") + 1);
		}
	}
	else {
		result.push_back(sites);
	}
	return result;
}

string toStringDate(Date date)
{
	return (to_string(date.getYear()) + "/" + to_string(date.getMonth()) + "/" + to_string(date.getDay()));
}

void UpdateClientFile(string filename, Agency agency) // atualiza o ficheiro de clientes
{
	ofstream ClientFile;
	vector<Client> aux = agency.getClients();
	ClientFile.open(filename);
	if (ClientFile.is_open())
	{
		for (unsigned int i = 0; i < agency.getClients().size(); i++)
		{
			ClientFile << aux.at(i).getName() << endl;
			ClientFile << aux.at(i).getVATnumber() << endl;
			ClientFile << aux.at(i).getFamilySize() << endl;
			ClientFile << AddressToString(aux.at(i).getAddress()) << endl;
			ClientFile << toStringPackets(aux.at(i).getSTRPacketList()) << endl;
			ClientFile << aux.at(i).getTotalPurchased();
			if ((i + 1) != aux.size())
				ClientFile << endl << "::::::::::" << endl;
		}
	}
	else
	{
		cout << "Error opening clients file!";
		exit(EXIT_FAILURE);
	}
	ClientFile.close();
}

void UpdatePackFile(string filename, Agency agency) // atualiza o ficheiro de packs
{
	ofstream PackFile;
	PackFile.open(filename);
	if (PackFile.is_open())
	{
		for (unsigned int i = 0; i < agency.getPackets().size(); i++)
		{
			PackFile << agency.getPackets().at(i).getId() << endl;
			PackFile << toStringSites(agency.getPackets().at(i).getSites()) << endl;
			PackFile << toStringDate(agency.getPackets().at(i).getBeginDate()) << endl;
			PackFile << toStringDate(agency.getPackets().at(i).getEndDate()) << endl;
			PackFile << agency.getPackets().at(i).getPricePerPerson() << endl;
			PackFile << agency.getPackets().at(i).getMaxPersons() << endl;
			PackFile << agency.getPackets().at(i).getSoldTickets();
			if ((i + 1) != agency.getPackets().size()) PackFile << endl << "::::::::::" << endl;
		}
	}
	else
	{
		cout << "Error opening packs file!";
		exit(EXIT_FAILURE);
	}
	PackFile.close();
}

int ClientFinder(vector<Client> ClientVector, string ClientNIF) // encontra o index do cliente com o NIF desejado no vector de clientes
{
	for (unsigned int i = 0; i < ClientVector.size(); i++)
	{
		if (ClientVector.at(i).getVATnumber() == stoi(ClientNIF, nullptr, 10))
		{
			return i;
		}
	}
	//cout << "Client Not Found!";
	return -1;
}

void ClientsMainMenu(Agency &agency)
{
	int input;
	cout << "[0] Exit" << endl;
	cout << "[1] Client Details" << endl;
	cout << "[2] Change Client Details" << endl;
	cout << "[3] Add Client" << endl;
	cout << "[4] Remove Client" << endl;
	cout << "Option: ";
	cin >> input;
	cout << "=============================================" << endl;
	switch (input)
	{
		case 0:
			break;
		case 1:
		{
			ClientsDetailsMenu(agency);
			break;
		}
		case(2):
		{
			Change_Clients_Details_Menu(agency);
			break;
		}
		case(3):
		{
			add_client_menu(agency);
			break;
		}
		case(4):
		{
			remove_client_menu(agency);
			break;
		}
	}
}

void ClientsDetailsMenu(Agency &agency)
{
	int input;
	cout << "[0] Exit" << endl;
	cout << "[1] Specific Client" << endl;
	cout << "[2] All Clients" << endl;
	cout << "Option: ";
	cin >> input;
	cout << "=============================================" << endl;
	switch (input)
	{
		case 0:
			break;
		case 1:
		{
			SpecificClientMenu(agency);
			break;
		}
		case 2:
		{
			AllClientsMenu(agency);
			break;
		}
	}
}

void SpecificClientMenu(Agency &agency)
{
	string chosenNIF;
	cout << "Available Clients: " << endl;
	cout << "---------------------------" << endl;
	for (unsigned int i = 0; i < agency.getClients().size(); i++)
	{
		cout << "Name: " << agency.getClients().at(i).getName() << endl;
		cout << "NIF: " << agency.getClients().at(i).getVATnumber() << endl;
		cout << "---------------------------" << endl;
	}
	cout << "Enter the NIF: ";
	cin >> chosenNIF;
	cout << "=============================================" << endl;
	int ClientNumber = ClientFinder(agency.getClients(), chosenNIF);
	if (ClientNumber == -1)
	{
		cout << "Client Not Found!";
	}
	else
	{
		cout << agency.getClients().at(ClientNumber).getName() << endl;
		cout << agency.getClients().at(ClientNumber).getVATnumber() << endl;
		cout << agency.getClients().at(ClientNumber).getFamilySize() << endl;
		cout << agency.getClients().at(ClientNumber).getAddress() << endl;
		cout << toStringPackets(agency.getClients().at(ClientNumber).getSTRPacketList()) << endl;
		cout << agency.getClients().at(ClientNumber).getTotalPurchased() << endl;
	}

}

void AllClientsMenu(Agency &agency)
{
	for (unsigned int i = 0; i < agency.getClients().size(); i++)
	{
		cout << agency.getClients().at(i).getName() << endl;
		cout << agency.getClients().at(i).getVATnumber() << endl;
		cout << agency.getClients().at(i).getFamilySize() << endl;
		cout << agency.getClients().at(i).getAddress() << endl;
		cout << toStringPackets(agency.getClients().at(i).getSTRPacketList()) << endl;
		cout << agency.getClients().at(i).getTotalPurchased() << endl;
		cout << "::::::::::" << endl;
	}
}

void Change_Clients_Details_Menu(Agency &agency)
{
	string chosenNIF;
	int ClientNumber;
	int input;
	cout << "Available Clients: " << endl;
	cout << "---------------------------" << endl;
	for (unsigned int i = 0; i < agency.getClients().size(); i++)
	{
		cout << "Name: " << agency.getClients().at(i).getName() << endl;
		cout << "NIF: " << agency.getClients().at(i).getVATnumber() << endl;
		cout << "---------------------------" << endl;
	}
	cout << "Enter the NIF: ";
	cin >> chosenNIF;
	cout << "=============================================" << endl;
	ClientNumber = ClientFinder(agency.getClients(), chosenNIF);
	cout << "What do you want to change?" << endl;
	cout << "[0] Exit" << endl;
	cout << "[1] Name" << endl;
	cout << "[2] NIF" << endl;
	cout << "[3] Number of family members" << endl;
	cout << "[4] Address" << endl;
	cout << "Option: ";
	cin >> input;
	cout << "=============================================" << endl;
	switch (input)
	{
		case(0):
			break;
		case(1):
		{
			Change_Name_Menu(agency, ClientNumber);
			break;
		}
		case(2):
		{
			change_NIF_menu(agency, ClientNumber);
			break;
		}
		case(3):
		{
			change_FamilySize_menu(agency, ClientNumber);
			break;
		}
		case(4):
		{
			change_Address_menu(agency, ClientNumber);
			break;
		}
	}
}

void Change_Name_Menu(Agency &agency, int ClientNumber)
{
	string newname;
	vector<Client> aux = agency.getClients();
	cout << "Enter the new name: ";
	cin.ignore(1000, '\n');
	getline(cin, newname);
	aux.at(ClientNumber).setName(newname);
	agency.setClients(aux);
	agency.setClientInfoHasChanged(true);

}

void change_NIF_menu(Agency &agency, int ClientNumber)
{
	string newnif;
	vector<Client> aux = agency.getClients();
	cout << "Enter the new NIF: ";
	cin >> newnif;
	if ((ClientFinder(agency.getClients(), newnif) != ClientNumber))
	{
		cout << "The client with this NIF is already registered!" << endl;
	}
	else
	{
		aux.at(ClientNumber).setVATnumber(stoi(newnif, nullptr, 10));
		agency.setClients(aux);
		agency.setClientInfoHasChanged(true);
	}
}

void change_FamilySize_menu(Agency &agency, int ClientNumber)
{
	unsigned short newfamilysize;
	vector<Client> aux = agency.getClients();
	cout << "Enter the new number of family members: ";
	cin >> newfamilysize;
	aux.at(ClientNumber).setFamilySize(newfamilysize);
	agency.setClients(aux);
	agency.setClientInfoHasChanged(true);
}

void change_Address_menu(Agency &agency, int ClientNumber)
{
	int input;
	cout << "What do you wish to change?" << endl;
	cout << "[0] Exit" << endl;
	cout << "[1] Everything" << endl;
	cout << "[2] Street" << endl;
	cout << "[3] Door Number" << endl;
	cout << "[4] Floor" << endl;
	cout << "[5] Postcode" << endl;
	cout << "[6] City" << endl;
	cout << "Option: ";
	cin >> input;
	switch (input)
	{
		case 0:	
			break;
		case 1:
		{
			change_Everything_menu(agency, ClientNumber);
			break;
		}
		case 2:
		{
			change_Street_menu(agency, ClientNumber);
			break;
		}
		case 3:
		{
			change_Door_menu(agency, ClientNumber);
			break;
		}
		case 4:
		{
			change_Floor_menu(agency, ClientNumber);
			break;
		}
		case 5:
		{
			change_PostalCode_menu(agency, ClientNumber);
			break;
		}
		case 6:
		{
			change_City_menu(agency, ClientNumber);
			break;
		}
	}
}

void change_Everything_menu(Agency &agency, int ClientNumber)
{
	string newstreet;
	int newdoornumber;
	string newfloor;
	string newpostalcode;
	string newcity;
	vector<Client> aux = agency.getClients();
	Address aux1 = aux.at(ClientNumber).getAddress();
	cout << "Enter the new street name: ";
	cin.ignore(1000, '\n');
	getline(cin, newstreet);
	aux1.setStreet(newstreet);
	aux.at(ClientNumber).setAddress(aux1);
	cout << "Enter the new door number: ";
	cin >> newdoornumber;
	aux1.setDoorNumber(newdoornumber);
	aux.at(ClientNumber).setAddress(aux1);
	cout << "Enter the new floor (use '-' if none): ";
	cin >> newfloor;
	aux1.setFloor(newfloor);
	aux.at(ClientNumber).setAddress(aux1);
	cout << "Enter the new postcode: ";
	cin >> newpostalcode;
	aux1.setPostalCode(newpostalcode);
	aux.at(ClientNumber).setAddress(aux1);
	cout << "Enter the new city: ";
	cin.ignore(1000, '\n');
	getline(cin, newcity);
	aux1.setLocation(newcity);
	aux.at(ClientNumber).setAddress(aux1);
	agency.setClients(aux);
	agency.setClientInfoHasChanged(true);
}

void change_Street_menu(Agency &agency, int ClientNumber)
{
	string newstreet;
	vector<Client> aux = agency.getClients();
	Address aux1 = aux.at(ClientNumber).getAddress();
	cout << "Enter the new street name: ";
	cin.ignore(1000, '\n');
	getline(cin, newstreet);
	aux1.setStreet(newstreet);
	aux.at(ClientNumber).setAddress(aux1);
	agency.setClients(aux);
	agency.setClientInfoHasChanged(true);
}

void change_Door_menu(Agency &agency, int ClientNumber)
{
	int newdoornumber;
	vector<Client> aux = agency.getClients();
	Address aux1 = aux.at(ClientNumber).getAddress();
	cout << "Enter the new door number: ";
	cin >> newdoornumber;
	aux1.setDoorNumber(newdoornumber);
	aux.at(ClientNumber).setAddress(aux1);
	agency.setClients(aux);
	agency.setClientInfoHasChanged(true);
}

void change_Floor_menu(Agency &agency, int ClientNumber)
{
	string newfloor;
	vector<Client> aux = agency.getClients();
	Address aux1 = aux.at(ClientNumber).getAddress();
	cout << "Enter the new floor (use '-' if none): ";
	cin >> newfloor;
	aux1.setFloor(newfloor);
	aux.at(ClientNumber).setAddress(aux1);
	agency.setClients(aux);
	agency.setClientInfoHasChanged(true);
}

void change_PostalCode_menu(Agency &agency, int ClientNumber)
{
	string newpostalcode;
	vector<Client> aux = agency.getClients();
	Address aux1 = aux.at(ClientNumber).getAddress();
	cout << "Enter the new postcode: ";
	cin >> newpostalcode;
	aux1.setPostalCode(newpostalcode);
	aux.at(ClientNumber).setAddress(aux1);
	agency.setClients(aux);
	agency.setClientInfoHasChanged(true);
}

void change_City_menu(Agency &agency, int ClientNumber)
{
	string newcity;
	vector<Client> aux = agency.getClients();
	Address aux1 = aux.at(ClientNumber).getAddress();
	cout << "Enter the new city: ";
	cin.ignore(1000, '\n');
	getline(cin, newcity);
	aux1.setLocation(newcity);
	aux.at(ClientNumber).setAddress(aux1);
	agency.setClients(aux);
	agency.setClientInfoHasChanged(true);
}

void add_client_menu(Agency &agency)
{
	string clientname;
	string clientnif;
	unsigned short int clientfam;
	string clientfloor;
	string clientstreet;
	string clientpostcode;
	string clientcity;
	int  clientdoornumber;
	Client newclient;
	vector<Client> newvector;
	Address newclientaddress;
	cout << "Enter the name of the new client: ";
	cin.ignore(1000, '\n');
	getline(cin, clientname);
	cout << "Enter the NIF of the new client: ";
	cin >> clientnif;
	if ((ClientFinder(agency.getClients(), clientnif) != -1))
	{
		cout << "The client with this NIF is already registered!" << endl;
	}
	cout << "Enter the number of family members of the new client: ";
	cin >> clientfam;
	cout << "Enter the street name of the new client: ";
	cin.ignore(1000, '\n');
	getline(cin, clientstreet);
	cout << "Enter the door number of the new client: ";
	cin >> clientdoornumber;
	cout << "Enter the floor of the new client (use '-' if none): ";
	cin >> clientfloor;
	cout << "Enter the postcode of the new client: ";
	cin >> clientpostcode;
	cout << "Enter the city of the new client: ";
	cin.ignore(1000, '\n');
	getline(cin, clientcity);
	newclientaddress = Address(clientstreet, clientdoornumber, clientfloor, clientpostcode, clientcity);
	newclient = Client(clientname, (unsigned) stoi(clientnif, nullptr, 10), clientfam, newclientaddress);
	newvector = agency.getClients();
	newvector.push_back(newclient);
	agency.setClients(newvector);
	agency.setClientInfoHasChanged(true);
}

void remove_client_menu(Agency &agency)
{
	string chosenNIF;
	int ClientNumber;
	vector<Client> aux = agency.getClients();
	cout << "Available Clients: " << endl;
	cout << "---------------------------" << endl;
	for (unsigned int i = 0; i < aux.size(); i++)
	{
		cout << "Name: " << aux.at(i).getName() << endl;
		cout << "NIF: " << aux.at(i).getVATnumber() << endl;
		cout << "---------------------------" << endl;
	}
	cout << "Enter the NIF of the client you wish to remove: " << endl;
	cin >> chosenNIF;
	ClientNumber = ClientFinder(aux, chosenNIF);
	if (ClientNumber == -1)
	{
		cout << "Client not found!";
	}
	else
	{
		aux.erase(aux.begin() + ClientNumber);
		agency.setClients(aux);
		agency.setClientInfoHasChanged(true);
	}
}

vector<int> PackFinderDestin(vector<Packet> PackVector, string destination) // encontra o index do pack por destino
{
	vector<int> chosenpacks;
	for (unsigned int i = 0; i < PackVector.size(); i++)
	{
		if (toStringSites(PackVector.at(i).getSites()).find(destination) != toStringSites(PackVector.at(i).getSites()).npos)
		{
		chosenpacks.push_back(i);
		}
	}
	return chosenpacks;
}

vector<int> PackFinderDate(vector<Packet> PackVector, int startt, int endt) // encontra o index do pack por datas
{
	vector<int> chosenpacks;
	Date startd;
	Date endd;
	int starttime, endtime;
	for (unsigned int i = 0; i < PackVector.size(); i++)
	{
		startd = PackVector.at(i).getBeginDate();
		starttime = startd.getYear() * 365 + startd.getMonth() * 30 + startd.getDay();
		endd = PackVector.at(i).getEndDate();
		endtime = endd.getYear() * 365 + endd.getMonth() * 30 + endd.getDay();
		if (starttime >= startt && starttime <= endt && endtime >= startt && endtime <= endt) chosenpacks.push_back(i);
	}
	return chosenpacks;
}

int PackIDFinder(vector<Packet> PackVector, string chosenID) // encontra o index do pack por identificador
{
	for (unsigned int i = 0; i < PackVector.size(); i++)
	{
		string aux;
		if (chosenID[0] == '-')
		{
			if (PackVector.at(i).getId() == stoi(chosenID, nullptr, 10))
				return i;
		}
		else
		{
			if (to_string(PackVector.at(i).getId())[0] == '-')
			{
				aux = to_string(PackVector.at(i).getId()).substr(1, to_string(PackVector.at(i).getId()).npos);
				if (aux == chosenID)
					return i;
			}
			else
			{
				if (PackVector.at(i).getId() == stoi(chosenID, nullptr, 10))
					return i;
			}
		}
	}
	return -1;
}

void PacksMainMenu(Agency &agency)
{
	int input;
	int PackNumber;
	cout << "[0] Exit" << endl;
	cout << "[1] Pack Details" << endl;
	cout << "[2] Change Pack Details" << endl;
	cout << "[3] Add Pack" << endl;
	cout << "[4] Remove Pack" << endl;
	cout << "Option: ";
	cin >> input;
	cout << "=============================================" << endl;
	switch (input)
	{
	case(0):
	{
		break;
	}
	case(1):
	{
		Pack_Details_Menu(agency);
		break;
	}
	case(2):
	{
		Change_PackDetails_Menu(agency);
		break;
	}
	case(3):
	{
		Add_Pack_Menu(agency);
		break;
	}
	case(4):
	{
		Remove_Pack_Menu(agency);
		break;
	}
	}
}

void Pack_Details_Menu(Agency &agency)
{
	int input;
	int PackNumber;
	cout << "[0] Exit" << endl;
	cout << "[1] Search Packs" << endl;
	cout << "[2] All Packs" << endl;
	cout << "Option: ";
	cin >> input;
	cout << "=============================================" << endl;
	switch (input)
	{
	case(0):
	{
		break;
	}
	case(1):
	{
		Search_Packs_Menu(agency);
		break;
	}
	case(2):
	{
		AllPacks_Menu(agency);
		break;
	}
	}
}

void Search_Packs_Menu(Agency &agency)
{
	vector<int>foundpacks;
	vector<int>foundpacks2;
	int input;
	int PackNumber;
	cout << "[0] Exit" << endl;
	cout << "[1] By Destination" << endl;
	cout << "[2] By Date" << endl;
	cout << "[3] By Destination and Date" << endl;
	cout << "[4] Bought by a specific client" << endl;
	cout << "Option: ";
	cin >> input;
	cout << "=============================================" << endl;
	switch (input)
	{
	case(0):
	{
		break;
	}
	case(1):
	{
		Search_PacksByDestination_Menu(agency, foundpacks);
		break;
	}
	case(2):
	{
		Search_PacksByDate_Menu(agency, foundpacks);
		break;
	}
	case(3):
	{
		Search_PacksByDestinationAndDate_Menu(agency, foundpacks, foundpacks2);
		break;
	}
	case(4):
	{
		Search_PackBoughtByClient_Menu(agency, foundpacks);
		break;
	}
	}
}

void Search_PackBoughtByClient_Menu(Agency &agency, vector<int> foundpacks)
{
	int ClientNumber;
	string  chosenNIF;
	string id;
	string packid;
	int foundid;
	cout << "Available Clients: " << endl;
	cout << "---------------------------" << endl;
	for (unsigned int i = 0; i < agency.getClients().size(); i++)
	{
		cout << "Name: " << agency.getClients().at(i).getName() << endl;
		cout << "NIF: " << agency.getClients().at(i).getVATnumber() << endl;
		cout << "---------------------------" << endl;
	}
	cout << "Enter the NIF: ";
	cin >> chosenNIF;
	cout << "=============================================" << endl;
	ClientNumber = ClientFinder(agency.getClients(), chosenNIF);
	if (ClientNumber == -1)
	{
		cout << "Client Not Found!";
	}
	else
	{
		for (unsigned int i = 0; i < agency.getClients().at(ClientNumber).getSTRPacketList().size(); i++)
		{
			packid = agency.getClients().at(ClientNumber).getSTRPacketList().at(i);
			foundid = PackIDFinder(agency.getPackets(), packid);
			if (foundid == -1)
			{
				cout << "Pack ID not found!" << endl;
				cout << "::::::::::" << endl;
			}
			else
			{
				cout << agency.getPackets().at(foundid).getId() << endl;
				cout << toStringSites(agency.getPackets().at(foundid).getSites()) << endl;
				cout << agency.getPackets().at(foundid).getBeginDate() << endl;
				cout << agency.getPackets().at(foundid).getEndDate() << endl;
				cout << agency.getPackets().at(foundid).getPricePerPerson() << endl;
				cout << agency.getPackets().at(foundid).getMaxPersons() << endl;
				cout << agency.getPackets().at(foundid).getSoldTickets() << endl;
				cout << "::::::::::" << endl;
			}
		}

	}
}

void Search_PacksByDestination_Menu(Agency &agency, vector<int>foundpacks)
{
	string destin;
	int PackNumber;
	cout << "Enter the desired destination: ";
	cin >> destin;
	cout << "=============================================" << endl;
	foundpacks = PackFinderDestin(agency.getPackets(), destin);
	if (foundpacks.size() > 0)
	{
		for (unsigned int i = 0; i < foundpacks.size(); i++)
		{
			PackNumber = foundpacks[i];
			cout << agency.getPackets().at(PackNumber).getId() << endl;
			cout << toStringSites(agency.getPackets().at(PackNumber).getSites()) << endl;
			cout << agency.getPackets().at(PackNumber).getBeginDate() << endl;
			cout << agency.getPackets().at(PackNumber).getEndDate() << endl;
			cout << agency.getPackets().at(PackNumber).getPricePerPerson() << endl;
			cout << agency.getPackets().at(PackNumber).getMaxPersons() << endl;
			cout << agency.getPackets().at(PackNumber).getSoldTickets() << endl;
			cout << "::::::::::" << endl;
		}
	}
	else cout << "No Packs Found!" << endl;
}

void Search_PacksByDate_Menu(Agency &agency, vector<int>foundpacks)
{
	int PackNumber;
	int start_date_year;
	int start_date_month;
	int start_date_day;
	int starttime;
	int end_date_year;
	int end_date_month;
	int end_date_day;
	int endtime;
	cout << "Enter the start date (YEAR MONTH DAY): ";
	cin >> start_date_year; cin >> start_date_month; cin >> start_date_day;
	starttime = 365 * start_date_year + 30 * start_date_month + start_date_day;
	cout << "Enter the end date (YEAR MONTH DAY): ";
	cin >> end_date_year; cin >> end_date_month; cin >> end_date_day;
	endtime = 365 * end_date_year + 30 * end_date_month + end_date_day;
	cout << "=============================================" << endl;
	foundpacks = PackFinderDate(agency.getPackets(), starttime, endtime);
	if (foundpacks.size() > 0)
	{
		for (unsigned int i = 0; i < foundpacks.size(); i++)
		{
			PackNumber = foundpacks[i];
			cout << agency.getPackets().at(PackNumber).getId() << endl;
			cout << toStringSites(agency.getPackets().at(PackNumber).getSites()) << endl;
			cout << agency.getPackets().at(PackNumber).getBeginDate() << endl;
			cout << agency.getPackets().at(PackNumber).getEndDate() << endl;
			cout << agency.getPackets().at(PackNumber).getPricePerPerson() << endl;
			cout << agency.getPackets().at(PackNumber).getMaxPersons() << endl;
			cout << agency.getPackets().at(PackNumber).getSoldTickets() << endl;
			cout << "::::::::::" << endl;
		}
	}
	else cout << "No packs were found!" << endl;
}

void Search_PacksByDestinationAndDate_Menu(Agency &agency, vector<int>foundpacks, vector<int>foundpacks2)
{
	string destin;
	int PackNumber;
	int start_date_year;
	int start_date_month;
	int start_date_day;
	int starttime;
	int end_date_year;
	int end_date_month;
	int end_date_day;
	int endtime;
	cout << "Enter the desired destination: ";
	cin >> destin;
	foundpacks = PackFinderDestin(agency.getPackets(), destin);
	cout << "Enter the start date (YEAR MONTH DAY): ";
	cin >> start_date_year; cin >> start_date_month; cin >> start_date_day;
	starttime = 365 * start_date_year + 30 * start_date_month + start_date_day;
	cout << "Enter the end date (YEAR MONTH DAY): ";
	cin >> end_date_year; cin >> end_date_month; cin >> end_date_day;
	endtime = 365 * end_date_year + 30 * end_date_month + end_date_day;
	foundpacks2 = PackFinderDate(agency.getPackets(), starttime, endtime);
	if (foundpacks.size() > 0 && foundpacks2.size() > 0)
	{
		int count = 0;
		for (unsigned int i = 0; i < foundpacks.size(); i++)
		{
			PackNumber = foundpacks[i];
			if (find(foundpacks2.begin(), foundpacks2.end(), PackNumber) != foundpacks2.end())
			{
				PackNumber = foundpacks[i];
				cout << agency.getPackets().at(PackNumber).getId() << endl;
				cout << toStringSites(agency.getPackets().at(PackNumber).getSites()) << endl;
				cout << agency.getPackets().at(PackNumber).getBeginDate() << endl;
				cout << agency.getPackets().at(PackNumber).getEndDate() << endl;
				cout << agency.getPackets().at(PackNumber).getPricePerPerson() << endl;
				cout << agency.getPackets().at(PackNumber).getMaxPersons() << endl;
				cout << agency.getPackets().at(PackNumber).getSoldTickets() << endl;
				cout << "::::::::::" << endl;
				count += 1;
			}
		}
		cout << "=============================================" << endl;
		if (count == 0)
			cout << "No packs were found!" << endl;
	}
	else cout << "No packs were found!" << endl;
}

void AllPacks_Menu(Agency &agency)
{
	cout << "=============================================" << endl;
	for (unsigned int i = 0; i < agency.getPackets().size(); i++)
	{
		cout << agency.getPackets().at(i).getId() << endl;
		cout << toStringSites(agency.getPackets().at(i).getSites()) << endl;
		cout << agency.getPackets().at(i).getBeginDate() << endl;
		cout << agency.getPackets().at(i).getEndDate() << endl;
		cout << agency.getPackets().at(i).getPricePerPerson() << endl;
		cout << agency.getPackets().at(i).getMaxPersons() << endl;
		cout << agency.getPackets().at(i).getSoldTickets() << endl;
		cout << "::::::::::" << endl;
	}
}

void Change_PackDetails_Menu(Agency &agency)
{
	int PackNumber;
	string chosenID;
	int input;
	cout << "Available Packs: " << endl;
	cout << "---------------------------" << endl;
	for (unsigned int i = 0; i < agency.getPackets().size(); i++)
	{
		cout << "ID: " << agency.getPackets().at(i).getId() << endl;
		cout << "Destination: " << toStringSites(agency.getPackets().at(i).getSites()) << endl;
		cout << "---------------------------" << endl;
	}
	cout << "Enter the identifier: ";
	cin >> chosenID;
	cout << "=============================================" << endl;
	PackNumber = PackIDFinder(agency.getPackets(), chosenID);
	if (PackNumber == -1)
	{
		cout << "Invalid identifier!" << endl;
	}
	cout << "What do you want to change?" << endl;
	cout << "[0] Exit" << endl;
	cout << "[1] Destination" << endl;
	cout << "[2] Start date" << endl;
	cout << "[3] End date" << endl;
	cout << "[4] Price" << endl;
	cout << "[5] Starting availability" << endl;
	cout << "[6] Set pack as unavailable" << endl;
	cout << "Option: ";
	cin >> input;
	cout << "=============================================" << endl;
	switch (input)
	{
	case(0):
	{
		break;
	}
	case(1):
	{
		Change_PackDestiation_Menu(agency, PackNumber);
		break;
	}
	case(2):
	{
		Change_PackStartDate_Menu(agency, PackNumber);
		break;
	}
	case(3):
	{
		Change_PackEndDate_Menu(agency, PackNumber);
		break;
	}
	case(4):
	{
		Change_PackPrice_Menu(agency, PackNumber);
		break;
	}
	case(5):
	{
		Change_PackStartingAvialability_Menu(agency, PackNumber);
		break;
	}
	case(6):
	{
		Change_PackAvailability_Menu(agency, PackNumber);
		break;
	}
	}
}

void Change_PackDestiation_Menu(Agency &agency, int PackNumber)
{
	vector<Packet> aux = agency.getPackets();
	string destin;
	cout << "Enter the new destination: ";
	cin.ignore(1000, '\n');
	getline(cin, destin);
	aux.at(PackNumber).setSites(toVectorSites(destin));
	agency.setPackets(aux);
	agency.setPacketsInfoHasChanged(true);
	
}

void Change_PackStartDate_Menu(Agency &agency, int PackNumber)
{
	vector<Packet> aux = agency.getPackets();
	Date newstartdate;
	unsigned int newstartdateyear, newstartdatemonth, newstartdateday;
	cout << "Enter the new start year: ";
	cin >> newstartdateyear;
	cout << "Enter the new start month: ";
	cin >> newstartdatemonth;
	cout << "Enter the new start day: ";
	cin >> newstartdateday;
	if ((agency.getPackets().at(PackNumber).getBeginDate().getYear() * 365 + agency.getPackets().at(PackNumber).getBeginDate().getMonth() * 30 + agency.getPackets().at(PackNumber).getBeginDate().getDay()) > (agency.getPackets().at(PackNumber).getEndDate().getYear() * 365 + agency.getPackets().at(PackNumber).getEndDate().getMonth() * 30 + agency.getPackets().at(PackNumber).getEndDate().getDay()))
	{
		cout << "The trip cannot start after it's over!" << endl;
	}
	else
	{
		newstartdate = Date(newstartdateday, newstartdatemonth, newstartdateyear);
		aux.at(PackNumber).setBeginDate(newstartdate);
		agency.setPackets(aux);
		agency.setPacketsInfoHasChanged(true);
	}
}

void Change_PackEndDate_Menu(Agency &agency, int PackNumber)
{
	vector<Packet> aux = agency.getPackets();
	Date newenddate;
	unsigned int newenddateyear, newenddatemonth, newenddateday;
	cout << "Enter the new end year: ";
	cin >> newenddateyear;
	cout << "Enter the new end month: ";
	cin >> newenddatemonth;
	cout << "Enter the new end day: ";
	cin >> newenddateday;
	if ((agency.getPackets().at(PackNumber).getBeginDate().getYear() * 365 + agency.getPackets().at(PackNumber).getBeginDate().getMonth() * 30 + agency.getPackets().at(PackNumber).getBeginDate().getDay()) > (agency.getPackets().at(PackNumber).getEndDate().getYear() * 365 + agency.getPackets().at(PackNumber).getEndDate().getMonth() * 30 + agency.getPackets().at(PackNumber).getEndDate().getDay()))
	{
		cout << "The trip cannot start after it's over!" << endl;
	}
	else
	{
		newenddate = Date(newenddateday, newenddatemonth, newenddateyear);
		aux.at(PackNumber).setEndDate(newenddate);
		agency.setPackets(aux);
		agency.setPacketsInfoHasChanged(true);
	}
}

void Change_PackPrice_Menu(Agency &agency, int PackNumber)
{
	vector<Packet> aux = agency.getPackets();
	double newprice;
	cout << "Enter the new price: ";
	cin >> newprice;
	aux.at(PackNumber).setPricePerPerson(newprice);
	agency.setPackets(aux);
	agency.setPacketsInfoHasChanged(true);
}

void Change_PackStartingAvialability_Menu(Agency &agency, int PackNumber)
{
	vector<Packet> aux = agency.getPackets();
	unsigned int newaviability;
	cout << "Enter the maximum number of people of the pack: ";
	cin >> newaviability;
	aux.at(PackNumber).setMaxPersons(newaviability);
	agency.setPackets(aux);
	agency.setPacketsInfoHasChanged(true);
}

void Change_PackSoldTickets_Menu(Agency &agency, int PackNumber)
{
	vector<Packet> aux = agency.getPackets();
	unsigned int bought;
	cout << "Enter the number of tickets bought: ";
	cin >> bought;
	aux.at(PackNumber).setSoldTickets(bought);
	agency.setPackets(aux);
	agency.setPacketsInfoHasChanged(true);
}

void Change_PackAvailability_Menu(Agency &agency, int PackNumber)
{
	int packid;
	packid = agency.getPackets().at(PackNumber).getId();
	if (packid < 0)
	{
		cout << "That Pack is already unavaliable" << endl;
	}
	else
	{
		vector<Packet> aux = agency.getPackets();
		int newid;
		newid = -1 * agency.getPackets().at(PackNumber).getId();
		aux.at(PackNumber).setId(newid);
		agency.setPackets(aux);
		agency.setPacketsInfoHasChanged(true);
	}

}

void Add_Pack_Menu(Agency &agency)
{
	int PackNumber;
	int identifier = abs(agency.getPackets().back().getId()) + 1;
	string local;
	vector<string> localsvec;
	Date startdate;
	Date enddate;
	unsigned short startdateday, startdatemonth, enddateday, enddatemonth;
	unsigned int startdateyear, enddateyear;
	double price;
	unsigned int vagas;
	unsigned int vendas;
	Packet newpacket;
	vector<Packet> newvector;
	cout << "Enter the destination: ";
	cin.ignore(1000, '\n');
	getline(cin, local);
	localsvec = toVectorSites(local);
	cout << "Enter the start year: ";
	cin >> startdateyear;
	cout << "Enter the start month: ";
	cin >> startdatemonth;
	cout << "Enter the start day: ";
	cin >> startdateday;
	cout << "Enter the end year: ";
	cin >> enddateyear;
	cout << "Enter the end month: ";
	cin >> enddatemonth;
	cout << "Enter the end day: ";
	cin >> enddateday;
	startdate = Date(startdateday, startdatemonth, startdateyear);
	enddate = Date(enddateday, enddatemonth, enddateyear);
	if ((startdate.getYear() * 365 + startdate.getMonth() * 30 + startdate.getDay()) > (enddate.getYear() * 365 + enddate.getMonth() * 30 + enddate.getDay()))
	{
		cout << "The trip cannot start after it's over!" << endl;
	}
	else
	{
		cout << "Enter the price: ";
		cin >> price;
		cout << "Enter the starting availability: ";
		cin >> vagas;
		cout << "Enter the number of sold tickets: ";
		cin >> vendas;
		if (vendas > vagas)
		{
			cout << "The number of sold tickets cannot exceed availability!" << endl;
		}
		else
		{
			if ((vendas == vagas) && identifier >= 0)
			{
				identifier = identifier * (-1);
			}
			newpacket = Packet(identifier, localsvec, startdate, enddate, price, vagas, vendas);
			newvector = agency.getPackets();
			newvector.push_back(newpacket);
			agency.setPackets(newvector);
			agency.setPacketsInfoHasChanged(true);
		}
	}
}

void Remove_Pack_Menu(Agency &agency)
{
	int PackNumber;
	string chosenID;
	vector<Packet> aux = agency.getPackets();
	cout << "Available Packs: " << endl;
	cout << "---------------------------" << endl;
	for (unsigned int i = 0; i < agency.getPackets().size(); i++)
	{
		cout << "ID: " << agency.getPackets().at(i).getId() << endl;
		cout << "Destination: " << toStringSites(agency.getPackets().at(i).getSites()) << endl;
		cout << "---------------------------" << endl;
	}
	cout << "Enter the identifier of the pack you wish to remove: ";
	cin >> chosenID;
	cout << "=============================================" << endl;
	PackNumber = PackIDFinder(agency.getPackets(), chosenID);
	if (PackNumber == -1)
	{
		cout << "Invalid identifier!" << endl;
	}
	else
	{
		aux.erase(aux.begin() + PackNumber);
		agency.setPackets(aux);
		agency.setPacketsInfoHasChanged(true);
	}
}

void salesMenu(Agency &agency)
{
	unsigned int input2;
	cout << "[0] Exit" << endl;
	cout << "[1] Buy Pack(s)" << endl;
	cout << "[2] Pack Stats" << endl;
	cout << "Option: ";
	cin >> input2;
	cout << "=============================================" << endl;
	switch (input2)
	{
	case 0:
		break;
	case 1:
		buyPacksMenu(agency);
		break;
	case 2:
		packStatsMenu(agency);
		break;
	}
}

void buyPacksMenu(Agency &agency)
{
	string chosenNIF, chosenpack;
	int ClientNumber, PackNumber;
	vector<Client> ClientVector = agency.getClients();
	vector<Packet> PackVector = agency.getPackets();
	vector<string> auxP;
	cout << "Available Clients: " << endl;
	cout << "---------------------------" << endl;
	for (unsigned int i = 0; i < ClientVector.size(); i++)
	{
		cout << "Name: " << ClientVector.at(i).getName() << endl;
		cout << "NIF: " << ClientVector.at(i).getVATnumber() << endl;
		cout << "---------------------------" << endl;
	}
	cout << "Enter the NIF of the client: ";
	cin >> chosenNIF;
	ClientNumber = ClientFinder(ClientVector, chosenNIF);
	if (ClientNumber == -1)
	{
		cout << "Client not found!" << endl;
	}
	else
	{
		cout << "Available Packs: " << endl;
		cout << "---------------------------" << endl;
		for (unsigned int i = 0; i < PackVector.size(); i++)
		{
			cout << "ID: " << PackVector.at(i).getId() << endl;
			cout << "Destination: " << toStringSites(PackVector.at(i).getSites()) << endl;
			cout << "---------------------------" << endl;
		}
		cout << "Enter the identifier of the pack you wish to buy: ";
		cin >> chosenpack;
		PackNumber = PackIDFinder(PackVector, chosenpack);
		if (PackNumber == -1)
		{
			cout << "Invalid identifier!" << endl;
		}
		else
		{
			if (PackVector.at(PackNumber).getMaxPersons() < (PackVector.at(PackNumber).getSoldTickets() + ClientVector.at(ClientNumber).getFamilySize()))
			{
				cout << "There is not enough space!" << endl;
			}
			else 
				if (PackVector.at(PackNumber).getId() < 0)
				{
				cout << "Pack is not available!" << endl;
				}
				else
				{
					unsigned int newsold = PackVector.at(PackNumber).getSoldTickets() + ClientVector.at(ClientNumber).getFamilySize();
					PackVector.at(PackNumber).setSoldTickets(newsold);
					agency.setPackets(PackVector);
					agency.setPacketsInfoHasChanged(true);
					auxP = ClientVector.at(ClientNumber).getSTRPacketList();
					auxP.push_back(chosenpack);
					ClientVector.at(ClientNumber).setSTRPacketList(auxP);
					ClientVector.at(ClientNumber).setTotalPurchased(ClientVector.at(ClientNumber).getTotalPurchased() + ClientVector.at(ClientNumber).getFamilySize() * PackVector.at(PackNumber).getPricePerPerson());
					agency.setClients(ClientVector);
					agency.setClientInfoHasChanged(true);
					if ((PackVector.at(PackNumber).getMaxPersons() - PackVector.at(PackNumber).getSoldTickets()) == 0)
					{
						PackVector.at(PackNumber).setId(PackVector.at(PackNumber).getId() * (-1));
						agency.setPacketsInfoHasChanged(true);
					}
				}
		}
	}
}

void buyPackForAll(Agency &agency)
{
	vector<Packet> PackVector = agency.getPackets();
	vector<Client> ClientVector = agency.getClients();
	int chosenID, PackNumber;
	double newspent;
	vector<string> auxPacks;
	cout << "Available Packs: " << endl;
	cout << "---------------------------" << endl;
	for (unsigned int i = 0; i < PackVector.size(); i++)
	{
		cout << "ID: " << PackVector.at(i).getId() << endl;
		cout << "Destination: " << toStringSites(PackVector.at(i).getSites()) << endl;
		cout << "---------------------------" << endl;
	}
	cout << "Enter the identifier of the pack you wish to purchase for all clients: ";
	cin >> chosenID;
	PackNumber = PackIDFinder(PackVector, to_string(chosenID));
	unsigned int newsold = PackVector.at(PackNumber).getSoldTickets();
	if (PackNumber == -1)
	{
		cout << "Invalid identifier!" << endl;
	}
	if (ClientVector.size() > (PackVector.at(PackNumber).getMaxPersons() - PackVector.at(PackNumber).getSoldTickets()))
	{
		cout << "There is not enough space for everyone!" << endl;
	}
	else
	{
		for (unsigned int i = 0; i < ClientVector.size(); i++)
		{
			newsold += 1;
			auxPacks = ClientVector.at(i).getSTRPacketList();
			auxPacks.push_back(to_string(chosenID));
			newspent = ClientVector.at(i).getTotalPurchased() + PackVector.at(PackNumber).getPricePerPerson();
			ClientVector.at(i).setSTRPacketList(auxPacks);
			ClientVector.at(i).setTotalPurchased(newspent);
		}
		PackVector.at(PackNumber).setSoldTickets(newsold);
		agency.setClients(ClientVector);
		agency.setClientInfoHasChanged(true);
		agency.setPacketsInfoHasChanged(true);
	}
	if ((PackVector.at(PackNumber).getMaxPersons() - PackVector.at(PackNumber).getSoldTickets()) == 0)
	{
		PackVector.at(PackNumber).setId(PackVector.at(PackNumber).getId() * (-1));
		agency.setPacketsInfoHasChanged(true);
	}
}

void packStatsMenu(Agency &agency)
{
	int input;
	cout << "[0] Exit" << endl;
	cout << "[1] Total number of packs sold and profit" << endl;
	cout << "[2] Number of packs sold and profit for a specific pack" << endl;
	cout << "[3] Most visited places (ordered)" << endl;
	cout << "[4] Pack suggestions for each client" << endl;
	cout << "Option: ";
	cin >> input;
	cout << "=============================================" << endl;
	switch (input)
	{
	case(0):
	{
		break;
	}
	case(1):
	{
		Total_PacksSoldAndProfit_Menu(agency);
		break;
	}
	case(2):
	{
		Number_PacksSoldAndProfit_SpecificPack_Menu(agency);
		break;
	}
	case(3):
	{
		mostVisitedSitesMenu(agency);
		break;
	}
	case(4):
	{
		packSuggestionMenu(agency);
		break;
	}
	}
}

void Total_PacksSoldAndProfit_Menu(Agency &agency)
{
	int numpacks = 0;
	int profit = 0;
	for (unsigned int i = 0; i < agency.getPackets().size(); i++)
	{
		numpacks += agency.getPackets().at(i).getSoldTickets();
		profit += agency.getPackets().at(i).getSoldTickets() * agency.getPackets().at(i).getPricePerPerson();
	}
	cout << "Total number of packs sold: " << numpacks << endl;
	cout << "Total profit on the packs sold: " << profit << endl;
}

void Number_PacksSoldAndProfit_SpecificPack_Menu(Agency &agency)
{
	string chosenpack;
	int PackNumber;
	int numpacks;
	int profit;
	cout << "Available Packs: " << endl;
	cout << "---------------------------" << endl;
	for (unsigned int i = 0; i < agency.getPackets().size(); i++)
	{
		cout << "ID: " << agency.getPackets().at(i).getId() << endl;
		cout << "Destination: " << toStringSites(agency.getPackets().at(i).getSites()) << endl;
		cout << "---------------------------" << endl;
	}
	cout << "Enter the identifier of the pack: " << endl;
	cin >> chosenpack;
	PackNumber = PackIDFinder(agency.getPackets(), chosenpack);
	if (PackNumber == -1)
	{
		cout << "Invalid identifier!" << endl;
	}
	numpacks = agency.getPackets().at(PackNumber).getSoldTickets();
	profit = numpacks * agency.getPackets().at(PackNumber).getPricePerPerson();
	cout << "Number of packs sold: " << numpacks << endl;
	cout << "Profit on pack number " << chosenpack << ": " << profit << endl;
}

vector<string> mostVisitedSitesVector(Agency &agency)
{
	vector<string> result;
	map<string, unsigned int> sitesVisits;
	map<double, string> aux;
	double newkey;
	for (unsigned int i = 0; i < agency.getPackets().size(); i++)
	{
		if (agency.getPackets().at(i).getSites().size() == 1)
		{
			if (sitesVisits.find(agency.getPackets().at(i).getSites().at(0)) == sitesVisits.end())
			{
				sitesVisits[agency.getPackets().at(i).getSites().at(0)] = agency.getPackets().at(i).getSoldTickets();
			}
			else
			{
				sitesVisits[agency.getPackets().at(i).getSites().at(0)] += agency.getPackets().at(i).getSoldTickets();
			}
		}
		else
		{
			for (unsigned int j = 1; j < agency.getPackets().at(i).getSites().size(); j++)
			{
				if (sitesVisits.find(agency.getPackets().at(i).getSites().at(j)) == sitesVisits.end())
				{
					sitesVisits[agency.getPackets().at(i).getSites().at(j)] = agency.getPackets().at(i).getSoldTickets();
				}
				else
				{
					sitesVisits[agency.getPackets().at(i).getSites().at(j)] += agency.getPackets().at(i).getSoldTickets();
				}
			}
		}
	}
	for (map<string, unsigned int>::iterator it = sitesVisits.begin(); it != sitesVisits.end(); ++it)
	{
		if (aux.find(it->second) == aux.end())
			aux[it->second] = it->first;
		else
		{
			newkey = it->second;
			while (aux.find(newkey) != aux.end())
				newkey += 0.000001;
			aux[newkey] = it->first;
		}
	}
	for (map<double, string>::iterator it = aux.begin(); it != aux.end(); ++it)
		result.push_back(it->second);
	reverse(result.begin(), result.end());
	return result;
}

void mostVisitedSitesMenu(Agency &agency)
{
	unsigned int input;
	vector<string> sites = mostVisitedSitesVector(agency);
	cout << "Enter the number of top locations you wish to see (enter " << sites.size() << " for the full list): ";
	cin >> input;
	if (input > sites.size()) cout << "There are not that many locations!" << endl;
	else
	{
		for (unsigned int i = 0; i < input; i++)
			cout << (i + 1) << ". " << sites.at(i) << endl;
	}
}

void packSuggestionMenu(Agency &agency)
{
	vector<Client> ClientVector = agency.getClients();
	int PackNumber;
	vector<int> foundpacks;
	vector<string> aux;
	vector<string> mostvisited = mostVisitedSitesVector(agency);
	for (unsigned int i = 0; i < ClientVector.size(); i++)
	{
		aux.clear();
		foundpacks.clear();
		for (unsigned int j = 0; j < ClientVector.at(i).getSTRPacketList().size(); j++)
		{
			PackNumber = PackIDFinder(agency.getPackets(), ClientVector.at(i).getSTRPacketList().at(j));
			if (PackNumber != (-1))
			{
				if (agency.getPackets().at(PackNumber).getSites().size() == 1)
					aux.push_back(agency.getPackets().at(PackNumber).getSites().at(0));
				else
				{
					for (unsigned int k = 1; k < agency.getPackets().at(PackNumber).getSites().size(); k++)
					{
						aux.push_back(agency.getPackets().at(PackNumber).getSites().at(k));
					}
				}
			}
		}
		for (unsigned int j = 0; j < mostvisited.size(); j++)
		{
			if (find(aux.begin(), aux.end(), mostvisited.at(j)) == aux.end())
			{
				foundpacks = PackFinderDestin(agency.getPackets(), mostvisited.at(j));
				if (foundpacks.size() == 1)
				{
					cout << "Client: " << ClientVector.at(i).getName() << ", NIF: " << ClientVector.at(i).getVATnumber() << ":" << endl;
					cout << "There is only 1 pack with the recommended destination (" << mostvisited.at(j) << ")" << endl;
					cout << "Recomendation:" << endl;
					cout << agency.getPackets().at(foundpacks.at(0)).getId() << endl;
					cout << toStringSites(agency.getPackets().at(foundpacks.at(0)).getSites()) << endl;
					cout << toStringDate(agency.getPackets().at(foundpacks.at(0)).getBeginDate()) << endl;
					cout << toStringDate(agency.getPackets().at(foundpacks.at(0)).getEndDate()) << endl;
					cout << agency.getPackets().at(foundpacks.at(0)).getPricePerPerson() << endl;
					cout << agency.getPackets().at(foundpacks.at(0)).getMaxPersons() << endl;
					cout << agency.getPackets().at(foundpacks.at(0)).getSoldTickets() << endl;
					cout << "=============================================" << endl;
				}
				if (foundpacks.size() > 1)
				{
					cout << "Client: " << ClientVector.at(i).getName() << ", NIF: " << ClientVector.at(i).getVATnumber() << ":" << endl;
					cout << "There are " << foundpacks.size() << " packs with the recommended destination for this client. (" << mostvisited.at(j) << ")" << endl;
					cout << "Recommendation:" << endl;
					cout << agency.getPackets().at(foundpacks.at(0)).getId() << endl;
					cout << toStringSites(agency.getPackets().at(foundpacks.at(0)).getSites()) << endl;
					cout << toStringDate(agency.getPackets().at(foundpacks.at(0)).getBeginDate()) << endl;
					cout << toStringDate(agency.getPackets().at(foundpacks.at(0)).getEndDate()) << endl;
					cout << agency.getPackets().at(foundpacks.at(0)).getPricePerPerson() << endl;
					cout << agency.getPackets().at(foundpacks.at(0)).getMaxPersons() << endl;
					cout << agency.getPackets().at(foundpacks.at(0)).getSoldTickets() << endl;
					cout << "=============================================" << endl;
				}
				break;
			}
			else 
			{
				if (j == mostvisited.size() - 1)
				{
					cout << "Client: " << ClientVector.at(i).getName() << ", NIF: " << ClientVector.at(i).getVATnumber() << ":" << endl;
					cout << "There are no recommendations for this client (probably visited every location available)" << endl;
					cout << "=============================================" << endl;
				}
			}
		}
	}
}

bool runCheck()
{
	bool input = false;
	unsigned int finalinput;
	cin.clear();
//	cin.ignore(1000, '\n');
	cout << "=============================================" << endl;
	cout << "Do you wish to do anything else?" << endl;
	cout << "[1] Yes" << endl;
	cout << "[2] No" << endl;
	cout << "Option: ";
	cin >> finalinput;
	if (finalinput == 2)
		input = false;
	else
	{
		if (finalinput == 1) input = true;
		else
		{
			cout << "Invalid input!" << endl;
		}
	}
	cout << "=============================================" << endl;
	return input;
}

void firstMenu(Agency &agency) {
	unsigned int input;
	cout << "========== Travel Agency Program ============" << endl;
	cout << "[0] Exit" << endl;
	cout << "[1] Clients Menu" << endl;
	cout << "[2] Packs Menu" << endl;
	cout << "[3] Sales Menu" << endl;
	cout << "Option: ";
	cin >> input;
	cout << "=============================================" << endl;
	switch (input)
	{
		case 0:
			break;
		case 1:
		{
			ClientsMainMenu(agency);
			break;
		}
		case 2:
		{
			PacksMainMenu(agency);
			break;
		}
		case 3:
		{
			salesMenu(agency);
			break;
		}
	}
}