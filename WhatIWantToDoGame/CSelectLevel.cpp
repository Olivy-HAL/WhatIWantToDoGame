#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Actor/CFeedActor.h"
#include "GameFramework/Game/CApplication.h"
#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CSoundManager.h"
#include "GameFramework/Managers/CLightManager.h"

#include "CMainGameLevel.h"

#include "CSelectFighter.h"
#include "CSkyDome.h"
#include "CSelectLevel.h"

void CSelectLevel::Init()
{
	new CFeedActor(*this, nullptr, CFeedActor::EOption::FEEDIN);

	CModelDataManager::GetInstance().GetModel("Assets/Models/Fighter/F-15E.fbx", "Assets/Models/Fighter/Textures/");
	CModelDataManager::GetInstance().GetModel("Assets/Models/F15C/F-15C.fbx", "Assets/Models/F15C/Textures/");

	mLeftArrow = new CDisplay2DActor(*this,"Assets/Textures/Select/セレクトL.png");
	mLeftArrow->Transform.Scale = { 200,200,0.0f };
	mLeftArrow->Transform.Location.x = static_cast<float>(CApplication::CLIENT_WIDTH / 10.0f);
	mLeftArrow->Transform.Location.y = static_cast<float>(CApplication::CLIENT_HEIGHT / 2.0f);
	mRightArrow = new CDisplay2DActor(*this,"Assets/Textures/Select/セレクトR.png");
	mRightArrow->Transform.Scale = { 200,200,0.0f };
	mRightArrow->Transform.Location.x = static_cast<float>(CApplication::CLIENT_WIDTH-(CApplication::CLIENT_WIDTH / 10.0f));
	mRightArrow->Transform.Location.y = static_cast<float>(CApplication::CLIENT_HEIGHT / 2.0f);

	CComponent* buf;

	mFighter = new CSelectFighter(*this);

	CSkyDome& skyDome = *new CSkyDome(*this);
	skyDome.Transform.SetOption(CTransform::EAttachOption::LOCATION_ONLY);

	mFighter->GetComponent<CCameraComponent>(buf);
	RequestSetCamera(*dynamic_cast<CCameraComponent*>(buf));

	CInputManager::GetInstance().AddEvent("SelectEnd", EButtonOption::TRIGGER, *this, { {EButtonType::MOUSE,EMouseButtonType::L_BUTTON},{EButtonType::KEYBOARD,DIK_RETURN} }, std::bind(&CSelectLevel::End, std::ref(*this)));
	
	CLightManager::GetInstance().SetDirectionLight({ 1.0f,1.0f,-1.0f });
	CLightManager::GetInstance().SetAmbientLight({ 0.1f,0.1f,0.1f });
}

void CSelectLevel::Tick()
{
	if (mColorFlg)
	{
		mLeftArrow->SetColor({ 1.0f,1.0f,1.0f, mAlpha });
		mRightArrow->SetColor({ 1.0f,1.0f,1.0f, mAlpha });
		mAlpha -= 0.02f;
		if (mAlpha <= 0.1)
		{
			mColorFlg = !mColorFlg;
		}
	}
	else
	{
		mLeftArrow->SetColor({ 1.0f,1.0f,1.0f, mAlpha });
		mRightArrow->SetColor({ 1.0f,1.0f,1.0f, mAlpha });
		mAlpha += 0.02f;
		if (mAlpha >= 1)
		{
			mColorFlg = !mColorFlg;
		}
	}
}

void CSelectLevel::End()
{


	new CMainGameLevel(mOwnerInterface, mFighter->GetModel(), mFighter->GetMesh().Transform,true);
	CSoundManager::GetInstance().PlaySound("CLICK");
	CInputManager::GetInstance().DeleteEvent("SelectEnd");
}
