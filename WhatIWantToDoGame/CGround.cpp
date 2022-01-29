#include "CGround.h"
#include "GameFramework/Components/CStaticMeshComponent.h"
#include "GameFramework/Managers/CModelDataManager.h"

CGround::CGround(ILevel& owner) :CActor(owner)
{
	XMFLOAT2 max, min, length;
	min = max = { 0,0 };

	CModelData& model = CModelDataManager::GetInstance().GetModel("Assets/Models/City/City.fbx", "Assets/Models/City/Textures/");

	for (auto& mesh : model.GetMeshes())
	{
		for (auto& vertex : mesh.Vertices)
		{
			if (min.x > vertex.Pos.x)min.x = vertex.Pos.x;
			else if (max.x < vertex.Pos.x)max.x = vertex.Pos.x;

			if (min.y > vertex.Pos.z)min.y = vertex.Pos.z;
			else if (max.y < vertex.Pos.z)max.y = vertex.Pos.z;
		}
	}

	length.x = max.x + std::fabsf(min.x);
	length.y = max.y + std::fabsf(min.y);

	for (int z = -2; z <= 2; z++)
	{
		for (int x = -4; x <= 4; x++)
		{
			CStaticMeshComponent& ground = *new CStaticMeshComponent(*this, Transform, model, "Shader/vs.hlsl", "Shader/ps.hlsl");
			ground.Transform.Location.x += x * length.x;
			ground.Transform.Location.z += z * length.y;
		}
	}
}
