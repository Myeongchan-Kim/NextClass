#pragma once
#include <iostream>
#include "const.h"
using namespace std;

class PatientList;
class PhysicianList;
class Physician;

class Strategy
{
private:

public:
	Strategy();
	virtual ~Strategy();
	virtual void showStartSelectingLog(Physician* doc);
	virtual void ChangePatients(PhysicianList * dList, PatientList * pList) = 0;
};

