#pragma once
#include "const.h"
#include "Strategy.h"
class PhysicianList;
class PatientList;

class FCFS : public Strategy
{
public:
	FCFS();
	virtual ~FCFS();
	virtual void ChangePatients(PhysicianList* dList, PatientList* pList);
};
