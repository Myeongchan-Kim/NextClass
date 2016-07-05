#pragma once
#include "Vehicle.h"

class Truck : public Vehicle
{
private:
	// this vehicle consume more Fuel.
	// So you have to add 10% of total fuel consumtion
	static const double additionalFuelEfficiency= 1.1;
	
public :
	Truck( double , double);
	~Truck();
	virtual double calcFuelNeeds();
};

