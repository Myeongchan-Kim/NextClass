#pragma once
#include <iostream>
#include "ArrayList.h"
#include "Physician.h"
class Patient;

class PhysicianList : public ArrayList<Physician*>
{
public:
	PhysicianList(const char* name = "Ph.List", int max = 3);
	~PhysicianList();
	Patient* Pop(Patient* p);
	Patient* Change(int i, Patient* p);
	bool isNoPatient();
	void deleteAllPhysicianAndList();
};

