#include "../ExternalLibrary/Assimp/assimp/include/assimp/postprocess.h"
#include "../ExternalLibrary/Assimp/assimp/include/assimp/cimport.h"
#include "../ExternalLibrary/Assimp/assimp/include/assimp/scene.h"

#include "AssimpScene.h"

bool AssimpScene::Init(std::string filename) {

	m_Scene = aiImportFile(filename.c_str(),
		aiProcess_ConvertToLeftHanded |
		aiProcessPreset_TargetRealtime_MaxQuality);

	if (m_Scene == nullptr) {
		return false;
	}

	return true;
}

// �I������
void AssimpScene::Exit() {
	aiReleaseImport(m_Scene);
}

// �V�[���擾
const aiScene* AssimpScene::GetScene() const {
	return m_Scene;
}

// �A�j���[�V�����������Ă��邩
bool AssimpScene::HasAnimation() {
	return m_Scene->HasAnimations();
}