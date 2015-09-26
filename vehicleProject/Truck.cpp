#include "Truck.h"

using namespace std;

Truck::Truck( double tripDistance, double fuelEfficiency) : Vehicle(tripDistance, fuelEfficiency){};
Truck::~Truck(){};

double Truck::calcFuelNeeds()
{
	//cout<<"truck calc"<<endl;
	return Vehicle::calcTripDistance()/Vehicle::calcFuelEfficiency()* Truck::additionalFuelEfficiency;
}

