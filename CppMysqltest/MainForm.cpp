#include "MainForm.h"
#include "ClientSceneMain.h"
#include "MySQLMangager.h"

MainForm::MainForm() {}

MainForm::~MainForm()
{
}

void MainForm::Init()
{
	m_pDB = std::make_shared<MySQLMangager>();   // Declare an instance of the db manager
	m_pClientScene = std::make_shared<ClientSceneMain>();
}

void MainForm::CreateGUI()
{
	m_fm = std::make_unique<form>(API::make_center(900, 200));
	m_fm->caption("Chat Client");

	//connect & login
	m_pClientScene->CreateUI(m_fm.get());

	//
	m_timer.elapse([&]() { Update();});
	m_timer.interval(32);
	m_timer.start();
}

void MainForm::Show()
{
	m_fm->show();
	exec();
}

void MainForm::Update()
{
	m_pClientScene->Update();
	//m_fm->update();
}
