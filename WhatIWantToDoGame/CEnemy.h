#pragma once
#include "GameFramework/Actor/CActor.h"

class CEnemy : public CActor
{
private:
	int mShotCnt = 0;
	int mNumber;
	void Tick()override;
	void EventAtBeginCollide(CActor& collideActor)override;
	void Move();
	void Shot();
	void Look(CActor& collideActor);
public:
	CEnemy(ILevel& owner,XMFLOAT3 loc,XMFLOAT3 angle,int num);
	int GetNumber() { return mNumber; }
	void SetNumber(int num) { mNumber = num; }

};

