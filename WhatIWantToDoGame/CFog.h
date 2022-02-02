#pragma once
#include "GameFramework/Actor/CActor.h"

class CFog :public CActor
{
private:
	int mLifeTime = 60;

public:
	CFog(ILevel& partner,XMFLOAT3 loc);

	void Tick() override;
};
