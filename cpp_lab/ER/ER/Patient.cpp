#include "Patient.h"

using namespace std;

Patient::Patient(int makeTime, const char * name, int age, char sex, const char * cc, const char * disease, int dtime, int extime) :makeTime(makeTime), patientAge(age), patientSex(sex), diagnosticTime(dtime), expireTime(extime), waitedTime(0), status(PATIENT::HEALTHY)
{
	strcpy_s(patientName, name);
	strcpy_s(cheifComplaint, cc);
	strcpy_s(diseaseName, disease);

	discharged = false;
	expired = false;
}


Patient::~Patient()
{
}

void Patient::treated()
{
	if (status == PATIENT::DEAD || status == PATIENT::DISCHARGED || status == PATIENT::HEALTHY)
		return;

	if (expireTime > 0)
		expireTime--;
	if( diagnosticTime > 0)
		diagnosticTime--;

	if (expireTime == 0)
		expire();
	else if (diagnosticTime <= 0)
		discharge();
}

void Patient::wait()
{
	if (status == PATIENT::DEAD || status == PATIENT::DISCHARGED || status == PATIENT::HEALTHY)
		return;

	waitedTime++;
	if (expireTime > 0)
		expireTime--;
	else if (expireTime == 0)
		expire();
}

void Patient::expire()
{
	if (status == PATIENT::DEAD || status == PATIENT::DISCHARGED || status == PATIENT::HEALTHY )
		return;

	status = PATIENT::DEAD;

	cout << patientName << " is expired." << endl;

	Hospital* hospital = Hospital::getInstance();
	hospital->Expire(this); 
	
	expired = true;
}

void Patient::discharge()
{
	if (status == PATIENT::DEAD || status == PATIENT::DISCHARGED )
		return;

	status = PATIENT::DISCHARGED;

	Hospital* hospital = Hospital::getInstance();
	
	if (hospital->Discharge(this) < 0)
		return;

	cout << patientName << " is discharged." << endl;
	discharged = true;

}

bool Patient::isTimeToAche(int time)
{ 
	if (this->makeTime == time)
	{
		this->status = PATIENT::WAIT;
		return true;
	}
	else
		return false;
}

int Patient::getMakeTime()
{
	return makeTime;
}

void Patient::showInfo()
{
	if (this != NULL){
		cout << this->makeTime << "min " << this->patientName << " " << this->cheifComplaint << " " << this->patientAge << this->patientSex << " Ex" << this->expireTime << ", Dx" << this->diagnosticTime << ", W" << this->waitedTime << " " << status << endl;
	}
}

bool Patient::operator==(const Patient* &p1)
{
	if (strcmp(this->patientName, p1->patientName))
		return true;
	else
		return false;
}

Patient * Patient::operator=(Patient * p)
{
	return p;
}

const char* Patient::getCC()
{
	return this->cheifComplaint;
}

const char* Patient::getName()
{
	return this->patientName;
}

ostream& operator<<(ostream& os, enum PATIENT::STATUS status)
{
	if (status == PATIENT::DEAD)
		os << "DEAD";
	else if (status == PATIENT::DISCHARGED)
		os << "Discharged";
	else if (status == PATIENT::HEALTHY)
		os << "Healthy";
	else if (status == PATIENT::TREATING)
		os << "Treatig";
	else if (status == PATIENT::WAIT)
		os << "waiting";
	else
		os << " wring status";

	return os;
}

ostream& operator<<(ostream& os, const Patient* p)
{
	if (p != NULL)
		os << p->patientName <<"("<<p->cheifComplaint<<")";
	else
		os << "NULL";
	return os;
}
