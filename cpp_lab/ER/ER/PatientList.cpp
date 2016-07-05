#include "PatientList.h"
using namespace std;

PatientList::PatientList(const char* name,int max):ArrayList(name, max)
{
}


PatientList::~PatientList()
{
	for (int i = 0; i < size(); i++)
	{
	//	delete list[i];
	}
}

void PatientList::wait()
{
	for (int i = 0; i < size(); i++)
	{
		list[i]->wait();
	}
}

ostream& operator<<(ostream& os, PatientList& pList)
{
	for (int i = 0; i < pList.size(); i++)
		pList.Get(i)->showInfo();
	return os;
}
