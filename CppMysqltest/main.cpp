#include <iostream>

#include "MainForm.h"
#include "MySQLMangager.h"

int main()
{
	MainForm mainForm;

	mainForm.Init();
	mainForm.CreateGUI();
	mainForm.Show();
}