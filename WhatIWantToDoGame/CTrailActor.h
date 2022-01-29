#pragma once

#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CSceneComponent.h"
#include "GameFramework/Data/CModelData.h"
#include "CPointer.h"

#define MAXROT 50
#define ROTSPEED 0.05

class CTrailActor :public CActor
{
private:
	typedef struct CameraStatus
	{
		XMFLOAT3 StartPos;
		XMFLOAT3 EndPos;
	};

	CPointer& mPointer;
	CStaticMeshComponent *mMesh;
	CSceneComponent *mScene;

	XMFLOAT3 mCameraLoc;
	XMFLOAT3 mParticleLocR;
	XMFLOAT3 mParticleLocL;

	CameraStatus mCameraStatus;
	int mShotCnt = 0;
	int mRot = 0;

	float mActorRotX = 0.f;
	float mMeshRotZ = 0.f;
	float mSpeed = 50.0f;
	float mSpeedLimitMin, mSpeedLimitMax;

	bool mRotFlag = false;
	bool mIsParticleFlag = false;


public:
	/*
	★超重要★
	コンポーネントの追加は基本的にコンストラクタ内で行う
	*/
	CTrailActor(ILevel& owner);

	void Shot();
	void ShotReset();
	void Move();
	void Particle(CActor& actor);
	void Rot(int dire);
	void SpeedChange(int type);
	float GetSpeed() { return mSpeed; }

	void Tick()override;
	void EventAtBeginCollide(CActor& collideActor)override;

};