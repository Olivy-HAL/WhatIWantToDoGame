#pragma once
#include <vector>
#include <DirectXMath.h>

using namespace DirectX;

static class LCMath
{
public:
	//オイラー角からクォータニオンに変換
	static const XMFLOAT4& TransformFromEulerAnglesToQuaternion(const XMFLOAT3& axisX, const XMFLOAT3& axisY, const XMFLOAT3& axisZ,
		const XMFLOAT3& eulerAngle, XMFLOAT4& resultQua);
	static XMFLOAT4 TransformFromEulerAnglesToQuaternion(const XMFLOAT3& axisX, const XMFLOAT3& axisY, const XMFLOAT3& axisZ,
		const XMFLOAT3& eulerAngle);

	//クォータニオンからオイラー角に変換
	static const XMFLOAT3& TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua, XMFLOAT3& resultAngle);
	static XMFLOAT3 TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua);	
	
	//行列からオイラー角に変換
	static const XMFLOAT3& TransformFromMatrixToEulerAngles(const XMFLOAT4X4& matrix, XMFLOAT3& resultAngle);
	static XMFLOAT3 TransformFromMatrixToEulerAngles(const XMFLOAT4X4& matrix);

	//単位行列化
	static void IdentityMatrix(XMFLOAT4X4& target);

	//単位クオータニオン化
	static void IdentityQuaternion(XMFLOAT4& target);

	//ロケーション、スケール、回転行列から指定の行列を更新
	static const XMFLOAT4X4& UpdateMatrix(const XMFLOAT3& location, const XMFLOAT3& scale, const XMFLOAT4X4& rotMTX, XMFLOAT4X4& resultMTX);
	static XMFLOAT4X4 UpdateMatrix(const XMFLOAT3& location, const XMFLOAT3& scale, const XMFLOAT4X4& rotMTX);

	//逆行列を取得
	static const XMFLOAT4X4& InverseMatrix(const XMFLOAT4X4& target, XMFLOAT4X4& resultMTX);
	static XMFLOAT4X4 InverseMatrix(const XMFLOAT4X4& target);
	
	//転置行列を取得
	static const XMFLOAT4X4& TransposeMatrix(const XMFLOAT4X4& target, XMFLOAT4X4& resultMTX);
	static XMFLOAT4X4 TransposeMatrix(const XMFLOAT4X4& target);

	//指定のFloat3同士が一致しているかの比較
	static bool CompareFloat3(const XMFLOAT3& target1, const XMFLOAT3& target2);
	
	//指定のFloat4同士が一致しているかの比較
	static bool CompareFloat4(const XMFLOAT4& target1, const XMFLOAT4& target2);

	//指定の行列同士が一致しているかの比較
	static bool CompareMatrix(const XMFLOAT4X4& target1, const XMFLOAT4X4& target2);

	//軸（向きベクトル）と角度(ラジアン)からクォータニオンを作成	
	static const XMFLOAT4& CreateFromAxisAndAngleToQuaternion(const XMFLOAT3& axis, const float& angleOfRadian, XMFLOAT4& resultQua);
	static XMFLOAT4 CreateFromAxisAndAngleToQuaternion(const XMFLOAT3& axis, const float& angleOfRadian);

	//クォータニオン同士の乗算
	static const XMFLOAT4& CalcQuaternionMultiply(const XMFLOAT4& qua1, const XMFLOAT4& qua2, XMFLOAT4& resultQua);
	static XMFLOAT4 CalcQuaternionMultiply(const XMFLOAT4& qua1, const XMFLOAT4& qua2);

	//クオータニオンから行列を算出
	static const XMFLOAT4X4& CalcMatrixFromQuaternion(const XMFLOAT4& target ,XMFLOAT4X4& resultMTX);
	static XMFLOAT4X4 CalcMatrixFromQuaternion(const XMFLOAT4& target);

	//行列同士の乗算
	static const XMFLOAT4X4& CalcMatrixMultply(const XMFLOAT4X4& target1 , const XMFLOAT4X4& target2 , XMFLOAT4X4& resultMTX);
	static XMFLOAT4X4 CalcMatrixMultply(const XMFLOAT4X4& target1 , const XMFLOAT4X4& target2);

	//スタートからゴールへのベクトルをゲット
	static const XMFLOAT3& CalcFloat3FromStartToGoal(const XMFLOAT3& start, const XMFLOAT3& goal, XMFLOAT3& resultVec);
	static XMFLOAT3 CalcFloat3FromStartToGoal(const XMFLOAT3& start, const XMFLOAT3& goal);

	//加算
	static const XMFLOAT3& CalcFloat3Addition(const XMFLOAT3& target, const XMFLOAT3& vector, XMFLOAT3& resultVec);
	static XMFLOAT3 CalcFloat3Addition(const XMFLOAT3& target, const XMFLOAT3& vector);

	//長さを取得
	static const float& CalcFloat3Length(const XMFLOAT3& target, float& resultLen);
	static float CalcFloat3Length(const XMFLOAT3& target);

	//正規化
	static const XMFLOAT3& CalcFloat3Normalize(const XMFLOAT3& target, XMFLOAT3& resultVec);
	static XMFLOAT3 CalcFloat3Normalize(const XMFLOAT3& target);

	//内積
	static const float& CalcFloat3Dot(const XMFLOAT3& target1, const XMFLOAT3& target2, float& resultScaler);
	static float CalcFloat3Dot(const XMFLOAT3& target1, const XMFLOAT3& target2);

	//外積
	static const XMFLOAT3& CalcFloat3Cross(const XMFLOAT3& target1, const XMFLOAT3& target2, XMFLOAT3& resultVec);
	static XMFLOAT3 CalcFloat3Cross(const XMFLOAT3& target1, const XMFLOAT3& target2);

	//スカラー積
	static const XMFLOAT3& CalcFloat3Scalar(const XMFLOAT3& target, const float& scalar, XMFLOAT3& resultVec);
	static XMFLOAT3 CalcFloat3Scalar(const XMFLOAT3& target, const float& scalar);

	//3次元ベクトルを行列と乗算
	static const XMFLOAT3& CalcFloat3MultplyMatrix(const XMFLOAT3& target,const XMFLOAT4X4& mtx, XMFLOAT3& result);
	static XMFLOAT3 CalcFloat3MultplyMatrix(const XMFLOAT3& target, const XMFLOAT4X4& mtx);

	//頂点配列からMin Maxを求める
	static const void CalcFloat3MinMax(const std::vector<XMFLOAT3>& vertices, XMFLOAT3& resultMin,XMFLOAT3& resultMax);

	//線形補間
	static const float& Lerp(const float& start, const float& end, const float& alpha, float& result);
	static float Lerp(const float& start, const float& end, const float& alpha);
	static const XMFLOAT3& Lerp(const XMFLOAT3& start, const XMFLOAT3& end, const float& alpha, XMFLOAT3& result);
	static XMFLOAT3 Lerp(const XMFLOAT3& start, const XMFLOAT3& end, const float& alpha);
	static const XMFLOAT4& Lerp(const XMFLOAT4& start, const XMFLOAT4& end, const float& alpha, XMFLOAT4& result);
	static XMFLOAT4 Lerp(const XMFLOAT4& start, const XMFLOAT4& end, const float& alpha);
	static const XMFLOAT4X4& Lerp(const XMFLOAT4X4& start, const XMFLOAT4X4& end, const float& alpha, XMFLOAT4X4& result);
	static XMFLOAT4X4 Lerp(const XMFLOAT4X4& start, const XMFLOAT4X4& end, const float& alpha);
};