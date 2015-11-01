#include "PatientGenerater.h"


PatientGenerater::PatientGenerater(const char * fileName) : sendedPatientsNum(0)
{
	pList = new PatientList("generator");
	if (fileName == NULL)
		return;
	ifstream f;
	f.open(fileName,ios::in);

	cout << "Generate Patient from file : " << fileName <<endl;

	while (!f.eof()) {
		char row[STRLEN::MAX_ROW_LEN];
		f.getline(row, STRLEN::MAX_ROW_LEN);
		
		//1,0,86,F,fever,UTI,1,-1
		//name, 도착시간, 나이, 성별, 증상, 진단, 진단시간, 사망시간
		//std::cout << row << std::endl;

		if (strlen(row) < 15)
			break;
		
		char * ptr = strtok(row, ",");
		
		char name[STRLEN::MAX_NAME_LEN];
		strcpy_s(name, ptr);
		//cout << name <<" ";

		int arrTime;
		ptr = strtok(NULL, ",");
		arrTime = atoi(ptr);
		//cout << arrTime << " ";

		int age;
		ptr = strtok(NULL, ",");
		age = atoi(ptr);
		//cout << age << " ";

		char gender; // M or F
		ptr = strtok(NULL, ",");
		gender = ptr[0];
		//cout << gender << " ";

		char cheifComplaint[STRLEN::MAX_NAME_LEN];
		ptr = strtok(NULL, ",");
		strcpy_s(cheifComplaint, ptr);
		//cout << cheifComplaint << " ";
		
		char disease[STRLEN::MAX_NAME_LEN];
		ptr = strtok(NULL, ",");
		strcpy_s(disease , ptr);
		//cout << disease << " ";

		int dxTime;
		ptr = strtok(NULL, ",");
		dxTime = atoi(ptr);
		//cout << dxTime << " ";

		int exTime;
		ptr = strtok(NULL, "\n");
		exTime = atoi(ptr);
		//cout << exTime << " ";

		//cout << endl;

		Patient* p = new Patient(arrTime, name, age, gender, cheifComplaint, disease, dxTime, exTime);
		pList->Add(p);
	}
	
	cout << *pList << endl;
}


PatientGenerater::~PatientGenerater()
{
}

void PatientGenerater::SendPatient(Patient* p, Hospital * hospital)
{
	cout << p << " ";
	hospital->admission(p);
	return;
}


void PatientGenerater::SendPatients(const int currentTime, Hospital * hospital)
{
	bool sendStartFlag = false;
	for (int i = 0; i < pList->size(); i++)
	{
		if (pList->Get(i)->isTimeToAche(currentTime)) {
			if (sendStartFlag == false)
				cout << "SendPatients : ";
			sendStartFlag = true;
			SendPatient(pList->Get(i), hospital);
			sendedPatientsNum++;
		}
	}
	cout << endl;
}

bool PatientGenerater::isAllSended()
{
	if (sendedPatientsNum < pList->size())
		return false;
	else
		return true;
}

void PatientGenerater::deletePatient()
{
	for (int i = 0; i < pList->size(); i++)
	{
		delete pList->Get(i);
	}

	delete []pList;
}