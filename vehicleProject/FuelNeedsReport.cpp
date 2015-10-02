#include <iostream>
#include "FuelNeedsReport.h"

using namespace std;

void FuelNeedsReport::showReport(Company* company)
{
	double total = 0;
	
	for( int i = 0; i< company->listOfVehicle.size() ; i++)
	{
		Vehicle* v = company->listOfVehicle.at(i);
		total += v->calcFuelNeeds();
		
		cout<<"\t"<<v->calcFuelNeeds()<<endl;
	}
	
	cout<<"Total fuel : "<<total<<endl;
}
