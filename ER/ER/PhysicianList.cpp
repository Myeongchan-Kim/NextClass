#include "PhysicianList.h"
using namespace std;

PhysicianList::PhysicianList(const char * name , int max):ArrayList(name, max)
{
	for (int i = 0; i < max; i++)
	{
		Physician* doc = new Physician();
		Add(doc);
	}

	cout << size() << " Doctors are created." << endl;
}


PhysicianList::~PhysicianList()
{
	for (int i = 0; i < size(); i++)
	{
		//delete list[i];
	}
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
