#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CSphereMeshComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Components/CParticleGeneratorComponent.h"
#include "GameFramework/Components/CVisionComponent.h"
#include "GameFramework/Managers/CGameManager.h"
#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Library/LCMath.h"

#include "CMissile.h"
#include "CEnemy.h"

CMissile::CMissile(ILevel& partner, XMFLOAT3 initLocation, XMFLOAT3 direction, XMFLOAT4 quaternion, int destroyFrame, std::string tag, XMFLOAT4 bulletColor)
	:CActor(partner), mDirection(direction), mDestroyFrame(destroyFrame)
{
	AddTag(tag);

	CStaticMeshComponent& mesh = *new CStaticMeshComponent(*this, Transform,
		CModelDataManager::GetInstance().GetModel("Assets/Models/Missile/AIM120D.obj", "Assets/Models/Missile/Textures/"),
		"Shader/vs.hlsl", "Shader/ps.hlsl");
	mesh.Transform.Location = initLocation;
	mesh.Transform.Rotation.SetQuaternion(quaternion);
	mesh.Transform.Scale = { 0.5f,0.5f,0.5f };
	CSphereColliderComponent& collider = *new CSphereColliderComponent(*this, mesh.Transform);
	collider.SetObjectType(tag);
	collider.Transform.Scale = { 2.f,2.f,2.f };

	//パーティクルアクター用の空アクター作成
	CActor& particle = *new CActor(partner);

	//パーティクル作成時に行う振舞いの作成
	auto createParticle = [&](CActor& actor)
	{
		CSphereMeshComponent& sphere = *new CSphereMeshComponent(actor, actor.Transform);
		sphere.Transform.Scale = { 2.0f,2.0f,2.0f };
		sphere.Transform.Location = mesh.Transform.Location;
	};
	
	//コーンパーティクル作成
	mParticle = new CParticleGeneratorComponent(particle, Transform, createParticle,
		0.3f, 0.f, 150.0f, *new CParticleBaseGeneratorLine({ 0.0f,1.0f,0.0f }));
	
	//CVisionComponent* vision = new CVisionComponent(*this, Transform, 1500, 25, std::bind(&CMissile::Look, std::ref(*this), std::placeholders::_1));
}

void CMissile::Tick()
{
	float dt = CGameManager::GetInstance().GetDeltaTime();

	mFrame++;

	Transform.Location.x += mDirection.x * (500.0f * dt);
	Transform.Location.y += mDirection.y * (500.0f * dt);
	Transform.Location.z += mDirection.z * (500.0f * dt);

	if (mFrame >= mDestroyFrame)
	{
		Destroy();
		mParticle->SetShouldUpdate(false);
	}
}

void CMissile::Look(CActor& collideActor)
{
	if (collideActor.HasTag("Enemy"))
	{
		float length;
		length = LCMath::CalcFloat3Length(LCMath::CalcFloat3FromStartToGoal(Transform.Location, collideActor.Transform.Location));

		if (length > 300.f)
		{
			Transform.Rotation.ChangeQuaternionToLocation(collideActor.Transform.GetWorldLocation());
			XMFLOAT3 direction = LCMath::CalcFloat3FromStartToGoal(Transform.Location, collideActor.Transform.Location);
			LCMath::CalcFloat3Normalize(direction, direction);
			mDirection = direction;
		}

	}
}
