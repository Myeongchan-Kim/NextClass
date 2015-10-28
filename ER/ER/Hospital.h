#pragma once
class Patient;
class PatientList;
class PhysicianList;
class Strategy;

class Hospital
{
private:
	PhysicianList* docList;
	PatientList* emergencyRoom; // room for 
	PatientList* waiting;

	static Hospital* instance;
	Hospital();
public:
	~Hospital();
	void Select(Strategy* strategy);
	void timeSpend();
	void admission(Patient* p);
	int Discharge(Patient* p);
	int Expire(Patient* p);
	static Hospital* getInstance();
};

