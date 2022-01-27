#include "GameFramework/Game/CApplication.h"

#include "CMainUI.h"

CMainUI::CMainUI(ILevel& owner) :CActor(owner)
{
	mRader = new CDisplay2DActor(owner, "Assets/Textures/Main/ƒŒ[ƒ_[.png");
	mRader->Transform.Scale = {150,150,0.f};
	mRader->Transform.Location.x = static_cast<float>(75);
	mRader->Transform.Location.y = static_cast<float>(75);
}