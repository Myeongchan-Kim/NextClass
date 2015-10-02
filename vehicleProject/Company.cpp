#include "Company.h"

Company* Company::instance;

Company* Company::getCompany(){
	if(Company::instance == 0)
		Company::instance = new Company();
	return Company::instance;
}


void Company::addVehicle(Vehicle* v){
	listOfVehicle.push_back(v);
}


