#pragma once
#include <string>

#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Components/C2DAnimationComponent.h"

class CEffectActor :public CActor
{
private:
	C2DAnimationComponent* mAnim;
	std::string mAlias;
	void Tick()override;

public:
	CEffectActor(ILevel& owner, XMFLOAT3 loc, std::string texturePath, int divWidth, int divHeight, std::string alias = "NONE");
};