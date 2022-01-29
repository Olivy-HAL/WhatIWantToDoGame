#pragma once

#include "GameFramework/Level/CLevel.h"

class CTrailLevel :public CLevel
{
private:
public:
	using CLevel::CLevel;

	void Init() override;
	void Tick() override;

};