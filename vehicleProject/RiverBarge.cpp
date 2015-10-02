#include "RiverBarge.h"

using namespace std;

RiverBarge::RiverBarge( double tripDistance, double fuelEfficiency) : Vehicle(tripDistance, fuelEfficiency){};
RiverBarge::~RiverBarge(){};

double RiverBarge::calcFuelNeeds()
{
	//cout<<"RB calc"<<endl;
	return Vehicle::calcTripDistance()/Vehicle::calcFuelEfficiency()* RiverBarge::additionalFuelEfficiency;
}
