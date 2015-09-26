#pragma once

#include <vector>
#include "Vehicle.h"
#include "Truck.h"
#include "RiverBarge.h"

using namespace std;

class Company
{
private :
	static Company * instance;
	Company(){};
	~Company()
	{
//		for(vector<Vehicle*>::iterator i = listOfVehicle.begin();
//			i != listOfVehicle.end();	i++)
//		{
//			delete i ; //error	//  I worried about delete memory this......
//		} 
		listOfVehicle.clear();
	};
	
public :
	static Company* getCompany();
	vector<Vehicle*> listOfVehicle;
	void addVehicle(Vehicle* v);
};

