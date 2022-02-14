#include "CPointer.h"
#include "CTrialActor.h"
#include "GameFramework/Components/CBillboardComponent.h"
#include "GameFramework/Game/CApplication.h"
#include "GameFramework/Managers/CInputManager.h"
#include "GameFramework/ExternalTools/imgui/myimgui.h"
#include "GameFramework/Level/CLevel.h"

CPointer::CPointer(ILevel& partner , CActor& owner):CActor(partner) , mOwner(owner)
{
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

	Transform.Location.x = mInitLocation->x;
}