#pragma once
#include <iostream>
#include "ArrayList.h"
#include "Patient.h"

using namespace std;

class PatientList: public ArrayList<Patient*>
{
public:
	PatientList(const char* name = "PatientList", int max = 10);
	~PatientList();
	void wait();

	friend ostream& operator<<(ostream& os, PatientList& pList);
};

