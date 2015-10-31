#include "Patient.h"
#include "PatientList.h"
#include "Physician.h"
#include "PhysicianList.h"
#include "FCFS.h"

FCFS::FCFS() : Strategy()
{
}


FCFS::~FCFS()
{
}

void FCFS::ChangePatients(PhysicianList* dList, PatientList* pList)
{
	for (int i = 0; i < dList->size(); i++)
	{
		Physician* doctor = dList->Get(i);
		Patient* oldPatient = dList->Get(i)->getMyPatient();

		bool flag = false;
		for (int j = 0; j < pList->size(); j++)
		{
			if (oldPatient == NULL) {
				if (flag == false)
					showStartSelectingLog(doctor);
				doctor->Change(pList->Pop(j));
				flag = true;
				j--;
				oldPatient = doctor->getMyPatient();
				continue;
			}
			if (oldPatient->getMakeTime() > pList->Get(j)->getMakeTime()) {
				if (flag == false)
					showStartSelectingLog(doctor);
				pList->Set(j, doctor->Change(pList->Get(j)));
				flag = true;
			}
		}
		if (flag)
			cout << doctor << "'s patient changed." << endl;
		else
			cout << doctor << " keep treating his patient." << endl;
	}
	return;
}