#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <cmath>
#include <fstream>
#include <cstring>
#include "Patient.h"
#include "PatientList.h"
#include "Hospital.h"

class PatientGenerater
{
private:
	PatientList* pList;

public:
	PatientGenerater(const char * fileName);
	~PatientGenerater();
	void SendPatient(Patient* p, Hospital * hospital);
	void SendPatients(const int time, Hospital* hospital);
};