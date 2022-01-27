#include "CSelectFighter.h"

#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CLightComponent.h"
#include "GameFramework/Components/CCameraComponent.h"

#include "GameFramework/Managers/CModelDataManager.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CSoundManager.h"
#include "GameFramework/Game/CApplication.h"

CSelectFighter::CSelectFighter(ILevel& owner) :CActor(owner)
{
	mSelect = PlayerSelect::F15C;
	mScene = new CSceneComponent(*this, Transform);

	XMFLOAT3 fv = Transform.GetForwardVectorRelative();
	XMFLOAT3 loc = Transform.Location;

	loc.z += fv.z * 20.0f;

	mMeshs.emplace_back(new CSelectActor(owner, mScene->Transform,
		//CModelDataManager::GetInstance().GetModel("Assets/Models/Boeing/FA-18F.obj", "Assets/Models/Boeing/Textures/"), loc));
		CModelDataManager::GetInstance().GetModel("Assets/Models/F15C/F-15C.fbx", "Assets/Models/F15C/Textures/"), loc));
	mMeshs.back()->GetMesh()->Transform.Scale = { 0.01f,0.01f,0.01f };
	loc.z -= loc.z * 2;

	mMeshs.emplace_back(new CSelectActor(owner, mScene->Transform,
		CModelDataManager::GetInstance().GetModel("Assets/Models/Fighter/F-15E.fbx", "Assets/Models/Fighter/Textures/"), loc, { -90.0f ,0.0f,180.0f }));
	Init();
}

void CSelectFighter::Init()
{
	CSoundManager::GetInstance().CreateSoundInfo("Assets/Sounds/shot.wav", 0.05f, false, "SHOT");

	CCameraComponent& camera = *new CCameraComponent(*this);

	XMFLOAT3 fv = Transform.GetForwardVectorRelative();
	XMFLOAT3 loc = Transform.Location;
	//loc.y += 5;
	loc.y += fv.y*-20.0f + 2.0f;
	loc.z += fv.z*20.0f;

	XMFLOAT3 cameraLoc = Transform.Location;
	cameraLoc.y += fv.y*-20.0f + 5.0f;
	cameraLoc.z += fv.z;

	camera.SetProjection(10.f, 10000.f, XM_PI / 4.f, CApplication::CLIENT_WIDTH, CApplication::CLIENT_HEIGHT);
	camera.SetView(cameraLoc, loc, { 0.f,1.f,0.f });

	CInputManager::GetInstance().AddEvent("SelectPosi", EButtonOption::TRIGGER, *this, { {EButtonType::KEYBOARD,DIK_D},{EButtonType::KEYBOARD,DIK_RIGHT} }, std::bind(&CSelectFighter::ChangePosi, std::ref(*this)));
	CInputManager::GetInstance().AddEvent("SelectNega", EButtonOption::TRIGGER, *this, { {EButtonType::KEYBOARD,DIK_A},{EButtonType::KEYBOARD,DIK_LEFT} }, std::bind(&CSelectFighter::ChangeNega, std::ref(*this)));

}

void CSelectFighter::Tick()
{
	
	if (mRotatePosiFlag || mRotateNegaFlag)
	{
		if (mRotatePosiFlag)
		{
			mScene->Transform.Rotation.AddAngleRelative({ 0.f, mAlpha, 0.f });
		}
		else if (mRotateNegaFlag)
		{
			mScene->Transform.Rotation.AddAngleRelative({ 0.f, -mAlpha, 0.f });
		}
		mRotationValue -= mAlpha;
		if (mRotationValue < 0)
		{
			mRotatePosiFlag = false;
			mRotateNegaFlag = false;
		}

	}
}

void CSelectFighter::ChangePosi()
{
	if (!mRotatePosiFlag && !mRotateNegaFlag)
	{
		mRotationValue = 360 / PlayerSelect::END;
		mRotatePosiFlag = true;
		mSelect = static_cast<CSelectFighter::PlayerSelect>(mSelect + 1);
		if (mSelect == CSelectFighter::PlayerSelect::END) mSelect = CSelectFighter::PlayerSelect::F15C;
	}
}

void CSelectFighter::ChangeNega()
{
	if (!mRotatePosiFlag && !mRotateNegaFlag)
	{
		mRotationValue = 360 / PlayerSelect::END;
		mRotateNegaFlag = true;
		mSelect = static_cast<CSelectFighter::PlayerSelect>(mSelect - 1);
		if (mSelect < CSelectFighter::PlayerSelect::F15C) mSelect = CSelectFighter::PlayerSelect::FIGHTER;
	}
}

CModelData& CSelectFighter::GetModel()
{
	if (mSelect == PlayerSelect::FIGHTER)
	{
		return CModelDataManager::GetInstance().GetModel("Assets/Models/Fighter/F-15E.fbx", "Assets/Models/Fighter/Textures/");
	}
	else if (mSelect == PlayerSelect::F15C)
	{
		return CModelDataManager::GetInstance().GetModel("Assets/Models/F15C/F-15C.fbx", "Assets/Models/F15C/Textures/");
	}
}

CStaticMeshComponent& CSelectFighter::GetMesh()
{
	int num = mSelect;
	return *mMeshs.at(num)->GetMesh();
}