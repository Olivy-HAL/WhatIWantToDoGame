#include "CPointLightComponent.h"

#include "CSpotLightComponent.h"

//!
//! @file
//! @brief スポットライトコンポーネントのソースファイル
//!

CSpotLightComponent::CSpotLightComponent(CActor& owner, CTransform& parentTrans,
	XMFLOAT4 attenuation, XMFLOAT3 direction, float angle, XMFLOAT3 location) :
	CPointLightComponent(owner, parentTrans, attenuation, location),
	mDirection(direction),
	mAngle(angle)
{
	mType = EType::SPOT;
}