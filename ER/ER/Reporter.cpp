#include "Reporter.h"
#include "TestModule.h"

Reporter::Reporter()
{
}


Reporter::~Reporter()
{
}

void Reporter::makeReport(const TestModule *test)
{
	Hospital* hospital = Hospital::getInstance();
	cout << *hospital->getEmergencyRoom() << endl;
	cout << "Expire : " << hospital->getExpireCount() << endl;
	cout << "DOA : " << hospital->getDOACount() << endl;
	cout << "Discharge : " << hospital->getDischargeCount() << endl;
	
}