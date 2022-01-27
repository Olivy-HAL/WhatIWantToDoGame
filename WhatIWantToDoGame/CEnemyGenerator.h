#pragma once

#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Level/CLevel.h"

#include "CEnemy.h"
class CEnemyGenerator :public CActor
{
private:
	XMFLOAT2 mMin, mMax;
	XMFLOAT3& mSkyLoc;

	float mTime;
	float mLenghtTime;
	bool mIsSpawn = false;

	void Create(float x , float z);
public:
	std::vector<CEnemy*> mAliveEnemy;
	CEnemyGenerator(ILevel& partner, XMFLOAT2 min, XMFLOAT2 max, XMFLOAT3& skyLoc, float generationPerSecond) :CActor(partner)
		, mMin(min), mMax(max), mLenghtTime(generationPerSecond),mSkyLoc(skyLoc)
	{
		mTime = mLenghtTime;
	}

	void Tick() override;

};