#pragma once
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Actor/CDisplay2DActor.h"

#include "CTitle.h"

class CTitle :public CLevel
{
private:
	CDisplay2DActor* mButton;
	float mAlpha = 1.0f;
	float mElapsedTime = 30.f;
	bool mColorFlg = true;
	bool mIsChange = false;
public:
	using CLevel::CLevel;

	void Init()override;
	void Tick()override;

	void End();
};

