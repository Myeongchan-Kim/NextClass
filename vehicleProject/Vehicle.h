#pragma once
#include <iostream>
using namespace std;

class Vehicle
{
protected:
	
	// distance is total trip distance of this vehicle.
	double distance;
	
	// fuelEfficiency is a fuel efficiency of this vehicle.
	// This is equal to (total trip distance)/(total fuel consumtion) 
	double fuelEfficiency;
	static const double additionalFuelEfficiency = 1.0;
public:
	Vehicle(double d, double e):distance(d), fuelEfficiency(e)
	{
		cout<<"new Vehicle! ("<<d<<", "<<e<<")"<<endl;
	};
	~Vehicle(){};
	
public:
	virtual double calcFuelNeeds();
	virtual double calcTripDistance();
	virtual double calcFuelEfficiency();
};

inline double Vehicle::calcFuelNeeds(){
	// calcFuelNeeds is a function to calculation of total fuel that this vehicle need.
	// Fuel efficiency = (total trip distance)/(total fuel consumtion) 
	// So, needs of fuel = (TripDistance)/(FuelEfficiency)
	return calcTripDistance()/calcFuelEfficiency()*additionalFuelEfficiency;
}

inline double Vehicle::calcTripDistance(){
	return distance;
}

inline double Vehicle::calcFuelEfficiency(){
	return fuelEfficiency;
}
