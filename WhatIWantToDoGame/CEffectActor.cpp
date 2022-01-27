#include "CEffectActor.h"
#include "GameFramework/Components/CBillboardComponent.h"

CEffectActor::CEffectActor(ILevel& owner, XMFLOAT3 loc, std::string texturePath,
	int divWidth, int divHeight, std::string alias) :CActor(owner),mAlias(alias)
{
	Transform.Location = loc;
	CBillboardComponent& billboard = *new CBillboardComponent(*this, Transform, texturePath);
	billboard.Transform.Scale = {10.f,10.f,10.f};
	auto updateVertex = [&]
	{
		billboard.UpdateVertexBuffer();
	};
	mAnim = new C2DAnimationComponent(*this, divWidth, divHeight);

	mAnim->AddAnimData(billboard.GetUV(0), billboard.GetUV(1),
		billboard.GetUV(2), billboard.GetUV(3), updateVertex, alias);
	mAnim->AddAnimInfo(alias,0,9,1.f,false);
	mAnim->Play(alias, alias);
	
}

void CEffectActor::Tick()
{
	if (!mAnim->CheckIsPlay(mAlias))
	{
		mAnim->DeleteAlias(mAlias);
		Destroy();
	}
}