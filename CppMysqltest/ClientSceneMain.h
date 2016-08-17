#pragma once

#include "IClientScene.h"
#include "MySQLMangager.h"

class ClientSceneMain : public IClientScene
{
public:
	ClientSceneMain() {}
	virtual ~ClientSceneMain() {}

	virtual void Update() override
	{
		if (m_IsLogined)
		{
			m_text_id->enabled(false);
			m_text_pw->enabled(false);
			m_button_delete->enabled(true);
			m_button_signup->enabled(false);
			m_button_login->caption("LogOut");
		}
		else 
		{
			m_text_id->enabled(true);
			m_text_pw->enabled(true);
			m_button_delete->enabled(false);
			m_button_signup->enabled(true);
			m_button_login->caption("Login");
		}
	}

	void CreateUI(form* pform)
	{
		m_pForm = pform;

		//GUI - ID
		m_label_id = std::make_shared<label>((form&)*m_pForm, nana::rectangle(22, 58, 18, 18));
		m_label_id->caption("ID:");
		m_text_id = std::make_shared<textbox>((form&)*m_pForm, nana::rectangle(43, 56, 115, 20));
		m_text_id->caption("123");

		//GUI - PW
		m_label_pw = std::make_shared<label>((form&)*m_pForm, nana::rectangle(170, 58, 69, 18));
		m_label_pw->caption("PassWord:");
		m_text_pw = std::make_shared<textbox>((form&)*m_pForm, nana::rectangle(230, 56, 115, 20));
		m_text_pw->caption("111");

		//GUI - Login
		m_button_login = std::make_shared<button>((form&)*m_pForm, nana::rectangle(353, 54, 100, 23));
		m_button_login->caption("Login");
		m_button_login->events().click([&]() { this->LogInOut(); });
		//m_button_login->enabled(true);

		//GUI - signup
		m_button_signup = std::make_shared<button>((form&)*m_pForm, nana::rectangle(493, 54, 100, 23));
		m_button_signup->caption("signup");
		m_button_signup->events().click([&]() { this->ReqSignUp(); });
		//m_button_signup->enabled(true);

		//GUI - delete
		m_button_delete = std::make_shared<button>((form&)*m_pForm, nana::rectangle(593, 54, 100, 23));
		m_button_delete->caption("delete");
		m_button_delete->events().click([&]() { this->DeleteUserInfo(); });
		//m_button_delete->enabled(false);
	}

private:
	//login button callback
	void LogInOut()
	{
		//로그인되어 있지 않으면
		if (m_IsLogined == false)
		{ 
			//로그인 요청한다
			swprintf_s(query, sizeof(query), L"CALL login_check('%ls', '%ls')", m_text_id->caption_wstring().c_str(), m_text_pw->caption_wstring().c_str());
			
			MySQLMangager db;
			db.sqlconn();
			db.sqlexec(query, result);
			db.sqldisconn();
			if (lstrcmpW(result, L"1")== 0)
			{
				m_IsLogined = true;
				m_button_login->caption("LogOut");
			}
		}
		//로그인되어 있으면
		else
		{ 
			//로그아웃 요청한다
			m_IsLogined = false;
			m_button_login->caption("Login");
		}
		Update();
	}

	void ReqSignUp()
	{
		//로그인 요청한다
		swprintf_s(query, sizeof(query), L"CALL register_ID('%ls', '%ls')", m_text_id->caption_wstring().c_str(), m_text_pw->caption_wstring().c_str());

		MySQLMangager db;
		db.sqlconn();
		db.sqlexec(query, result);
		db.sqldisconn();
		if ((lstrcmpW(result, L"INSERTED") == 0))
		{
			LogInOut();
		}
	}

	void DeleteUserInfo()
	{
		//로그인 요청한다
		swprintf_s(query, sizeof(query), L"CALL delete_ID('%ls', '%ls')", m_text_id->caption_wstring().c_str(), m_text_pw->caption_wstring().c_str());

		MySQLMangager db;
		db.sqlconn();
		db.sqlexec(query, result);
		db.sqldisconn();
		if (lstrcmpW(result, L"DELETE") == 0)
		{
			m_IsLogined = false;
		}
		LogInOut();
	}

	bool m_IsLogined = false;
	form* m_pForm = nullptr;
	SQLWCHAR query[200];
	SQLWCHAR result[200];
	
	std::shared_ptr<label> m_label_id;
	std::shared_ptr<textbox> m_text_id;

	std::shared_ptr<label> m_label_pw;
	std::shared_ptr<textbox> m_text_pw;

	std::shared_ptr<button> m_button_login;
	std::shared_ptr<button> m_button_signup;
	std::shared_ptr<button> m_button_delete;
};