#include <iostream>
#include "Physician.h"
#include "Patient.h"
using namespace std;

Physician::Physician(const char* name)
{
	strcpy_s(m_name, name);
	myPatient = NULL;
}


Physician::~Physician()
{
}

void Physician::treat()
{
	if( myPatient != NULL)
		myPatient->treated();
}

void Physician::Bye()
{
	myPatient = NULL;
}

Patient* Physician::getMyPatient()
{
	return myPatient;
}

Patient*  Physician::Change(Patient * p )
{
	Patient* tmp = myPatient;
	myPatient = p;
	if (tmp != NULL && myPatient != NULL)
		cout << tmp << "->" << myPatient << endl;
	else if (myPatient != NULL)
		cout << "NULL->" << myPatient << endl;
	return tmp;
}

ostream& operator<<(ostream& os, Physician* doctor){
	os << doctor->m_name;
	return os;
}