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
	PatientList* emergencyRoom; // all enter patient 
	PatientList* waiting;

	int expireCount;
	int dischargeCount;
	int DOACount;

	static Hospital* instance;
	Hospital();
public:
	~Hospital();
	void Select(Strategy* strategy);
	void timeSpend();
	void admission(Patient* p);
	int Discharge(Patient* p);
	int Expire(Patient* p);

	void sendInfo(Reporter* p);
	bool isEmpty();
	int getExpireCount() const;
	int getDOACount() const;
	int getDischargeCount() const;
	PatientList* getEmergencyRoom() const;
	void deleteAllList();

	static Hospital* getInstance();
};

