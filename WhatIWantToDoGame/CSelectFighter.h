#pragma once
#include <vector>
#include <memory>

#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CSceneComponent.h"
#include "GameFramework/Actor/CActor.h"

#include "CSelectActor.h"

class CModelData;

class CSelectFighter :public CActor
{
public:
	enum PlayerSelect
	{
		F15C = 0,
		FIGHTER,
		END
	};

private:
	std::vector<CSelectActor*> mMeshs;
	CSceneComponent* mScene;
	PlayerSelect mSelect;
	CStaticMeshComponent* mMesh;

	bool mRotatePosiFlag = false;
	bool mRotateNegaFlag = false;
	float mAlpha=2.0f;
	float mRotationValue;

	void Tick() override;
public:
	CSelectFighter(ILevel& owner);

	void Init();

	void ChangePosi();
	void ChangeNega();

	CModelData& GetModel();
	CStaticMeshComponent& GetMesh();
};