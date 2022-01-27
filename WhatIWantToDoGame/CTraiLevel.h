#pragma once

#include "GameFramework/Level/CLevel.h"

class CTraiLevel :public CLevel
{
private:
public:
	using CLevel::CLevel;

	void Init() override;
	void Tick() override;

};