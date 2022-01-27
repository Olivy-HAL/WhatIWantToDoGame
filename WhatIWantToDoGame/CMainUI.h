#pragma once
#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Actor/CDisplay2DActor.h"

class CMainUI :public CActor
{
private:
	CDisplay2DActor* mRader;
public:
	CMainUI(ILevel& owner);
};
