#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <cmath>
#include <fstream>
#include <cstring>
#include "Patient.h"
#include "PatientList.h"
#include "Hospital.h"
using namespace std;

class PatientGenerater
{
private:
	PatientList* pList;
	int sendedPatientsNum;

public:
	PatientGenerater(const char * fileName);
	~PatientGenerater();
	void SendPatient(Patient* p, Hospital * hospital);
	bool isAllSended();
	void SendPatients(const int time, Hospital* hospital);
	void deletePatient();
};