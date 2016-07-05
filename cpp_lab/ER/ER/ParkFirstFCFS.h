#pragma once
#include "const.h"
#include "Strategy.h"
class PhysicianList;
class PatientList;

class ParkFirstFCFS : public Strategy
{
public:
	ParkFirstFCFS();
	virtual ~ParkFirstFCFS();
	virtual void ChangePatients(PhysicianList* dList, PatientList* pList);
};

