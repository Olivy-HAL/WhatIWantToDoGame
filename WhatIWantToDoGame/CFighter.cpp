#include "GameFramework/ExternalTools/imgui/myimgui.h"

#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CSphereMeshComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Components/CLightComponent.h"
#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CSpringArmComponent.h"
#include "GameFramework/Components/CParticleGeneratorComponent.h"

#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CSoundManager.h"
#include "GameFramework/Managers/CGameManager.h"
#include "GameFramework/Game/CApplication.h"

#include "CBullet.h"
#include "CMissile.h"
#include "CFighter.h"

CFighter::CFighter(ILevel& owner, CModelData& modelData, CTransform& trans) :CActor(owner), mPointer(*new CPointer(owner, *this)),
mSpeedLimitMin(mSpeed / 2.0f), mSpeedLimitMax(mSpeed*2.0f)
{
	Transform.AttachTransform(mPointer.Transform);
	mPointer.Transform.Location.y = 4.0f;
	mPointer.Transform.Location.z = 100.0f;

	//タグ追加
	AddTag("Fighter");

	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/shot.wav", 0.05f, false, "SHOT");
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/bomb.wav", 0.1f, false, "BOMB");

	mScene = new CSceneComponent(*this, Transform);
	/*
	★超重要★
	コンポーネントはコンストラクタの引数ownerにいれたアクターに自動で追加される
	その際原則ヒープ領域に(newで)作成すること
	*/
	mMesh = new CStaticMeshComponent(*this, mScene->Transform, modelData, "Shader/vs.hlsl", "Shader/ps.hlsl");
	mMesh->Transform.Rotation.SetQuaternion(trans.Rotation.GetQuaternion());
	mMesh->Transform.Scale = trans.Scale;

	CCameraComponent& camera = *new CCameraComponent(*this);

	XMFLOAT3 fv = Transform.GetForwardVectorRelative();
	XMFLOAT3 loc = Transform.Location;
	mCameraLoc = Transform.Location;
	mCameraLoc.x -= 50.0f;
	mCameraStatus.StartPos.x = mCameraLoc.x;
	mCameraStatus.EndPos.x = 0;
	mCameraStatus.StartPos.y = mCameraLoc.y;
	mCameraStatus.EndPos.y = mCameraLoc.y + fv.y * -20.0f + 4.0f;
	mCameraStatus.EndPos.z = mCameraLoc.z + fv.z * -20.0f;
	mCameraLoc.z += 5.0f;
	mCameraStatus.StartPos.z = mCameraLoc.z;

	camera.SetProjection(10.f, 10000.f, XM_PI / 4.f, CApplication::CLIENT_WIDTH, CApplication::CLIENT_HEIGHT);
	camera.SetView(mCameraLoc, loc, { 0.f,1.f,0.f });

	CSpringArmComponent& spr = *new CSpringArmComponent(*this, Transform, camera);
	spr.SetLerpTime(0.3f);

	CSphereColliderComponent& collider = *new CSphereColliderComponent(*this, mMesh->GetModel(), Transform);
	collider.Transform.Scale = { trans.Scale.x/1.2f,trans.Scale.y / 1.2f,trans.Scale.z / 1.2f, };
	collider.Transform.Location.y += 2.0f;
	collider.Transform.Location.z -= 2.0f;

	Transform.RequestDebugLine();

	XMFLOAT3 forwardVec = Transform.GetForwardVectorWorld();
	forwardVec.x *= -1;
	forwardVec.y *= -1;
	forwardVec.z *= -1;

	//コーンパーティクル作成
	/*new CParticleGeneratorComponent(*this, Transform, std::bind(&CFighter::Particle, std::ref(*this), std::placeholders::_1), 0.3f, 1.f, 30,
		*new CParticleBaseGeneratorCone(forwardVec, 30),100000);*/

	/*
	★超重要★
	ボタンの入力で呼びだしたいメソッドはこのようにインプットマネージャーに追加できる
	他にも追加方法があるのでインプットマネージャーのヘッダーを確認することを推奨
	*/
	/*CInputManager::GetInstance().AddEvent("SpeedUP", EButtonOption::PRESS, *this, { EButtonType::MOUSE,EMouseButtonType::L_BUTTON }, std::bind(&CFighter::SpeedChange, std::ref(*this), 0));
	CInputManager::GetInstance().AddEvent("SpeedDPWN", EButtonOption::PRESS, *this, { EButtonType::MOUSE,EMouseButtonType::R_BUTTON }, std::bind(&CFighter::SpeedChange, std::ref(*this), 1));*/
	CInputManager::GetInstance().AddEvent("SpeedUP", EButtonOption::PRESS, *this, { EButtonType::KEYBOARD,DIK_UP }, std::bind(&CFighter::SpeedChange, std::ref(*this), 0));
	CInputManager::GetInstance().AddEvent("SpeedDPWN", EButtonOption::PRESS, *this, { EButtonType::KEYBOARD,DIK_DOWN }, std::bind(&CFighter::SpeedChange, std::ref(*this), 1));
	//CInputManager::GetInstance().AddEvent("Reset" , EButtonOption::RELEASE , *this , { EButtonType::MOUSE,EMouseButtonType::L_BUTTON } , std::bind(&CFighter::ShotReset , std::ref(*this)));
}

