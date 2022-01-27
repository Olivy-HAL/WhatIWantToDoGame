#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Managers/CGameManager.h"

#include "CSkyDome.h"
#include "CFighter.h"

CSkyDome::CSkyDome(ILevel& owner) :CActor(owner)
{
	mMesh = new CStaticMeshComponent(*this, Transform,
		CModelDataManager::GetInstance().GetModel("Assets/Models/Skydome/Dome_BB601.x", "Assets/Models/Skydome/"),
		"Shader/vs.hlsl", "Shader/pstexcol.hlsl");
	mMesh->Transform.Scale = { 70.0f,70.0f,70.0f };

}

CSkyDome::CSkyDome(ILevel& owner, CFighter& fighter):CActor(owner)
{
	mMesh = new CStaticMeshComponent(*this , Transform ,
		CModelDataManager::GetInstance().GetModel("Assets/Models/Skydome/Dome_BB601.x" , "Assets/Models/Skydome/") ,
		"Shader/vs.hlsl" , "Shader/pstexcol.hlsl");
	mMesh->Transform.Scale = { 70.0f,70.0f,70.0f };

	mFighterTransform = &fighter.Transform;
	mFighterSpeed = fighter.GetSpeed();

	CSphereColliderComponent& collider = *new CSphereColliderComponent(*this, mMesh->GetModel(), mMesh->Transform);
	collider.Transform.Scale = { 0.3f,0.3f,0.3f };
}

void CSkyDome::Tick()
{
	if (!mIsOutSide)
	{
		XMFLOAT3 fv = mFighterTransform->GetForwardVectorRelative();
		float dt = CGameManager::GetInstance().GetDeltaTime();
		Transform.Location.x += fv.x * (mFighterSpeed * dt);
		Transform.Location.y += fv.y * (mFighterSpeed * dt);
		Transform.Location.z += fv.z * (mFighterSpeed * dt);
	}
}

void CSkyDome::EventAtBeginCollide(CActor& collideActor)
{
	if (collideActor.HasTag("Fighter"))
	{
		mIsOutSide = true;
	}
}

void CSkyDome::EventAtEndCollide(CActor& collideActor)
{
	if (collideActor.HasTag("Fighter"))
	{
		mIsOutSide = false;
	}
}
