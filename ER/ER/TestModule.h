#pragma once
#include "PatientList.h"
#include "PatientGenerater.h"
#include "Reporter.h"
class Hospital;
class Strategy;

namespace MODULE_CONST
{
	const int MAX_TIME = 100;
	const char* const DEFULAT_PATIENT_FILE_NAME = "SamplePatientList.csv";
}

class TestModule
{
private:
	PatientGenerater* community;
	Hospital* singletonHospital;
	Strategy* mainStrategy;
	Reporter* report;
	int m_time;
	int m_maxTime;
	void ShowCurrentInfo();
public:
	TestModule(Strategy* mainStr, int physician_num = 3, const int maxTime =MODULE_CONST::MAX_TIME, const char * fileName = MODULE_CONST::DEFULAT_PATIENT_FILE_NAME);
	~TestModule();
	void Run();
	void processing();
	void sendInfo(Reporter* report);
};
