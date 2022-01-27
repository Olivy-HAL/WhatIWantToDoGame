#pragma once
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Actor/CDisplay2DActor.h"

#include "CSelectFighter.h"

class CSelectLevel : public CLevel
{
private:

	CSelectFighter* mFighter;

	CDisplay2DActor *mLeftArrow;
	CDisplay2DActor *mRightArrow;

	float mAlpha = 1.0f;
	bool mColorFlg = true;

public:
	using CLevel::CLevel;

	void Init()override;
	void Tick()override;

	void End();

	/*void ChangePosi();
	void ChangeNega();*/
};

