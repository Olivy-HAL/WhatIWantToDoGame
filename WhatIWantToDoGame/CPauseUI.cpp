#include "CPauseUI.h"

CPauseUI::CPauseUI(ILevel& owner, std::string texturePath, XMFLOAT3 scale,
	float loc_x, float loc_y, XMFLOAT4 color)
{
	mDisplay2D = new CDisplay2DActor(owner, texturePath);
	mDisplay2D->Transform.Scale = scale;
	mDisplay2D->Transform.Location.x = loc_x;
	mDisplay2D->Transform.Location.y = loc_y;
	mDisplay2D->SetColor(color);

}

void CPauseUI::Update()
{
	if (mSelect)
	{
		mDisplay2D->SetColor({0.2f,0.8f,1.f,0.9});
	}
	else
	{
		mDisplay2D->SetColor({ 1.f,1.f,1.f,0.9f });
	}
	mSelect = false;
}

void CPauseUI::Destroy()
{
	mDisplay2D->Destroy();
}