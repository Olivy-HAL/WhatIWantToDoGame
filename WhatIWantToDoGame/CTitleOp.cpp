#include "GameFramework/Managers/CSoundManager.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CLightManager.h"
#include "GameFramework/Components/CCameraComponent.h"

#include "CSkyDome.h"

#include "CTitleOp.h"
#include "CSelectLevel.h"
#include "CTitle.h"

void CTitleOp::Init()
{
	CComponent* buf;

	mActor = new CTitleActor(*this);
	CSkyDome& skyDome = *new CSkyDome(*this);
	skyDome.Transform.SetOption(CTransform::EAttachOption::LOCATION_ONLY);

	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/button_click.wav", 0.2f, false, "CLICK");
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/title_bgm.wav", 0.1f, true, "BGM");

	CSoundManager::GetInstance().PlaySound("BGM");

	mActor->GetComponent<CCameraComponent>(buf);
	RequestSetCamera(*dynamic_cast<CCameraComponent*>(buf));

	CInputManager::GetInstance().AddEvent("TitleEnd", EButtonOption::TRIGGER, *this, { {EButtonType::MOUSE,EMouseButtonType::L_BUTTON},{EButtonType::KEYBOARD,DIK_RETURN} }, std::bind(&CTitleOp::End, std::ref(*this)));
	CLightManager::GetInstance().SetDirectionLight({ 1.0f,1.0f,-1.0f });
	CLightManager::GetInstance().SetAmbientLight({ 0.1f,0.1f,0.1f });
}

void CTitleOp::Tick()
{

}

void CTitleOp::Notice(CActor& actor)
{
	if (actor.HasTag("Player"))
	{
		new CTitle(mOwnerInterface, true);
	}
}

void CTitleOp::End()
{
	//new CMainGameLevel(mOwnerInterface , true);
	new CTitle(mOwnerInterface, true);
	CSoundManager::GetInstance().PlaySound("CLICK");
	CInputManager::GetInstance().DeleteEvent("TitleEnd");
}
