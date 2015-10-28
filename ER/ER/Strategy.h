#pragma once
#include "const.h"
class PatientList;
class PhysicianList;

class Strategy
{
private:

public:
	Strategy();
	virtual ~Strategy();
	virtual void ChangePatients(PhysicianList * dList, PatientList * pList) = 0;
};

