#pragma once

#include "Agency.h"
#include "Address.h"
#include <fstream>
#include <map>


void mainMenu(Agency &agency);
void firstMenu(Agency &agency);

// Useful functions

bool runCheck();
string AddressToString(Address adrs);
string toStringSites(vector<string> vector);
string toStringDate(Date date);
string toStringSites(vector<string> vector);
int PackIDFinder(vector<Packet> PackVector, string chosenID);
vector<int> PackFinderDestin(vector<Packet> PackVector, string destination);
vector<int> PackFinderDate(vector<Packet> PackVector, int startt, int endt);

// File Updaters

void UpdateClientFile(string filename, Agency agency);
void UpdatePackFile(string filename, Agency agency);

// Clients

int ClientFinder(vector<Client> ClientVector, string ClientNIF); // encontra o index do cliente com o NIF desejado no vector de clientes
void ClientsDetailsMenu(Agency &agency);
void SpecificClientMenu(Agency &agency);
void AllClientsMenu(Agency &agency);
void Change_Clients_Details_Menu(Agency &agency);
void Change_Name_Menu(Agency &agency, int ClientNumber);
void change_NIF_menu(Agency &agency, int ClientNumber);
void change_FamilySize_menu(Agency &agency, int ClientNumber);
void change_Address_menu(Agency &agency, int ClientNumber);
void change_Everything_menu(Agency &agency, int ClientNumber);
void change_Street_menu(Agency &agency, int ClientNumber);
void change_Door_menu(Agency &agency, int ClientNumber);
void change_Floor_menu(Agency &agency, int newfloor);
void change_PostalCode_menu(Agency &agency, int ClientNumber);
void change_City_menu(Agency &agency, int ClientNumber);
void add_client_menu(Agency &agency);
void remove_client_menu(Agency &agency);
void ClientsMainMenu(Agency &agency);

// Packs

void PacksMainMenu(Agency &agency);
void Pack_Details_Menu(Agency &agency);
void Search_Packs_Menu(Agency &agency);
void Search_PackBoughtByClient_Menu(Agency &agency, vector<int> foundpacks);
void Search_PacksByDestination_Menu(Agency &agency, vector<int>foundpacks);
void Search_PacksByDate_Menu(Agency &agency, vector<int>foundpacks);
void Search_PacksByDestinationAndDate_Menu(Agency &agency, vector<int>foundpacks, vector<int>foundpacks2);
void AllPacks_Menu(Agency &agency);
void Change_PackDetails_Menu(Agency &agency);
void Change_PackDestiation_Menu(Agency &agency, int PackNumber);
void Change_PackStartDate_Menu(Agency &agency, int PackNumber);
void Change_PackEndDate_Menu(Agency &agency, int PackNumber);
void Change_PackPrice_Menu(Agency &agency, int PackNumber);
void Change_PackStartingAvialability_Menu(Agency &agency, int PackNumber);
void Change_PackSoldTickets_Menu(Agency &agency, int PackNumber);
void Add_Pack_Menu(Agency &agency);
void Remove_Pack_Menu(Agency &agency);
void Change_PackAvailability_Menu(Agency &agency, int PackNumber);

// Sales and stats

void packStatsMenu(Agency &agency);
void buyPacksMenu(Agency &agency);
void salesMenu(Agency &agency);
void Number_PacksSoldAndProfit_SpecificPack_Menu(Agency &agency);
void Total_PacksSoldAndProfit_Menu(Agency &agency);
void mostVisitedSitesMenu(Agency &agency);
void packSuggestionMenu(Agency &agency);
vector<string> mostVisitedSitesVector(Agency &agency);
