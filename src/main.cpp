#include <iostream>
#include <string>
#include <vector>
#include "Agency.h"
#include "Menus.h"
#include "Client.h"
#include "Packet.h"
#include "Date.h"
#include "Address.h"

// #include "utils.h"


int main(){
  Agency agency(AGENCY_FILE_NAME);   // create the agency
  bool isProgramRunning = true;
  while (isProgramRunning) 
  {
	  agency.setClientInfoHasChanged(false);
	  agency.setPacketsInfoHasChanged(false);
	  mainMenu(agency); // initial menu inicial with the major options of the application
	  isProgramRunning = runCheck(); // checks if the program is supposed to keep running
	  if (agency.getClientInfoHasChanged() == 1)
	  {
		  cout << "Saving changes in the clients file..." << endl;
		  UpdateClientFile(agency.getClientsFile(), agency);
		  cout << "Saved successfully!" << endl;
	  }
	  if (agency.getPacketsInfoHasChanged() == 1)
	  {
		  cout << "Saving changes in the packets file..." << endl;
		  UpdatePackFile(agency.getPacketsFile(), agency);
		  cout << "Saved successfully!" << endl;
		  cout << "=============================================" << endl;
	  }
  }
   return 0;
}
