#include "Date.h"
#include "Agency.h"
#include "Client.h"
#include "Packet.h"
#include "Address.h"

Date::Date(){
}

Date::Date(string date){
  
	string aux;
	year = stoi(date.substr(0, date.find('/')), nullptr, 10);
	aux = date.erase(0, date.find('/') + 1);
	month = stoi(aux.substr(0, date.find('/')), nullptr, 10);
	aux = aux.erase(0, date.find('/') + 1);
	day = stoi(aux, nullptr, 10);
}


Date::Date(unsigned short nday, unsigned short nmonth, unsigned nyear){

	day = nday;
	month = nmonth;
	year = nyear;
}

/*********************************
 * GET Methods
 ********************************/
unsigned short Date::getDay() const{

	return day;

}

  
unsigned short Date::getMonth() const{

	return month;

}
    
unsigned Date::getYear() const{

	return year;

}

/*********************************
 * SET Methods
 ********************************/

void Date::setDay(unsigned short nday){
  
	day = nday;
}
void Date::setMonth(unsigned short nmonth){
  
	month = nmonth;
}

void Date::setYear(unsigned nyear){

	year = nyear;
}


/*********************************
 * Show Date
 ********************************/  

// disply a Date in a nice format
ostream& operator<<(ostream& out, const Date & date){

	out << to_string(date.year) << "/" << to_string(date.month) << "/" << to_string(date.day);
	return out;
}
