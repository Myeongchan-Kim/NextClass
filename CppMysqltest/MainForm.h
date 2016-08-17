#pragma once
#include <memory>
#include <nana/gui/wvl.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/listbox.hpp>
#include <nana/gui/timer.hpp>
#include <nana/gui.hpp>
#include "MySQLMangager.h"

#ifdef NDEBUG
#pragma comment(lib, "nana_v140_Release_x86.lib")
#else
#pragma comment(lib, "nana_v140_Debug_x86.lib")
#endif

using namespace nana;

class TcpNetwork;
class IClientScene;
class ClientSceneMain;
class ClientSceneLogin;
class ClientSceneLobby;
class ClientSceneRoom;
class ClientChat;

class MainForm
{
public:
	MainForm();
	~MainForm();

	void Init();
	void CreateGUI();

	void Show();

private:
	void Update();

private:
	std::shared_ptr<ClientSceneMain> m_pClientScene;
	std::shared_ptr<MySQLMangager> m_pDB;
	
	bool m_IsLogined = false;
	std::unique_ptr<form> m_fm;
	timer m_timer;

};
