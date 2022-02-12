#pragma once

#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CSceneComponent.h"
#include "GameFramework/Data/CModelData.h"
#include "CPointer.h"

#define MAXROT 50
#define ROTSPEED 0.05

class CTrialActor :public CActor
{
private:

	CPointer& mPointer;
	CStaticMeshComponent *mMesh;
	CSceneComponent *mScene;

	XMFLOAT3 mCameraLoc;
	XMFLOAT3 mParticleLocR;
	XMFLOAT3 mParticleLocL;

	int mShotCnt = 0;
	int mRot = 0;

	float mActorRotX = 0.f;
	float mMeshRotZ = 0.f;
	float mSpeed = 100.0f;
	float mSpeedLimitMin, mSpeedLimitMax;

	bool mRotFlag = false;
	bool mTurn = true;
	bool mIsParticleFlag = false;

	void Shot();
	void ShotReset();
	void Move();
	void Particle(CActor& actor);
	void Rot(int dire);
	void Turning();
	void Turn();
	void SpeedChange(int type);
	void ControlUnit();
	float GetSpeed() { return mSpeed; }

	void Tick()override;
	void EventAtBeginCollide(CActor& collideActor)override;
public:
	/*
	★超重要★
	コンポーネントの追加は基本的にコンストラクタ内で行う
	*/
	CTrialActor(ILevel& owner);

};