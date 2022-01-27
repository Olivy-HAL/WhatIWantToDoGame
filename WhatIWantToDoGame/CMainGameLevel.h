#pragma once
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Data/CModelData.h"
#include "GameFramework/Components/CStaticMeshComponent.h"

#include "CFighter.h"
#include "CEnemyGenerator.h"
#include "CPause.h"

class CMainGameLevel :public CLevel
{
private:	
	CFighter* mFighter;
	CPause* mPause;
	CEnemyGenerator* mEGenerator;
	CModelData mPlayerModel;
	CTransform mStartTransform;

	float mTime = 60.0f;
	int mAliveEnemy = 3;

	bool mIsEnd = false;
	bool mIsGameOver = false;
	bool mPauseFlg = false;

	void Resume();	

public:
	using CLevel::CLevel;

	CMainGameLevel(IGame& owner, const CModelData& modelData, const CTransform& trans, bool isFeed = false);

	void Init()override;

	void Tick()override;

	void Notice(CActor& actor)override;

	void Pause();

	void Decision();
};

