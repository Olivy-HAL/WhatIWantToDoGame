#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Managers/CLightManager.h"

#include "CTrialLevel.h"
#include "CSkyDome.h"
#include "CTrialActor.h"
#include "CGround.h"

void CTrialLevel::Init()
{
	CComponent* buf;
	CSkyDome& skyDome = *new CSkyDome(*this);
	CTrialActor& player = *new CTrialActor(*this);
	player.Transform.Location = {0,50,0};
	CGround& ground = *new CGround(*this);

	player.GetComponent<CCameraComponent>(buf);
	RequestSetCamera(*dynamic_cast<CCameraComponent*>(buf));

	CLightManager::GetInstance().SetDirectionLight({ 1.0f,1.0f,-1.0f });
	CLightManager::GetInstance().SetAmbientLight({ 0.1f,0.1f,0.1f });

}

void CTrialLevel::Tick()
{

}