#include "Hospital.h"
#include "Strategy.h"
#include "PhysicianList.h"
#include "PatientList.h"
using namespace std;

Hospital * Hospital::instance = new Hospital();

Hospital::Hospital() : docList()
{
	docList = new PhysicianList("D.List");
	emergencyRoom = new PatientList("ER");
	waiting = new PatientList("Ward");
}


Hospital::~Hospital()
{
	cout << "~hospital()" << endl;
}


void Hospital::Select( Strategy* strategy)
{
	cout << "Select()" << endl;
	strategy->ChangePatients(docList, waiting);
}

void Hospital::timeSpend()
{
	waiting->wait();

	for (int i = 0; i < docList->size(); i++)
	{
		if(docList->Get(i) != NULL)
			docList->Get(i)->treat();
	}
	cout << "Time spend()" << endl;
}

void Hospital::admission(Patient * p)
{
	waiting->Add(p);
}

int Hospital::Discharge(Patient* p)
{
	int id = emergencyRoom->GetId(p);
	if (id < 0) {
		cerr << "Can;t find Patient in ER" << endl;
		return -1;
	}

	Patient* popP = emergencyRoom->Pop(id);
	if (popP != p)
	{
		cerr << "pop err" << endl;
		return -1;
	}
	
	return 0;
}

int Hospital::Expire(Patient* p)
{
	if (p == NULL) {
		cerr << "Who is expired?" << endl;
		return -1;
	}

	int id = waiting->GetId(p);
	if (id < 0) {
		if (docList->Pop(p) != NULL) {
			return 0;
		}
		return -1;
	}
	else {
		Patient* popP = waiting->Pop(id);
		if (popP == NULL)
			return -1;
		if (popP == p)
			return 0;
		else
			return -1;
	}
}



Hospital * Hospital::getInstance()
{
	if (instance == NULL)
		instance = new Hospital();
	return instance;
}
