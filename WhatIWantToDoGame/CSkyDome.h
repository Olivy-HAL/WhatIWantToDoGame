#pragma once
#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Components/CStaticMeshComponent.h"

class CFighter;

class CSkyDome :public CActor
{
private:
	CStaticMeshComponent* mMesh;
	CTransform* mFighterTransform;
	float mFighterSpeed;
	bool mIsOutSide = true;

	void Tick()override;
	void EventAtBeginCollide(CActor& collideActor)override;
	void EventAtEndCollide(CActor& collideActor)override;

public:
	CSkyDome(ILevel& owner);
	CSkyDome(ILevel& owner, CFighter& fighter);
};

