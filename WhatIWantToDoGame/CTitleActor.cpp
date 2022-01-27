#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Managers/CGameManager.h"

#include "GameFramework/Components/CSphereMeshComponent.h"
#include "GameFramework/Components/CCameraComponent.h"
#include "GameFramework/Components/CParticleGeneratorComponent.h"
#include "GameFramework/Game/CApplication.h"

#include "CTitleActor.h"

CTitleActor::CTitleActor(ILevel& owner) :CActor(owner)
{
	mMesh = new CStaticMeshComponent(*this, Transform,
		CModelDataManager::GetInstance().GetModel("Assets/Models/Fighter/F-15E.fbx", "Assets/Models/Fighter/Textures/")
		, "Shader/vs.hlsl", "Shader/ps.hlsl");
	mMesh->Transform.Rotation.SetAngle({ -90.0f ,0.0f,180.0f });

	CCameraComponent& camera = *new CCameraComponent(*this);
	XMFLOAT3 fv = Transform.GetForwardVectorRelative();
	XMFLOAT3 loc = Transform.Location;
	loc.y += 5;

	XMFLOAT3 cameraLoc = Transform.Location;
	cameraLoc.y += fv.y*-20.0f + 10.0f;
	cameraLoc.z += fv.z*-20.0f;

	camera.SetProjection(10.f, 10000.f, XM_PI / 4.f, CApplication::CLIENT_WIDTH, CApplication::CLIENT_HEIGHT);
	camera.SetView(cameraLoc, loc, { 0.f,1.f,0.f });

	XMFLOAT3 forwardVec = Transform.GetForwardVectorWorld();
	forwardVec.x *= -1;
	forwardVec.y *= -1;
	forwardVec.z *= -1;

	//コーンパーティクル作成
	new CParticleGeneratorComponent(*this, Transform, std::bind(&CTitleActor::Particle, std::ref(*this), std::placeholders::_1),
		2.f, 2.f, 60, *new CParticleBaseGeneratorCone(forwardVec, 20));

	//タグ追加
	AddTag("Player");
}

void CTitleActor::Tick()
{
	CComponent* buf;
	GetComponent<CCameraComponent>(buf);
	CCameraComponent& camera = *dynamic_cast<CCameraComponent*>(buf);
	XMFLOAT3 locEye = camera.GetEye();
	XMFLOAT3 locAct = camera.GetLookAt()/*mMesh->Transform.Location*/;
	//locAct.y += 5;

	if (std::abs(locEye.x) > 30 && !mChangeFlg)
	{
		mOwnerInterface.Notice(*this);
		mChangeFlg = true;
	}
	if (std::abs(locEye.z) > 60) mIncreZPos *= -1;
	locEye.x += mIncreXPos;
	locEye.z += mIncreZPos;
	camera.SetView(locEye,locAct, { 0.f,1.f,0.f });
	
	Move();
}

void CTitleActor::Move()
{
	XMFLOAT3 fv = Transform.GetForwardVectorRelative();
	float dt = CGameManager::GetInstance().GetDeltaTime();

	Transform.Location.x += fv.x * (mSpeed*dt);
	Transform.Location.y += fv.y * (mSpeed*dt);
	Transform.Location.z += fv.z * (mSpeed*dt);
}

void CTitleActor::Particle(CActor& actor)
{
	XMFLOAT3 loc = actor.Transform.Location;
	XMFLOAT3 fvR = actor.Transform.GetRightVectorRelative();
	loc.x += fvR.x * 1.5f;
	loc.y += fvR.y * 2.f;
	loc.z += fvR.z * 1.5f;
	CSphereMeshComponent& sphereMesh1 = *new CSphereMeshComponent(actor, actor.Transform, { 1,0.5,0.5,1 });
	sphereMesh1.Transform.Scale = { 0.3f,0.3f,0.3f };
	sphereMesh1.Transform.Location = loc;

	loc.x *= -1;
	loc.y *= -1;
	loc.z *= -1;
	CSphereMeshComponent& sphereMesh2 = *new CSphereMeshComponent(actor, actor.Transform, { 1,0.5,0.5,1 });
	sphereMesh2.Transform.Scale = { 0.3f,0.3f,0.3f };
	sphereMesh2.Transform.Location = loc;
}
