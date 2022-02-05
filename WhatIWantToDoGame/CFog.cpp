#include <random>

#include "CFog.h"
#include "GameFramework/Components/CBillboardComponent.h"

CFog::CFog(ILevel& partner, XMFLOAT3 loc) :CActor(partner)
{
	std::random_device randomSeed;							//乱数デバイス
	std::mt19937 randomEngine(randomSeed());				//乱数アルゴリズム
	std::uniform_int_distribution<> randomScope(0, 1);		//範囲指定乱数生成器
	int random = randomScope(randomEngine);

	Transform.Location = loc;
	if (random == 0)
	{
		CBillboardComponent& billboard = *new CBillboardComponent(*this, Transform, "Assets/Textures/Trail/Fog01.png");
		billboard.Transform.Scale = { 70.0f,70.0f,1.0f };
		billboard.SetColor({ 1,1,1,0.02 });
	}
	else if(random == 1)
	{
		CBillboardComponent& billboard = *new CBillboardComponent(*this, Transform, "Assets/Textures/Trail/Fog02.png");
		billboard.Transform.Scale = { 70.0f,70.0f,1.0f };
		billboard.SetColor({ 1,1,1,0.02 });
	}
	/*else
	{
		CBillboardComponent& billboard = *new CBillboardComponent(*this, Transform, "Assets/Textures/Trail/Fog03.jpg");
		billboard.Transform.Scale = { 100.0f,100.0f,1.0f };
		billboard.SetColor({ 1,1,1,0.02 });
	}*/
}

void CFog::Tick()
{
	if (mLifeTime == 0)
	{
		Destroy();
	}
	mLifeTime--;
}
