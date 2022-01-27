#pragma once

#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Transform/CTransform.h"
#include "GameFramework/Components/CStaticMeshComponent.h"

class CSelectActor :public CActor
{
private:
	CStaticMeshComponent* mMesh;
public:
	CSelectActor(ILevel& owner, CTransform& parentTrans, CModelData& model, XMFLOAT3 loc, XMFLOAT3 angle = { 0,0,0 });

	void Tick()override;
	CStaticMeshComponent* GetMesh() { return mMesh; }
};