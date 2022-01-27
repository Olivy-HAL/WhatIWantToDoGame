#pragma once
#include <string>

#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Components/CParticleGeneratorComponent.h"

class CMissile :public CActor
{
private:
	CParticleGeneratorComponent* mParticle;
	XMFLOAT3 mDirection;
	int mDestroyFrame;
	int mFrame = 0;
	void Look(CActor& collideAc);
	void Tick()override;
public:
	CMissile(ILevel& partner, XMFLOAT3 initLocation, XMFLOAT3 direction,XMFLOAT4 quaternion, int destroyFrame, std::string tag = "Bullet", XMFLOAT4 bulletColor = { 1.0f,1.0f,1.0f,1.0f });

};

