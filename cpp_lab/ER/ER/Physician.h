#pragma once
#include <cstring>
#include <iostream>
using namespace std;
class Patient;

class Physician
{
	char m_name[255];
	Patient* myPatient;
public:
	Physician(const char * name = "NoNameDoc");
	~Physician();
	void treat();
	Patient* getMyPatient();
	Patient* Change(Patient*);
	void Bye();

	friend ostream& operator<<(ostream& os, Physician* doctor);
};

