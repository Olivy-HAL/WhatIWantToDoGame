#pragma once
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Actor/CActor.h"

#include "CTitleActor.h"

class CTitleOp :public CLevel
{
private:
	CTitleActor* mActor;

public:
	using CLevel::CLevel;
	void Init()override;
	void Tick()override;
	void Notice(CActor& actor)override;
	void End();
};