void CFighter::Shot()
{
	if (mShotCnt % 5 != 0)
	{
		mShotCnt++;
		return;
	}
	mShotCnt++;

	XMFLOAT3 loc = mMesh->Transform.GetWorldLocation();
	XMFLOAT3 fv, dire;
	fv = dire = mMesh->Transform.GetForwardVectorWorld();
	XMFLOAT3 fvR = mMesh->Transform.GetRightVectorWorld();
	XMFLOAT3 missilePos_R, missilePos_L;

	loc.x += fv.x * 10.0f;
	loc.y += fv.y * 10.0f - 2.0f;
	loc.z += fv.z * 10.0f;
	missilePos_R = missilePos_L = loc;

	LCMath::CalcFloat3FromStartToGoal(loc, mPointer.Transform.GetWorldLocation(), dire);
	LCMath::CalcFloat3Normalize(dire, dire);
	XMFLOAT4 qua = Transform.Rotation.GetQuaternion();

	missilePos_R.x += fvR.x*5.f;
	missilePos_R.y += fvR.y*5.f;
	missilePos_R.z += fvR.z*5.f;

	missilePos_L.x -= fvR.x*5.f;
	missilePos_L.y -= fvR.y*5.f;
	missilePos_L.z -= fvR.z*5.f;

	/*	missilePos_R.x += 5.f;
		missilePos_L.x -= 5.f;*/
	//new CBullet(mOwnerInterface, loc, dire, 60 * 3, "PlayerBullet", { 1.0f,1.0f,0.0f,1.0f });
	new CMissile(mOwnerInterface, missilePos_R, dire, qua, 60, "PlayerBullet");
	new CMissile(mOwnerInterface, missilePos_L, dire, qua, 60, "PlayerBullet");

	CSoundManager::GetInstance().PlaySound("SHOT");
}

void CFighter::ShotReset()
{
	mShotCnt = 0;
}

void CFighter::Move()
{
	XMFLOAT3 fv = Transform.GetForwardVectorRelative();
	float dt = CGameManager::GetInstance().GetDeltaTime();

	Transform.Location.x += fv.x * (mSpeed*dt);
	Transform.Location.y += fv.y * (mSpeed*dt);
	Transform.Location.z += fv.z * (mSpeed*dt);
}

void CFighter::Particle(CActor& actor)
{
	if (!mIsParticleFlag)
	{
		XMFLOAT3 loc = mScene->Transform.Location;
		XMFLOAT3 fvR = mScene->Transform.GetRightVectorRelative();
		XMFLOAT3 fvU = mScene->Transform.GetUpwardVectorRelative();
		loc.x += fvU.x * 2.f;
		loc.y += fvU.y * 2.f;
		loc.z += fvU.z * 2.f;
		mParticleLocR = { loc.x + (fvR.x*1.5f),loc.y + (fvR.y*1.5f),loc.z + (fvR.z*1.5f) };
		mParticleLocL = { loc.x - (fvR.x*1.5f),loc.y - (fvR.y*1.5f),loc.z - (fvR.z*1.5f) };
		mIsParticleFlag = true;
	}
	CSphereMeshComponent& sphereMesh1 = *new CSphereMeshComponent(actor, actor.Transform, { 1,0,0,1 });
	sphereMesh1.Transform.Scale = { 0.5f,0.5f,0.5f };
	sphereMesh1.Transform.Location = mParticleLocR;

	CSphereMeshComponent& sphereMesh2 = *new CSphereMeshComponent(actor, actor.Transform, { 1,0,0,1 });
	sphereMesh2.Transform.Scale = { 0.5f,0.5f,0.5f };
	sphereMesh2.Transform.Location = mParticleLocL;
}

