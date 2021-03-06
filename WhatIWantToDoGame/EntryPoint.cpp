//*****************************************************************************
//!	@file	WinMain.cpp
//!	@brief	
//!	@note	アプリケーション開始
//!	@author	
//*****************************************************************************

#pragma comment (lib,"d3d11.lib")					// リンク対象ライブラリ
#pragma comment (lib,"dxgi.lib")					// リンク対象ライブラリ
#pragma comment (lib,"D3DCompiler.lib")				// リンク対象ライブラリ
#pragma comment (lib,"winmm.lib")					// リンク対象ライブラリ
#pragma comment (lib,"dxguid.lib")					// リンク対象ライブラリ
#pragma comment (lib,"dinput8.lib")					// リンク対象ライブラリ

#pragma comment (lib,"assimp-vc141-mtd.lib")		// リンク対象ライブラリ

#ifdef _DEBUG
#pragma comment (lib,"_debug/directxtex.lib")		// リンク対象ライブラリ
#else
#pragma comment (lib,"_release/directxtex.lib")		// リンク対象ライブラリ
#endif

//-----------------------------------------------------------------------------
//	Include header files.
//-----------------------------------------------------------------------------
#include <Windows.h>
#include "GameFramework/Managers/CGameManager.h"

#include "CTitle.h"
#include "CTitleOp.h"
#include "CTrailLevel.h"

//==============================================================================
//!	@fn		WinMain
//!	@brief	エントリポイント
//!	@param	インスタンスハンドル
//!	@param	意味なし
//!	@param	起動時の引数文字列
//!	@param	ウインドウ表示モード
//!	@retval	TRUE　成功終了/FALSE　失敗終了
//!	@note	
//==============================================================================
INT APIENTRY WinMain(HINSTANCE  h_hInst ,
	HINSTANCE  h_hPrevInst ,
	LPSTR		h_lpszArgs ,
	int		h_nWinMode)
{
	//ゲームマネージャー取得
	CGameManager& gameManager = CGameManager::GetInstance();

	/*
	★超重要★
	ここに開始したいレベルのコンストラクタを
	引数をIGame&で呼び出す
	メモリ解放はゲームマネージャーが行うので考えなくてよい
	*/
	//new CTitle(gameManager.GetGameInterface());
	//new CTitleOp(gameManager.GetGameInterface());
	new CTrailLevel(gameManager.GetGameInterface());

	//ゲームの実行をリクエスト
	gameManager.RequestExecute(h_hInst , h_nWinMode);
}

//******************************************************************************
//	End of file.
//******************************************************************************


