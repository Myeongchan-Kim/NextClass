#pragma once
#include "Vehicle.h"


class RiverBarge : public Vehicle
{
private:
	// this vehicle consume more Fuel.
	// So you have to add 10% of total fuel consumtion
	static const double additionalFuelEfficiency = 1.2;

public :
	RiverBarge( double , double);
	~RiverBarge();
	virtual double calcFuelNeeds();
};

