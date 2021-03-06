#include "CPointer.h"
#include "CTrailActor.h"
#include "GameFramework/Components/CBillboardComponent.h"
#include "GameFramework/Game/CApplication.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/ExternalTools/imgui/myimgui.h"
#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Game/CApplication.h"

CPointer::CPointer(ILevel& partner , CActor& owner):CActor(partner) , mOwner(owner)
{
	int displayCenterPosX = GetSystemMetrics(SM_CXSCREEN) / 2;
	int displayCenterPosY = GetSystemMetrics(SM_CYSCREEN) / 2;

	SetCursorPos(displayCenterPosX , displayCenterPosY);
	mDiffPosX = CApplication::CLIENT_WIDTH / 2;
	mDiffPosY = CApplication::CLIENT_HEIGHT / 2;

	CBillboardComponent& billboard = *new CBillboardComponent(*this , Transform , "Assets/Textures/Pointer/Pointer.png");
	billboard.Transform.Scale = { 10.0f,10.0f,1.0f };
}

void CPointer::Tick()
{
	if(mInitLocation == nullptr)
	{
		mInitLocation.reset(new XMFLOAT3);
		*mInitLocation = mOwner.Transform.Location;
	}

	float posX , posY;
	//posX = mDiffPosX / 6.f;
	//posY = mDiffPosY / 6.f;

	Transform.Location.x = mInitLocation->x ;
	//Transform.Location.y = mInitLocation->y ;
}