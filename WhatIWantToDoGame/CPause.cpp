#include <cstdlib>

#include "GameFramework/Actor/CDisplay2DActor.h"
#include "GameFramework/Game/CApplication.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CSoundManager.h"

#include "CPause.h"

CPause::CPause(ILevel& owner) :CActor(owner,false)
{
	mBackground = new CDisplay2DActor(owner, "Assets/Textures/Pose/pose.png");
	mBackground->Transform.Scale = { 900,600,0.0f };
	mBackground->Transform.Location.x = static_cast<float>(CApplication::CLIENT_WIDTH / 2.0f);
	mBackground->Transform.Location.y = static_cast<float>(CApplication::CLIENT_HEIGHT / 2.0f);
	mBackground->SetColor({ 1.f,1.f,1.f,0.9f });

	mButtons.emplace_back(new CPauseUI(owner, "Assets/Textures/Pose/pose_resume.png", { 360,240,0.0f },
		static_cast<float>(CApplication::CLIENT_WIDTH / 2.65f), static_cast<float>(CApplication::CLIENT_HEIGHT / 2.6f), { 1.f,1.f,1.f,0.9f }));	
	mButtons.emplace_back(new CPauseUI(owner, "Assets/Textures/Pose/pose_restart.png", { 360,240,0.0f },
		static_cast<float>(CApplication::CLIENT_WIDTH / 1.6f), static_cast<float>(CApplication::CLIENT_HEIGHT / 2.6f), { 1.f,1.f,1.f,0.9f }));
	mButtons.emplace_back(new CPauseUI(owner, "Assets/Textures/Pose/pose_configuration.png", { 360,240,0.0f },
		static_cast<float>(CApplication::CLIENT_WIDTH / 2.65f), static_cast<float>(CApplication::CLIENT_HEIGHT / 1.5f), { 1.f,1.f,1.f,0.9f }));
	mButtons.emplace_back(new CPauseUI(owner, "Assets/Textures/Pose/pose_end.png", { 360,240,0.0f },
		static_cast<float>(CApplication::CLIENT_WIDTH / 1.6f), static_cast<float>(CApplication::CLIENT_HEIGHT / 1.5f), { 1.f,1.f,1.f,0.9f }));
	
	CInputManager::GetInstance().AddEvent("SelectUP", EButtonOption::TRIGGER, *this, { EButtonType::KEYBOARD,DIK_UP }, std::bind(&CPause::Select, std::ref(*this), -2));
	CInputManager::GetInstance().AddEvent("SelectDOWN", EButtonOption::TRIGGER, *this, { EButtonType::KEYBOARD,DIK_DOWN }, std::bind(&CPause::Select, std::ref(*this), 2));
	CInputManager::GetInstance().AddEvent("SelectRIGHT", EButtonOption::TRIGGER, *this, { EButtonType::KEYBOARD,DIK_RIGHT }, std::bind(&CPause::Select, std::ref(*this), 1));
	CInputManager::GetInstance().AddEvent("SelectLEFT", EButtonOption::TRIGGER, *this, { EButtonType::KEYBOARD,DIK_LEFT }, std::bind(&CPause::Select, std::ref(*this), -1));

	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/Decision.wav", 0.5f, false, "DECISION");
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/NonDecision.wav", 0.7f, false, "NONDECISION");
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/Select.wav", 0.5f, false, "SELECT");

}

void CPause::Select(int num)
{
	for (int n = 0; n < std::abs(num); n++)
	{
		if(num>0) mSelect = static_cast<SelectButton>(mSelect + 1);
		else mSelect = static_cast<SelectButton>(mSelect - 1);

		if (mSelect > SelectButton::END) mSelect = SelectButton::RESUME;
		else if (mSelect < SelectButton::RESUME) mSelect = SelectButton::END;
	}

	CSoundManager::GetInstance().PlaySound("SELECT");
}

void CPause::Cancel()
{
	Destroy();
	mBackground->Destroy();
	for (auto& button : mButtons)
	{
		button.get()->Destroy();
	}

	CInputManager::GetInstance().DeleteEvent("SelectUP");
	CInputManager::GetInstance().DeleteEvent("SelectDOWN");
	CInputManager::GetInstance().DeleteEvent("SelectRIGHT");
	CInputManager::GetInstance().DeleteEvent("SelectLEFT");
}

void CPause::Tick()
{
	if(mSelect==SelectButton::RESUME)
	{ 
		mButtons.at(0).get()->SetSelect(true);
	}
	else if(mSelect==SelectButton::RESTART)
	{ 
		mButtons.at(1).get()->SetSelect(true);
	}
	else if(mSelect==SelectButton::CONFIG)
	{
		mButtons.at(2).get()->SetSelect(true);
	}
	else if(mSelect==SelectButton::END)
	{
		mButtons.at(3).get()->SetSelect(true);
	}
	
	for (auto& button : mButtons)
	{
		button.get()->Update();
	}
}