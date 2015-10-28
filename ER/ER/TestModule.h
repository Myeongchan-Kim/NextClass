#pragma once
#include "PatientList.h"
#include "PatientGenerater.h"
class Hospital;
class Strategy;

class TestModule
{
private:
	PatientGenerater* community;
	Hospital* singletonHospital;
	Strategy* mainStrategy;
	int m_time;
	int m_maxTime;
	void ShowCurrentInfo();
public:
	TestModule(Strategy* mainStr, int physician_num = 3, const int maxTime = 100, const char * fileName = "SamplePatientList.csv");
	~TestModule();
	void Run();
	void processing();
};
