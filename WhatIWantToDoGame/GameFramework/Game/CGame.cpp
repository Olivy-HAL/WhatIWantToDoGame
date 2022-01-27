#include <Windows.h>

#include "../ExternalTools/imgui/myimgui.h"
#include "../ExternalCode/CDirectxGraphics.h"
#include "../ExternalCode/DX11Settransform.h"
#include "../ExternalCode/CDirectInput.h"
#include "../Managers/CInputManager.h"
#include "../Managers/CSoundManager.h"
#include "../Actor/CFeedActor.h"

#include "CGame.h"
#include "CApplication.h"

CGame::CGame(CGameManager& partner):mApp(*this)
{}

CGame::~CGame()
{
	//ImGui�̏I������
	imguiExit();
}

long CGame::Execute(HINSTANCE hInst , int winMode)
{
	// �A�v���P�[�V������������
	mApp.Init(hInst);

	// �E�C���h�E��\������
	ShowWindow(mApp.GetHWnd() , winMode);
	UpdateWindow(mApp.GetHWnd());

	//�Q�[�����̏�����
	Init();

	// ���C�����[�v
	long ret = mApp.MainLoop();

	// �A�v���P�[�V�����I������
	mApp.Dispose();

	return ret;
}

void CGame::SetLevel(CLevel& level)
{
	mLevel.reset(&level);
}

void CGame::Init()
{
	// DX11�@������
	bool sts;

	//�T�E���h�}�l�[�W���[������
	CSoundManager::GetInstance();

	CDirectXGraphics* directGraph = CDirectXGraphics::GetInstance();

	//DirectX�O���t�B�b�N�X�̏�����
	sts = directGraph->Init(
		mApp.GetHWnd() ,
		CApplication::CLIENT_WIDTH ,
		CApplication::CLIENT_HEIGHT ,
		false);
	if(!sts)
	{
		MessageBox(mApp.GetHWnd() , "DX11 init error" , "error" , MB_OK);
		exit(1);
	}

	//DX11SetTransform�̏�����
	sts = DX11SetTransform::GetInstance()->Init();
	if(!sts)
	{
		MessageBox(NULL , "SetTransform error" , "Error" , MB_OK);
		exit(1);
	}

	//�������ݒ�
	directGraph->TurnOnAlphaBlending();

	//DIRECTINPUT������
	CDirectInput::GetInstance().Init
	(
		mApp.GetHInst() ,
		mApp.GetHWnd() ,
		CApplication::CLIENT_WIDTH ,
		CApplication::CLIENT_HEIGHT
	);

	//�R���X�^���g�o�b�t�@�쐬
	sts = CreateConstantBuffer(directGraph->GetDXDevice() , sizeof(SConstantBufferViewPort) , mConstantBufferViewPort.GetAddressOf());
	if(!sts)
	{
		MessageBox(NULL , "CreateBuffer(constant buffer Light) error" , "Error" , MB_OK);
	}

	ID3D11DeviceContext* devCon = directGraph->GetImmediateContext();
	SConstantBufferViewPort cb;

	cb.ScreenWidth = CApplication::CLIENT_WIDTH;
	cb.ScreenHeight = CApplication::CLIENT_HEIGHT;

	//�萔�o�b�t�@�̍X�V
	devCon->UpdateSubresource(mConstantBufferViewPort.Get() , 0 , nullptr , &cb , 0 , 0);

	//�萔�o�b�t�@�̃Z�b�g
	devCon->VSSetConstantBuffers(5 , 1 , mConstantBufferViewPort.GetAddressOf());
	devCon->PSSetConstantBuffers(5 , 1 , mConstantBufferViewPort.GetAddressOf());

	//ImGui�̏�����
	imguiInit();
}

void CGame::Input()
{
	//���̓`�F�b�N����
	CInputManager::GetInstance().CheckInput();
}

void CGame::Update()
{
	//���x�����ݒ肳��Ă���ꍇ
	if(mLevel != nullptr)
	{
		mLevel->Tick();			//���̃��x���I���W�i���ōs�������̎��s
		mLevel->Update();		//�S���x�����ʂ̍X�V���[�e�B�������s
	}
}

void CGame::Render()
{
	//���x�����ݒ肳��Ă���ꍇ
	if(mLevel != nullptr)
	{
		mLevel->Render();		//�`�揈���̎��s
	}

	//���[�h���x���֐����ݒ肳��Ă���Ȃ���s����ɂ���
	if(mLoadLevelFunction != nullptr)
	{
		mLoadLevelFunction();
		mLoadLevelFunction = nullptr;
	}
}

void CGame::LoadLevel(CLevel& level , bool isFeed , XMFLOAT3 feedColor , float feedTime)
{
	//�t�F�[�h���s�������x�����ݒ肳��Ă���ꍇ
	if(isFeed&&mLevel != nullptr)
	{
		//���[�h���x�����t�F�[�h�Ȃ��ōs���֐��I�u�W�F�N�g���쐬
		auto loadLevelCall = [&]
		{
			LoadLevel(level);
		};

		//�t�F�[�h�A�N�^�[�̍쐬
		new CFeedActor(*mLevel , loadLevelCall , CFeedActor::EOption::FEEDOUT , feedColor , feedTime);
	}
	else
	{
		//���x����؂�ւ�����������֐��I�u�W�F�N�g���쐬
		auto loadLevel = [&]
		{
			mLevel.reset(&level);
			mLevel->Init();
		};

		//���[�h���x���֐��I�u�W�F�N�g�ɃZ�b�g
		mLoadLevelFunction = loadLevel;
	}
}