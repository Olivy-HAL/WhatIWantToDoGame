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

//トランスフォームクラス
class CTransform
{
public:
	enum class EAttachOption
	{
		DEFAULT = 0b00 ,
		LOCATION_ONLY = 0b01 ,
	};

private:
	XMFLOAT4X4 mWorldMatrixSelf;			//自身のワールド行列
	XMFLOAT4X4 mWorldMatrixResult;			//最終的な結果のワールド行列

	CTransform* mParentTransform = nullptr;				//親トランスフォーム
	std::vector<CTransform*> mChildTransform;			//子トランスフォーム

	XMFLOAT3 mLastFrameLocation = { 0.f,0.f,0.f };		//前フレームのロケーション
	XMFLOAT3 mLastFrameScale = { 0.f,0.f,0.f };			//前フレームのスケール

	IActor& mOwnerInterface;

	EAttachOption mAttachOption = EAttachOption::DEFAULT;

	std::vector<std::function<void()>> mMatrixUpdateTimeFunction;		//マトリックス更新時実行関数

	bool mShouldUpdateMatrix = true;			//行列を更新すべきか
	bool mIgnoreUpdateMatrixOnce = false;		//一度行列の更新を無視するか
	bool mIsChild = false;						//自分が子トランスフォームか
	bool mIsBillboard = false;					//ビルボードかどうか
	bool mDoDrawDebugLine = false;				//デバッグラインを描画するか

	void SetWorldMatrixSelf(const XMFLOAT4X4& matrix);
	
public:
	XMFLOAT3 Location = { 0.f,0.f,0.f };		//ロケーション
	XMFLOAT3 Scale = { 1.f,1.f,1.f };			//スケール

	CRotator Rotation;			//ローテーション

	//アクターを作るとき限定のコンストラクタ
	CTransform(IActor& partner);

	//作るときから従属するトランスフォームが決まっている時のコンストラクタ
	CTransform(IActor& partner , CTransform& parentTrans);

	~CTransform();

	//更新
	void Update();

	//行列をDirectxにセットしてもらうリクエスト
	void RequestSetMatrix();

	//引数のトランスフォームをアタッチ（子として親子付け）する
	void AttachTransform(CTransform& attachTarget);

	//引数のトランスフォームをデタッチ（親子付け解除）する
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