#include <random>

#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CVisionComponent.h"

#include "GameFramework/Level/CLevel.h"

#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Managers/CSoundManager.h"

#include "CBullet.h"
#include "CEnemy.h"
#include "CEffectActor.h"

CEnemy::CEnemy(ILevel& owner, XMFLOAT3 loc, XMFLOAT3 angle, int num) :CActor(owner), mNumber(num)
{
	AddTag("Enemy");
	Transform.Location = loc;
	Transform.Rotation.ChangeQuaternionToLocation(angle);

	CStaticMeshComponent& mesh = *new CStaticMeshComponent(*this, Transform,
		CModelDataManager::GetInstance().GetModel("Assets/Models/Enemy/f1.x", "Assets/Models/Enemy/Texture/"),
		"Shader/vs.hlsl", "Shader/ps.hlsl");

	CSphereColliderComponent& collider = *new CSphereColliderComponent(*this, mesh.GetModel(), Transform);
	CVisionComponent* vision = new CVisionComponent(*this, Transform, 500, 25, std::bind(&CEnemy::Look, std::ref(*this), std::placeholders::_1));
}

void CEnemy::Move()
{
	XMFLOAT3 fv = Transform.GetForwardVectorRelative();

	Transform.Location.x += fv.x * 1.5f;
	Transform.Location.y += fv.y * 1.5f;
	Transform.Location.z += fv.z * 1.5f;
}

void CEnemy::Shot()
{
	if (mShotCnt % 5 != 0)
	{
		mShotCnt++;
		return;
	}
	mShotCnt++;

	XMFLOAT3 loc = Transform.GetWorldLocation();
	XMFLOAT3 fv = Transform.GetForwardVectorRelative();

	loc.x += fv.x * 10.0f;
	loc.y += fv.y * 10.0f + 2.0f;
	loc.z += fv.z * 10.0f;

	new CBullet(mOwnerInterface, loc, fv, 60 * 3, "EnemyBullet", { 1.0f,0.0f,1.0f,1.0f });

	CSoundManager::GetInstance().PlaySound("SHOT");
}

void CEnemy::Look(CActor& collideActor)
{
	if (collideActor.HasTag("Fighter"))
	{
		std::random_device rd;
		std::mt19937 mt(rd());
		float length;
		length = LCMath::CalcFloat3Length(LCMath::CalcFloat3FromStartToGoal(Transform.Location, collideActor.Transform.Location));
		if (length > 100)
		{
			Transform.Rotation.ChangeQuaternionToLocation(collideActor.Transform.GetWorldLocation());
			if (mt() % 200 == 7) Shot();
		}

	}
}

void CEnemy::Tick()
{
	Move();
}

void CEnemy::EventAtBeginCollide(CActor& collideActor)
{
	if (collideActor.HasTag("PlayerBullet"))
	{
		mOwnerInterface.Notice(*this);
		CEffectActor& effect = *new CEffectActor(mOwnerInterface, Transform.Location,
			"Assets/Textures/Anim/Explosion.png",10,1,"Explosion");
		Destroy();
		collideActor.Destroy();

		CSoundManager::GetInstance().PlaySound("BOMB");
	}
}
