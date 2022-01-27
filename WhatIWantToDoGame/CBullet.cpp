#include "GameFramework/Components/CSphereMeshComponent.h"
#include "GameFramework/Components/CSphereColliderComponent.h"
#include "GameFramework/Managers/CGameManager.h"
#include "GameFramework/Managers/CSoundManager.h"

#include "CBullet.h"

CBullet::CBullet(ILevel& partner , XMFLOAT3 initLocation , XMFLOAT3 direction , int destroyFrame, std::string tag, XMFLOAT4 bulletColor)
	:CActor(partner) ,
	mDirection(direction) , mDestroyFrame(destroyFrame)
{
	AddTag(tag);
	Transform.Location = initLocation;
	CSphereMeshComponent& mesh = *new CSphereMeshComponent(*this , Transform , bulletColor);
	//mesh.Transform.Location = initLocation;
	mesh.Transform.Scale = { 2.0f,2.0f,2.0f };

	CSphereColliderComponent& collider = *new CSphereColliderComponent(*this , mesh.Transform);
	collider.SetObjectType(tag);

}

void CBullet::Tick()
{
	float dt = CGameManager::GetInstance().GetDeltaTime();
	mFrame++;

	Transform.Location.x += mDirection.x*(250.0f*dt);
	Transform.Location.y += mDirection.y*(250.0f*dt);
	Transform.Location.z += mDirection.z*(250.0f*dt);
	

	if(mFrame == mDestroyFrame)
	{
		Destroy();
	}
}
