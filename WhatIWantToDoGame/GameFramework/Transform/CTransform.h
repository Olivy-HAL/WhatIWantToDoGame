#pragma once
#include <vector>
#include <memory>
#include <array>
#include <functional>
#include <DirectXMath.h>

#include "CRotator.h"

using namespace DirectX;

class CChildTransform;
class IActor;

//�g�����X�t�H�[���N���X
class CTransform
{
public:
	enum class EAttachOption
	{
		DEFAULT = 0b00 ,
		LOCATION_ONLY = 0b01 ,
	};

private:
	XMFLOAT4X4 mWorldMatrixSelf;			//���g�̃��[���h�s��
	XMFLOAT4X4 mWorldMatrixResult;			//�ŏI�I�Ȍ��ʂ̃��[���h�s��

	CTransform* mParentTransform = nullptr;				//�e�g�����X�t�H�[��
	std::vector<CTransform*> mChildTransform;			//�q�g�����X�t�H�[��

	XMFLOAT3 mLastFrameLocation = { 0.f,0.f,0.f };		//�O�t���[���̃��P�[�V����
	XMFLOAT3 mLastFrameScale = { 0.f,0.f,0.f };			//�O�t���[���̃X�P�[��

	IActor& mOwnerInterface;

	EAttachOption mAttachOption = EAttachOption::DEFAULT;

	std::vector<std::function<void()>> mMatrixUpdateTimeFunction;		//�}�g���b�N�X�X�V�����s�֐�

	bool mShouldUpdateMatrix = true;			//�s����X�V���ׂ���
	bool mIgnoreUpdateMatrixOnce = false;		//��x�s��̍X�V�𖳎����邩
	bool mIsChild = false;						//�������q�g�����X�t�H�[����
	bool mIsBillboard = false;					//�r���{�[�h���ǂ���
	bool mDoDrawDebugLine = false;				//�f�o�b�O���C����`�悷�邩

	void SetWorldMatrixSelf(const XMFLOAT4X4& matrix);
	
public:
	XMFLOAT3 Location = { 0.f,0.f,0.f };		//���P�[�V����
	XMFLOAT3 Scale = { 1.f,1.f,1.f };			//�X�P�[��

	CRotator Rotation;			//���[�e�[�V����

	//�A�N�^�[�����Ƃ�����̃R���X�g���N�^
	CTransform(IActor& partner);

	//���Ƃ�����]������g�����X�t�H�[�������܂��Ă��鎞�̃R���X�g���N�^
	CTransform(IActor& partner , CTransform& parentTrans);

	~CTransform();

	//�X�V
	void Update();

	//�s���Directx�ɃZ�b�g���Ă��炤���N�G�X�g
	void RequestSetMatrix();

	//�����̃g�����X�t�H�[�����A�^�b�`�i�q�Ƃ��Đe�q�t���j����
	void AttachTransform(CTransform& attachTarget);

	//�����̃g�����X�t�H�[�����f�^�b�`�i�e�q�t�������j����
	void DetachTransform(CTransform& detachTarget);

	void RequestDebugLine();

	const XMFLOAT4X4& GetWorldMatrixSelf()const
	{
		return mWorldMatrixSelf;
	}

	const XMFLOAT4X4& GetWorldMatrixResult()const
	{
		return mWorldMatrixResult;
	}

	const bool& GetIsChild()const
	{
		return mIsChild;
	}

	XMFLOAT3 GetRightVectorWorld()const;

	XMFLOAT3 GetUpwardVectorWorld()const;

	XMFLOAT3 GetForwardVectorWorld()const;
	
	XMFLOAT3 GetRightVectorRelative()const;

	XMFLOAT3 GetUpwardVectorRelative()const;

	XMFLOAT3 GetForwardVectorRelative()const;

	XMFLOAT3 GetWorldLocation()const;

	XMFLOAT3 GetWorldScale()const;

	//XMFLOAT3 GetWorldRotatorAngle()const;

	void SetIsBillboard(bool flg)
	{
		mIsBillboard = flg;
	}

	void AddMatrixUpdateTimeFunction(const std::function<void()>& func)
	{
		mMatrixUpdateTimeFunction.emplace_back(func);
	};

	void SetOption(EAttachOption option)
	{
		mAttachOption = option;
	}

};