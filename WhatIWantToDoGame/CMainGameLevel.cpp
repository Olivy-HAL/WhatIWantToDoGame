#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Components/CCameraComponent.h"

#include "GameFramework/Actor/CActorGenerator.h"
#include "GameFramework/Actor/CActor.h"
#include "GameFramework/Actor/CFeedActor.h"

#include "GameFramework/ExternalTools/imgui/myimgui.h"
#include "GameFramework/Game/CApplication.h"

#include "GameFramework/Managers/CGameManager.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/Managers/CLightManager.h"
#include "GameFramework/Managers/CSoundManager.h"

#include "CSkyDome.h"

#include "CTitle.h"
#include "CSelectLevel.h"
#include "CMainGameLevel.h"
#include "CPause.h"
#include "CMainUI.h"

CMainGameLevel::CMainGameLevel(IGame& owner, const CModelData& modelData, const CTransform& trans, bool isFeed)
	:CLevel(owner, isFeed), mPlayerModel(modelData), mStartTransform(trans)
{}

void CMainGameLevel::Init()
{
	new CFeedActor(*this, nullptr, CFeedActor::EOption::FEEDIN);

	CComponent* buf;

	mFighter = new CFighter(*this, mPlayerModel, mStartTransform);
	//mFighter->Transform.Location.z = -500.0f;

	CSkyDome& skyDome = *new CSkyDome(*this, *mFighter);
	
	skyDome.GetComponent<CStaticMeshComponent>(buf);
	XMFLOAT3 min, max;
	min = max = { 0.0f,0.0f,0.0f };
	CStaticMeshComponent& skyDomeMesh = dynamic_cast<CStaticMeshComponent&>(*buf);

	for (auto& mesh : skyDomeMesh.GetModel().GetMeshes())
	{
		for (auto& vertex : mesh.Vertices)
		{
			if (min.x > vertex.Pos.x)min.x = vertex.Pos.x;
			else if (max.x < vertex.Pos.x)max.x = vertex.Pos.x;

			if (min.z > vertex.Pos.z)min.z = vertex.Pos.z;
			else if (max.z < vertex.Pos.z)max.z = vertex.Pos.z;
		}
	}
	min.x *= 20;
	min.z *= 20;
	max.x *= 20;
	max.z *= 20;
	mEGenerator = new CEnemyGenerator(*this, { min.x, min.z }, { max.x, max.z }, skyDome.Transform.Location, 10.f);

	CInputManager::GetInstance().AddEvent("Pause", EButtonOption::TRIGGER, *this, { EButtonType::KEYBOARD,DIK_TAB }, std::bind(&CMainGameLevel::Pause, std::ref(*this)));

	//CMainUI& ui = *new CMainUI(*this);

	mFighter->GetComponent<CCameraComponent>(buf);
	RequestSetCamera(*dynamic_cast<CCameraComponent*>(buf));

	CLightManager::GetInstance().SetDirectionLight({ 1.0f,1.0f,-1.0f });
	CLightManager::GetInstance().SetAmbientLight({ 0.1f,0.1f,0.1f });
}

void CMainGameLevel::Tick()
{

	if ((mIsGameOver || mTime <= 0.0f) && !mIsEnd)
	{
		mIsEnd = true;

		//std::string scoreStr = "Score:" + std::to_string(mScore);
		//MessageBox(nullptr, scoreStr.c_str(), "GameOver!", MB_OK);
		new CSelectLevel(mOwnerInterface, true);
	}

}

void CMainGameLevel::Notice(CActor& actor)
{
	if (actor.HasTag("Enemy"))
	{
		mAliveEnemy--;
		if (mAliveEnemy == 0)
		{
			for (auto itr = mEGenerator->mAliveEnemy.begin(); itr != mEGenerator->mAliveEnemy.end(); )
			{
				mEGenerator->mAliveEnemy.erase(itr);
			}
			mEGenerator->mAliveEnemy.shrink_to_fit();
			mAliveEnemy = 3;
		}
	}
	else if (actor.HasTag("Fighter"))
	{
		mIsGameOver = true;
	}
}

void CMainGameLevel::Pause()
{
	if (mPauseFlg)
	{
		Resume();
		CInputManager::GetInstance().DeleteEvent("Decision");
	}
	else
	{
		CGameManager::GetInstance().SetIsPause(true);
		mPause = new CPause(*this);
		mPauseFlg = true;
		CInputManager::GetInstance().AddEvent("Decision", EButtonOption::TRIGGER, *this, { EButtonType::KEYBOARD,DIK_RETURN }, std::bind(&CMainGameLevel::Decision, std::ref(*this)));
	}
}

void CMainGameLevel::Decision()
{
	if (mPause->GetSelect() == ::CPause::SelectButton::RESTART) new CMainGameLevel(mOwnerInterface, mPlayerModel, mStartTransform, true);
	else if (mPause->GetSelect() == ::CPause::SelectButton::CONFIG) 
	{
		CSoundManager::GetInstance().PlaySound("NONDECISION");
		return;
	}
	else if (mPause->GetSelect() == ::CPause::SelectButton::END) new CSelectLevel(mOwnerInterface, true);

	Resume();
}

void CMainGameLevel::Resume()
{
	CGameManager::GetInstance().SetIsPause(false);
	mPause->Cancel();
	mPauseFlg = false;
	CInputManager::GetInstance().DeleteEvent("Decision");
	CSoundManager::GetInstance().PlaySound("DECISION");
}