#include "TestModule.h"
using namespace std;


void TestModule::ShowCurrentInfo()
{
	// ...?
}

TestModule::TestModule( Strategy* str, 
	int physician_num, const int maxTime, const char * fileName) :m_maxTime(maxTime),  mainStrategy(str)
{
	community = new PatientGenerater(fileName);
	singletonHospital = Hospital::getInstance();
	report = new Reporter();
	m_time = 0;
};


TestModule::~TestModule()
{
	community->deletePatient();
	singletonHospital->deleteAllList();
	delete mainStrategy;
}

void TestModule::processing()
{
	//New Patient Generating
}

void TestModule::Run()
{
	cout << "--------Test Start---------" << endl;

	while (m_time <= m_maxTime )
	{
		cout << "**** Time:" << m_time << " ****"<<endl;
		
		community->SendPatients(m_time, singletonHospital);
		
		//hospital select patient
		singletonHospital->Select(mainStrategy);

		//some patients are waiting, starving, treating, expiring....
		singletonHospital->timeSpend();
		
		if (community->isAllSended() && singletonHospital->isEmpty()){
			cout << "No more Patient." << endl;
			this->sendInfo(report);
			cout << endl;
			break;
		}

		cout << endl;
		m_time++;
	}
	if (m_time > m_maxTime)
	{
		cout << "Max time over." << endl;
		this->sendInfo(report);
		cout << endl;
	}

	cout << "--------Test Finished---------" << endl;
}

void TestModule::sendInfo(Reporter *report)
{
	report->makeReport(this);
}