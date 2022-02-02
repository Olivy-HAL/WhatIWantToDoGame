#pragma once
#include "GameFramework/Actor/CActor.h"

class CFog :public CActor
{
private:

public:
	CFog(ILevel& partner,XMFLOAT3 loc);
};
