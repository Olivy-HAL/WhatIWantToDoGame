#include "CSelectActor.h"

CSelectActor::CSelectActor(ILevel& owner, CTransform& parentTrans, CModelData& model, XMFLOAT3 loc, XMFLOAT3 angle)
	:CActor(owner)
{
	parentTrans.AttachTransform(Transform);
	Transform.Location = loc;
	mMesh = new CStaticMeshComponent(*this, Transform, model, "Shader/vs.hlsl", "Shader/ps.hlsl");
	mMesh->Transform.Rotation.SetAngle(angle);
}

void CSelectActor::Tick()
{
	Transform.Rotation.AddAngleWorld({ 0.f,-1.f,0.f });
}
