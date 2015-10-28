#include "Patient.h"

using namespace std;

Patient::Patient(int makeTime, const char * name, int age, char sex, const char * cc, const char * disease, int dtime, int extime):makeTime(makeTime),patientAge(age),patientSex(sex) ,diagnosticTime(dtime), expireTime(extime), waitedTime(0)
{
	strcpy_s(patientName, name);
	strcpy_s(cheifComplaint, name);
	strcpy_s(diseaseName, name);

	discharged = false;
	expired = false;
}


Patient::~Patient()
{
}

void Patient::treated()
{
	if (expired == true)
		return;

	expireTime--;
	diagnosticTime--;

	if (expireTime == 0)
		expire();
	else if (diagnosticTime <= 0)
		discharge();
}

void Patient::wait()
{
	waitedTime++;
	expireTime--;
	if (expireTime == 0)
		expire();
}

void Patient::expire()
{
	if (expired == true)
		return;

	cout << patientName << "is expired." << endl;

	Hospital* hospital = Hospital::getInstance();
	hospital->Expire(this); 
	
	expired = true;
}

void Patient::discharge()
{
	if (discharged == true)
		return;
	
	Hospital* hospital = Hospital::getInstance();
	
	if (hospital->Discharge(this) < 0)
		return;

	cout << patientName << "is discharged." << endl;
	discharged = true;

}

bool Patient::isTimeToAche(int time)
{ 
	if (this->makeTime == time)
		return true;
	else
		return false;
}

int Patient::getMakeTime()
{
	return makeTime;
}

void Patient::showInfo()
{
	cout << patientName << endl;
}



Patient * Patient::operator=(Patient * p)
{
	return p;
}


ostream& operator<<(ostream& os, const Patient* p)
{
	os << p->makeTime <<"min " <<p->patientName << " " << p->patientAge << p->patientSex << " " << p->expireTime << "," <<p->diagnosticTime <<","<< p->waitedTime << endl;
	return os;
}

