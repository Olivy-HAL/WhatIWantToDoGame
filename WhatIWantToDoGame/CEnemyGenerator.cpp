#include <random>

#include "GameFramework/Managers/CGameManager.h"
#include "GameFramework/Library/LCMath.h"

#include "CEnemyGenerator.h"

void CEnemyGenerator::Tick()
{
	if (mIsSpawn)
	{
		if (mAliveEnemy.size() == 0) mIsSpawn = false;
	}
	else
	{
		mTime -= CGameManager::GetInstance().GetDeltaTime();

		if (mTime <= 0.f)
		{
			mTime = mLenghtTime;
			mIsSpawn = true;

			std::random_device randomSeed;							//乱数デバイス
			std::mt19937 randomEngine(randomSeed());				//乱数アルゴリズム
			std::uniform_int_distribution<> randomScope(0, 3);		//範囲指定乱数生成器
			int spawnSeed = randomScope(randomEngine);

			if (spawnSeed == 0)Create(mSkyLoc.x + mMin.x,0);

			else if (spawnSeed == 1)Create(mSkyLoc.x + mMax.x, 0);

			else if (spawnSeed == 2)Create(0, mSkyLoc.z + mMin.y);

			else if (spawnSeed == 3)Create(0, mSkyLoc.z + mMax.y);
		}
	}
}

void CEnemyGenerator::Create(float x, float z)
{
	XMFLOAT3 angle = { 0,0,0 };
	XMFLOAT3 defLoc = { x,0.f,z };

	mAliveEnemy.emplace_back() = new CEnemy(CGameManager::GetInstance().GetLevelInterface(),defLoc, angle,0);

	XMFLOAT3 fvF = mAliveEnemy.back()->Transform.GetForwardVectorWorld();
	XMFLOAT3 fvR = mAliveEnemy.back()->Transform.GetRightVectorWorld();
	fvF.x *= -10; fvF.y *= -10; fvF.z *= -10;

	LCMath::CalcFloat3Addition(defLoc, fvF, defLoc);
	mAliveEnemy.emplace_back() = new CEnemy(CGameManager::GetInstance().GetLevelInterface(),
		{ defLoc.x + (fvR.x * 15.f),defLoc.y + (fvR.y * 15.f),defLoc.z + (fvR.z * 15.f) },
		{angle.x + (fvR.x * 15.f),angle.y + (fvR.y * 15.f),angle.z + (fvR.z * 15.f) },1);
	
	mAliveEnemy.emplace_back() = new CEnemy(CGameManager::GetInstance().GetLevelInterface(),
		{ defLoc.x - (fvR.x * 15.f),defLoc.y - (fvR.y * 15.f),defLoc.z - (fvR.z * 15.f) },
		{ angle.x - (fvR.x * 15.f),angle.y - (fvR.y * 15.f),angle.z - (fvR.z * 15.f) },2);
}