void CFighter::Rot(int dire)
{
	if (dire == 0)
	{
		mRotFlag = true;
		Transform.Rotation.AddAngleRelative({ 0,-1,0 });
		if (mMeshRotZ < MAXROT)
		{
			mMeshRotZ += 1.5;
			mScene->Transform.Rotation.AddAngleRelative({ 0,0,1.5f });
		}
	}
	else if (dire == 1)
	{
		mRotFlag = true;
		Transform.Rotation.AddAngleRelative({ 0,1,0 });
		if (mMeshRotZ > -MAXROT)
		{
			mMeshRotZ -= 1.5;
			mScene->Transform.Rotation.AddAngleRelative({ 0,0,-1.5f });
		}
	}
	else if (dire == 2)
	{
		
		Transform.Rotation.AddAngleRelative({ -1,0,0 });
	}
	else if (dire == 3)
	{
		
		Transform.Rotation.AddAngleRelative({ 1,0,0 });
	}

}

void CFighter::SpeedChange(int type)
{
	if (type == 0)
	{
		if (mSpeed < mSpeedLimitMax)mSpeed += 0.5f;
	}
	else if (type == 1)
	{
		if (mSpeed > mSpeedLimitMin)mSpeed -= 0.5f;
	}
}

void CFighter::Tick()
{
	if (mStartDelay)
	{
		static float alpha = 0.f;
		alpha += 0.01;
		LCMath::Lerp(mCameraStatus.StartPos.x, mCameraStatus.EndPos.x, alpha, mCameraLoc.x);
		LCMath::Lerp(mCameraStatus.StartPos.y, mCameraStatus.EndPos.y, alpha, mCameraLoc.y);
		LCMath::Lerp(mCameraStatus.StartPos.z, mCameraStatus.EndPos.z, alpha, mCameraLoc.z);
		CComponent* buf;
		if (GetComponent<CCameraComponent>(buf))
		{
			XMFLOAT3 loc = Transform.Location;
			loc.y += 5;
			loc.z += 5;
			CCameraComponent& camera = *dynamic_cast<CCameraComponent*>(buf);
			camera.SetView(mCameraLoc, loc, { 0.f,1.f,0.f });
		}
		if (alpha >= 1)
		{
			mStartDelay = false;
			alpha = 0.f;
			CInputManager::GetInstance().AddEvent("Shot", EButtonOption::PRESS, *this, { EButtonType::KEYBOARD,DIK_SPACE }, std::bind(&CFighter::Shot, std::ref(*this)));
			CInputManager::GetInstance().AddEvent("Rot-Y", EButtonOption::PRESS, *this, { EButtonType::KEYBOARD,DIK_A }, std::bind(&CFighter::Rot, std::ref(*this), 0));
			CInputManager::GetInstance().AddEvent("Rot+Y", EButtonOption::PRESS, *this, { EButtonType::KEYBOARD,DIK_D }, std::bind(&CFighter::Rot, std::ref(*this), 1));
			CInputManager::GetInstance().AddEvent("Rot-X", EButtonOption::PRESS, *this, { EButtonType::KEYBOARD,DIK_W }, std::bind(&CFighter::Rot, std::ref(*this), 2));
			CInputManager::GetInstance().AddEvent("Rot+X", EButtonOption::PRESS, *this, { EButtonType::KEYBOARD,DIK_S }, std::bind(&CFighter::Rot, std::ref(*this), 3));

		}
	}
	else
	{
		Move();
		if (!mRotFlag)
		{
			if (mMeshRotZ > 0)
			{
				mMeshRotZ -= 1.5;
				mScene->Transform.Rotation.AddAngleRelative({ 0,0,-1.5f });
			}
			else if (mMeshRotZ < 0)
			{
				mMeshRotZ += 1.5;
				mScene->Transform.Rotation.AddAngleRelative({ 0,0,1.5f });
			}
		}
		
		mRotFlag = false;
		mIsParticleFlag = false;
	}
}

void CFighter::EventAtBeginCollide(CActor& collideActor)
{
	if (collideActor.HasTag("EnemyBullet"))
	{
		mOwnerInterface.Notice(*this);

		/*Destroy();*/
		collideActor.Destroy();

		CSoundManager::GetInstance().PlaySound("BOMB");
	}
}
