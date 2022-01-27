#pragma once
#include <string>

#include "GameFramework/Level/CLevel.h"
#include "GameFramework/Actor/CDisplay2DActor.h"

class CPauseUI
{
private:
	CDisplay2DActor* mDisplay2D;
	bool mSelect = false;
public:
	CPauseUI(ILevel& owner, std::string texturePath,XMFLOAT3 scale,
		float loc_x,float loc_y,XMFLOAT4 color);
	void Update();
	void SetSelect(bool flg) { mSelect = flg; }
	void Destroy();
};

