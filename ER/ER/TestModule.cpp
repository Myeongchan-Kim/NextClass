#include "TestModule.h"
using namespace std;


void TestModule::ShowCurrentInfo()
{
	cout << "info" << endl;
}

TestModule::TestModule( Strategy* str, 
	int physician_num, const int maxTime, const char * fileName) :m_maxTime(maxTime),  mainStrategy(str)
{
	community = new PatientGenerater(fileName);
	singletonHospital = Hospital::getInstance();
	m_time = 0;
};


TestModule::~TestModule()
{
	delete community;
}

void TestModule::processing()
{
	//New Patient Generating
}

void TestModule::Run()
{
	cout << "--------Test Start---------" << endl;

	while (m_time <= m_maxTime)
	{
		cout << "Time:" << m_time << endl;
		
		community->SendPatients(m_time, singletonHospital);
		
		//hospital select patient
		singletonHospital->Select(mainStrategy);

		//some patients are waiting, starving, treating, expiring....
		singletonHospital->timeSpend();
		
		m_time++;
	}

	cout << "--------Test Finished---------" << endl;
}
