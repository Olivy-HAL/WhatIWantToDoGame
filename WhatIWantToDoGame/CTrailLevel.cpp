#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Managers/CLightManager.h"

#include "CTrailLevel.h"
#include "CSkyDome.h"
#include "CTrailActor.h"
#include "CGround.h"

void CTrailLevel::Init()
{
	CComponent* buf;
	CSkyDome& skyDome = *new CSkyDome(*this);
	CTrailActor& player = *new CTrailActor(*this);
	player.Transform.Location = {0,50,0};
	CGround& ground = *new CGround(*this);

	player.GetComponent<CCameraComponent>(buf);
	RequestSetCamera(*dynamic_cast<CCameraComponent*>(buf));

	CLightManager::GetInstance().SetDirectionLight({ 1.0f,1.0f,-1.0f });
	CLightManager::GetInstance().SetAmbientLight({ 0.1f,0.1f,0.1f });

}

void CTrailLevel::Tick()
{

}