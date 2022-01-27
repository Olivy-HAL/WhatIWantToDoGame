#pragma once
#include <string>

#include "GameFramework/Actor/CActor.h"

class CBullet :public CActor
{
private:
	XMFLOAT3 mDirection;
	int mDestroyFrame;
	int mFrame = 0;

	void Tick()override;
public:
	CBullet(ILevel& partner , XMFLOAT3 initLocation , XMFLOAT3 direction , int destroyFrame, std::string tag="Bullet",XMFLOAT4 bulletColor = { 1.0f,1.0f,1.0f,1.0f });

};

