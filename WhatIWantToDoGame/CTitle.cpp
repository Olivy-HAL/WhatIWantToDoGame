#include "GameFramework/Actor/CDisplay2DActor.h"
#include "GameFramework/Actor/CFeedActor.h"

#include "GameFramework/Game/CApplication.h"

#include "GameFramework/Managers/CGameManager.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CSoundManager.h"

//#include "CMainGameLevel.h"
#include "CSelectLevel.h"
#include "CTitle.h"
#include "CTitleOp.h"

void CTitle::Init()
{
	new CFeedActor(*this, nullptr, CFeedActor::EOption::FEEDIN);

	CDisplay2DActor& title = *new CDisplay2DActor(*this , "Assets/Textures/Decal/sky_noise.png");
	title.Transform.Scale = { static_cast<float>(CApplication::CLIENT_WIDTH),static_cast<float>(CApplication::CLIENT_HEIGHT),0.0f };
	title.Transform.Location.x = static_cast<float>(CApplication::CLIENT_WIDTH / 2.0f);
	title.Transform.Location.y = static_cast<float>(CApplication::CLIENT_HEIGHT / 2.0f);

	mButton = new CDisplay2DActor(*this, "Assets/Textures/Decal/press_button.png");
	mButton->Transform.Scale = { 300.0,100.0,0.0 };
	mButton->Transform.Location.x= static_cast<float>(CApplication::CLIENT_WIDTH / 2.0f);
	mButton->Transform.Location.y = static_cast<float>(CApplication::CLIENT_HEIGHT / 1.25f);

	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/button_click.wav" , 0.2f , false , "CLICK");
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/title_bgm.wav" , 0.1f , true , "BGM");

	CSoundManager::GetInstance().PlaySound("BGM");

	CInputManager::GetInstance().AddEvent("TitleEnd" , EButtonOption::TRIGGER , *this , { {EButtonType::MOUSE,EMouseButtonType::L_BUTTON},{EButtonType::KEYBOARD,DIK_RETURN} } , std::bind(&CTitle::End , std::ref(*this)));
}

void CTitle::Tick()
{
	if (mColorFlg)
	{
		mButton->SetColor({ 1.0f,1.0f,1.0f, mAlpha });
		mAlpha -= 0.01f;
		if (mAlpha<=0)
		{
			mColorFlg = !mColorFlg;
		}
	}
	else
	{
		mButton->SetColor({ 1.0f,1.0f,1.0f, mAlpha });
		mAlpha += 0.01f;
		if (mAlpha >= 1)
		{
			mColorFlg = !mColorFlg;
		}
	}

	mElapsedTime-= CGameManager::GetInstance().GetDeltaTime();
	if (mElapsedTime <= 0.f && !mIsChange)
	{
		mIsChange = true;
		new CTitleOp(mOwnerInterface, true);
	}
}

void CTitle::End()
{
	//new CMainGameLevel(mOwnerInterface , true);
	new CSelectLevel(mOwnerInterface , true);
	CSoundManager::GetInstance().PlaySound("CLICK");
	CInputManager::GetInstance().DeleteEvent("TitleEnd");
}