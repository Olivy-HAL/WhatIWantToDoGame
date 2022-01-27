#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Managers/CLightManager.h"

#include "CTraiLevel.h"
#include "CSkyDome.h"
#include "CTraiActor.h"

void CTraiLevel::Init()
{
	CComponent* buf;
	CSkyDome& skyDome = *new CSkyDome(*this);
	CTraiActor& player = *new CTraiActor(*this);

	player.GetComponent<CCameraComponent>(buf);
	RequestSetCamera(*dynamic_cast<CCameraComponent*>(buf));

	CLightManager::GetInstance().SetDirectionLight({ 1.0f,1.0f,-1.0f });
	CLightManager::GetInstance().SetAmbientLight({ 0.1f,0.1f,0.1f });
}

void CTraiLevel::Tick()
{

}