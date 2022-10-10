#include "Enemy.h"

void Enemy::Initialize(Model* model ,Vector3& pos, CarModel carModel)
{
	// NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;

	// ���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();

	// �������W��ݒ�
	worldTransform_.translation_ = pos;
	worldTransform_.scale_ = { 5,5,5 };

	// �Ԏ��ݒ�
	carModel_ = carModel;

	// �Ԏ킲�Ƃ̃X�s�[�h��ݒ�
	switch (carModel_)
	{
	case CarModel::truck:
		moveSpeed_ = { 0.0f,0.0f, 3.0f };
		break;
	case CarModel::prius:
		moveSpeed_ = { 0.0f,0.0f, 2.0f };
		break;
	case CarModel::ferrari:
		moveSpeed_ = { 0.0f,0.0f, 1.5f };
		break;
	default:
		break;
	}
}

void Enemy::Update()
{
	// �����Ă��鎞�Ԃ����Z
	lifeTimer++;

	//�O�ɐi�ޏ���
	worldTransform_.translation_ -= moveSpeed_;

	// �s����v�Z���]��
	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();

	// �����Ă��鎞�Ԃ����E�ɒB���������
	if (lifeTimer >= lifeInterval) {
		isDead_ = true;
	}
}

void Enemy::LaneChangeCheck(Vector3& pos)
{
	// ��ԉE���̃��[���ɂ����ꍇ�̎Ԑ��ύX
	if (worldTransform_.translation_.x >= 2 * loadWidth) {
		if (worldTransform_.translation_.z += laneRadius <= pos.z) {
			//float leftpos = worldTransform_.translation_.x + (1 * loadWidth);
			laneChangeFlag = true;
		}
	}
}

void Enemy::LeftLaneChangeCheck(Vector3& pos)
{
	Vector3 leftpos = { worldTransform_.translation_.x - (1 * loadWidth),worldTransform_.translation_.y,worldTransform_.translation_.z };
	if (leftpos.z += laneRadius <= pos.z) {
		leftLaneChangeFlag = true;
	}
}

void Enemy::RightLaneChangeCheck(Vector3& pos)
{
	Vector3 rightpos = { worldTransform_.translation_.x + (1 * loadWidth),worldTransform_.translation_.y,worldTransform_.translation_.z };
	if (rightpos.z += laneRadius <= pos.z) {
		rightLaneChangeFlag = true;
	}
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	//if (isDead_ == false) {
		model_->Draw(worldTransform_, viewProjection);
	//}
}
