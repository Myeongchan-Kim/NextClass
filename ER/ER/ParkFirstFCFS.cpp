#include "Patient.h"
#include "PatientList.h"
#include "Physician.h"
#include "PhysicianList.h"
#include "ParkFirstFCFS.h"

ParkFirstFCFS::ParkFirstFCFS() : Strategy()
{
}


ParkFirstFCFS::~ParkFirstFCFS()
{
}

void ParkFirstFCFS::ChangePatients(PhysicianList* dList, PatientList* pList)
{
	for (int i = 0; i < dList->size(); i++)
	{
		Physician* doctor = dList->Get(i);
		Patient* oldPatient = dList->Get(i)->getMyPatient();

		bool flag = false;
		showStartSelectingLog(doctor);
		for (int j = 0; j < pList->size(); j++)
		{
			if (oldPatient == NULL) {
				doctor->Change(pList->Pop(j));
				flag = true;
				j--;
				oldPatient = doctor->getMyPatient();
				continue;
			}
			if (strcmp(doctor->getMyPatient()->getName(), "Park eun jong") == 0)
			{
				break;
			}
			if (strcmp(pList->Get(j)->getName(), "Park eun jong") == 0)
			{
				pList->Set(j, doctor->Change(pList->Get(j)));
				flag = true;
			}else if (oldPatient->getMakeTime() > pList->Get(j)->getMakeTime()) {
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
