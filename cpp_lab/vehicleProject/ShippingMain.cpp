#include "ShippingMain.h"

int main(int argc, char** argv) {
	
	Company * company = Company::getCompany();
	
	Truck* t = new Truck(300, 30);
	company->addVehicle(t);
	t = new Truck(100, 20);
	company->addVehicle(t);
	t = new Truck(200, 10);
	company->addVehicle(t);
	
	RiverBarge* r = new RiverBarge(100, 5);
	company->addVehicle(r);
	r = new RiverBarge(500, 5);
	company->addVehicle(r);
	
	FuelNeedsReport report = FuelNeedsReport();
	report.showReport(company);
	
	return 0;
}
