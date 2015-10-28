#pragma once
#include <iostream>
#include <cstring>
#include "const.h"
#include "Hospital.h"
using namespace std;

class Patient
{
private:
	int makeTime;
	char patientName[STRLEN::MAX_NAME_LEN];
	int patientAge;
	char patientSex; //M=male , F=female.
	char cheifComplaint[STRLEN::MAX_NAME_LEN];
	char diseaseName[STRLEN::MAX_NAME_LEN];
	int diagnosticTime;
	int expireTime;
	int waitedTime;
	bool discharged;
	bool expired;

public:
	Patient(int makeTime = 0, const char * name = "noname", int age = 0, char sex = 'M', const char * cc = "", const char * disease = "", int dtime = 1, int extime = -1);
	~Patient();
	void treated();
	void wait();
	void expire();
	void discharge();
	bool isTimeToAche(int time);
	int getMakeTime();
	void showInfo();

	Patient* operator=(Patient* p);
	friend ostream& operator<<(ostream& os, const Patient* p);
};

