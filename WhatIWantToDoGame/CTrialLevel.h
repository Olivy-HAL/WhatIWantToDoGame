#pragma once

#include "GameFramework/Level/CLevel.h"

class CTrialLevel :public CLevel
{
private:
public:
	using CLevel::CLevel;

	void Init() override;
	void Tick() override;

};