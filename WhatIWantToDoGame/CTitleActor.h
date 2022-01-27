#pragma once
#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Components/CStaticMeshComponent.h"

class CTitleActor:public CActor
{
private:
	CStaticMeshComponent *mMesh;
	float mIncreXPos = 0.1f;
	float mIncreZPos = 0.2f;
	float mSpeed = 0.2f;

	bool mChangeFlg = false;

	void Move();
public:

	CTitleActor(ILevel& owner);
	void Tick()override;
	void Particle(CActor& collideActor);

};