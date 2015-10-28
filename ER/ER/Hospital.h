#pragma once
class Patient;
class PatientList;
class PhysicianList;
class Strategy;
class Reporter;

class Hospital
{
private:
	PhysicianList* docList;
	PatientList* emergencyRoom; // room for 
	PatientList* waiting;

	int expireCount;
	int dischargeCount;

	static Hospital* instance;
	Hospital();
public:
	~Hospital();
	void Select(Strategy* strategy);
	void timeSpend();
	void admission(Patient* p);
	int Discharge(Patient* p);
	int Expire(Patient* p);

	void makeReport(Reporter* p);
	bool isEmpty();
	static Hospital* getInstance();
};

