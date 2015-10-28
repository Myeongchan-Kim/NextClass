#include "Physician.h"
#include "Patient.h"

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
	return tmp;
}

