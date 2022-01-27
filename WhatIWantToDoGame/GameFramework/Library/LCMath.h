#pragma once
#include <vector>
#include <DirectXMath.h>

using namespace DirectX;

static class LCMath
{
public:
	//�I�C���[�p����N�H�[�^�j�I���ɕϊ�
	static const XMFLOAT4& TransformFromEulerAnglesToQuaternion(const XMFLOAT3& axisX, const XMFLOAT3& axisY, const XMFLOAT3& axisZ,
		const XMFLOAT3& eulerAngle, XMFLOAT4& resultQua);
	static XMFLOAT4 TransformFromEulerAnglesToQuaternion(const XMFLOAT3& axisX, const XMFLOAT3& axisY, const XMFLOAT3& axisZ,
		const XMFLOAT3& eulerAngle);

	//�N�H�[�^�j�I������I�C���[�p�ɕϊ�
	static const XMFLOAT3& TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua, XMFLOAT3& resultAngle);
	static XMFLOAT3 TransformFromQuaternionToEulerAngles(const XMFLOAT4& qua);	
	
	//�s�񂩂�I�C���[�p�ɕϊ�
	static const XMFLOAT3& TransformFromMatrixToEulerAngles(const XMFLOAT4X4& matrix, XMFLOAT3& resultAngle);
	static XMFLOAT3 TransformFromMatrixToEulerAngles(const XMFLOAT4X4& matrix);

	//�P�ʍs��
	static void IdentityMatrix(XMFLOAT4X4& target);

	//�P�ʃN�I�[�^�j�I����
	static void IdentityQuaternion(XMFLOAT4& target);

	//���P�[�V�����A�X�P�[���A��]�s�񂩂�w��̍s����X�V
	static const XMFLOAT4X4& UpdateMatrix(const XMFLOAT3& location, const XMFLOAT3& scale, const XMFLOAT4X4& rotMTX, XMFLOAT4X4& resultMTX);
	static XMFLOAT4X4 UpdateMatrix(const XMFLOAT3& location, const XMFLOAT3& scale, const XMFLOAT4X4& rotMTX);

	//�t�s����擾
	static const XMFLOAT4X4& InverseMatrix(const XMFLOAT4X4& target, XMFLOAT4X4& resultMTX);
	static XMFLOAT4X4 InverseMatrix(const XMFLOAT4X4& target);
	
	//�]�u�s����擾
	static const XMFLOAT4X4& TransposeMatrix(const XMFLOAT4X4& target, XMFLOAT4X4& resultMTX);
	static XMFLOAT4X4 TransposeMatrix(const XMFLOAT4X4& target);

	//�w���Float3���m����v���Ă��邩�̔�r
	static bool CompareFloat3(const XMFLOAT3& target1, const XMFLOAT3& target2);
	
	//�w���Float4���m����v���Ă��邩�̔�r
	static bool CompareFloat4(const XMFLOAT4& target1, const XMFLOAT4& target2);

	//�w��̍s�񓯎m����v���Ă��邩�̔�r
	static bool CompareMatrix(const XMFLOAT4X4& target1, const XMFLOAT4X4& target2);

	//���i�����x�N�g���j�Ɗp�x(���W�A��)����N�H�[�^�j�I�����쐬	
	static const XMFLOAT4& CreateFromAxisAndAngleToQuaternion(const XMFLOAT3& axis, const float& angleOfRadian, XMFLOAT4& resultQua);
	static XMFLOAT4 CreateFromAxisAndAngleToQuaternion(const XMFLOAT3& axis, const float& angleOfRadian);

	//�N�H�[�^�j�I�����m�̏�Z
	static const XMFLOAT4& CalcQuaternionMultiply(const XMFLOAT4& qua1, const XMFLOAT4& qua2, XMFLOAT4& resultQua);
	static XMFLOAT4 CalcQuaternionMultiply(const XMFLOAT4& qua1, const XMFLOAT4& qua2);

	//�N�I�[�^�j�I������s����Z�o
	static const XMFLOAT4X4& CalcMatrixFromQuaternion(const XMFLOAT4& target ,XMFLOAT4X4& resultMTX);
	static XMFLOAT4X4 CalcMatrixFromQuaternion(const XMFLOAT4& target);

	//�s�񓯎m�̏�Z
	static const XMFLOAT4X4& CalcMatrixMultply(const XMFLOAT4X4& target1 , const XMFLOAT4X4& target2 , XMFLOAT4X4& resultMTX);
	static XMFLOAT4X4 CalcMatrixMultply(const XMFLOAT4X4& target1 , const XMFLOAT4X4& target2);

	//�X�^�[�g����S�[���ւ̃x�N�g�����Q�b�g
	static const XMFLOAT3& CalcFloat3FromStartToGoal(const XMFLOAT3& start, const XMFLOAT3& goal, XMFLOAT3& resultVec);
	static XMFLOAT3 CalcFloat3FromStartToGoal(const XMFLOAT3& start, const XMFLOAT3& goal);

	//���Z
	static const XMFLOAT3& CalcFloat3Addition(const XMFLOAT3& target, const XMFLOAT3& vector, XMFLOAT3& resultVec);
	static XMFLOAT3 CalcFloat3Addition(const XMFLOAT3& target, const XMFLOAT3& vector);

	//�������擾
	static const float& CalcFloat3Length(const XMFLOAT3& target, float& resultLen);
	static float CalcFloat3Length(const XMFLOAT3& target);

	//���K��
	static const XMFLOAT3& CalcFloat3Normalize(const XMFLOAT3& target, XMFLOAT3& resultVec);
	static XMFLOAT3 CalcFloat3Normalize(const XMFLOAT3& target);

	//����
	static const float& CalcFloat3Dot(const XMFLOAT3& target1, const XMFLOAT3& target2, float& resultScaler);
	static float CalcFloat3Dot(const XMFLOAT3& target1, const XMFLOAT3& target2);

	//�O��
	static const XMFLOAT3& CalcFloat3Cross(const XMFLOAT3& target1, const XMFLOAT3& target2, XMFLOAT3& resultVec);
	static XMFLOAT3 CalcFloat3Cross(const XMFLOAT3& target1, const XMFLOAT3& target2);

	//�X�J���[��
	static const XMFLOAT3& CalcFloat3Scalar(const XMFLOAT3& target, const float& scalar, XMFLOAT3& resultVec);
	static XMFLOAT3 CalcFloat3Scalar(const XMFLOAT3& target, const float& scalar);

	//3�����x�N�g�����s��Ə�Z
	static const XMFLOAT3& CalcFloat3MultplyMatrix(const XMFLOAT3& target,const XMFLOAT4X4& mtx, XMFLOAT3& result);
	static XMFLOAT3 CalcFloat3MultplyMatrix(const XMFLOAT3& target, const XMFLOAT4X4& mtx);

	//���_�z�񂩂�Min Max�����߂�
	static const void CalcFloat3MinMax(const std::vector<XMFLOAT3>& vertices, XMFLOAT3& resultMin,XMFLOAT3& resultMax);

	//���`���
	static const float& Lerp(const float& start, const float& end, const float& alpha, float& result);
	static float Lerp(const float& start, const float& end, const float& alpha);
	static const XMFLOAT3& Lerp(const XMFLOAT3& start, const XMFLOAT3& end, const float& alpha, XMFLOAT3& result);
	static XMFLOAT3 Lerp(const XMFLOAT3& start, const XMFLOAT3& end, const float& alpha);
	static const XMFLOAT4& Lerp(const XMFLOAT4& start, const XMFLOAT4& end, const float& alpha, XMFLOAT4& result);
	static XMFLOAT4 Lerp(const XMFLOAT4& start, const XMFLOAT4& end, const float& alpha);
	static const XMFLOAT4X4& Lerp(const XMFLOAT4X4& start, const XMFLOAT4X4& end, const float& alpha, XMFLOAT4X4& result);
	static XMFLOAT4X4 Lerp(const XMFLOAT4X4& start, const XMFLOAT4X4& end, const float& alpha);
};