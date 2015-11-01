#include "PhysicianList.h"
using namespace std;

PhysicianList::PhysicianList(const char * name , int max):ArrayList(name, max)
{
	Physician* doc = new Physician("Dr.Kim");
	Add(doc);
	doc = new Physician("Dr.Lee");
	Add(doc);
	doc = new Physician("Dr.Park");
	Add(doc);

	cout << size() << " Doctors are created." << endl;
}


PhysicianList::~PhysicianList()
{

}

void PhysicianList::deleteAllPhysicianAndList()
{
	for (int i = 0; i < size(); i++)
	{
		delete list[i];
	}

	delete[] list;
}

Patient* PhysicianList::Pop(Patient* p)
{
	for (int i = 0; i < size(); i++)
	{
		if (list[i]->getMyPatient() == p) {
			list[i]->Bye();
			return p;
		}
	}
	return NULL;
}


Patient* PhysicianList::Change(int i, Patient * p)
{
	return Get(i)->Change(p);
}

bool PhysicianList::isNoPatient()
{
	for (int i = 0; i < size(); i++)
	{
		if (list[i]->getMyPatient() != NULL) {
			return false;
		}
	}
	return true;
}