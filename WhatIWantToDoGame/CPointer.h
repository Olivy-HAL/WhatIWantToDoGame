#pragma once
#include <memory>
#include "GameFramework/Actor/CActor.h"

class CPointer :public CActor
{
private:
	CActor& mOwner;
	std::unique_ptr<XMFLOAT3> mInitLocation;

	float mInitMousePosX;
	float mInitMousePosY;
	float mDiffPosX;
	float mDiffPosY;
public:
	CPointer(ILevel& partner , CActor& owner);

	void Tick()override;
};

