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
	initPos = worldTransform_.translation_;
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

	// ���Ԑ��Ɉړ��\��������A�ꃌ�[���ړ�������
	if (leftLaneChangeFlag_ == true) {
		if (worldTransform_.translation_.x > initPos.x - (1 * loadWidth)) {
			worldTransform_.translation_.x -= 0.5f;
		}
		if (worldTransform_.translation_.x <= initPos.x - (1 * loadWidth)) {
			leftLaneChangeFlag_ = false;
		}
	}

	// �E�Ԑ��Ɉړ��\��������A�ꃌ�[���ړ�������
	if (rightLaneChangeFlag_ == true) {
		if (worldTransform_.translation_.x < initPos.x + (1 * loadWidth)) {
			worldTransform_.translation_.x += 0.5f;
		}
		if (worldTransform_.translation_.x >= initPos.x + (1 * loadWidth)) {
			rightLaneChangeFlag_ = false;
		}
	}

	// �s����v�Z���]��
	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();

	// �����Ă��鎞�Ԃ����E�ɒB���������
	if (lifeTimer >= lifeInterval) {
		isDead_ = true;
	}
}

void Enemy::Lane1ChangeCheck(Vector3& pos)
{
	Vector3 pos_ = worldTransform_.translation_;

	// ��ԍ����̃��[���ɂ����ꍇ�̎Ԑ��ύX
	if (pos_.x == pos.x) {
		if (pos_.x <= -2 * loadWidth) {
			if (pos_.z <= pos.z + laneRadius && pos_.z > pos.z) {
				lane1ChangeFlag_ = true;
			}
		}
	}
}

void Enemy::Lane5ChangeCheck(Vector3& pos)
{
	Vector3 pos_ = worldTransform_.translation_;

	// ��ԉE���̃��[���ɂ����ꍇ�̎Ԑ��ύX
	if (pos_.x == pos.x) {
		if (pos_.x >= 2 * loadWidth) {
			if (pos_.z <= pos.z + laneRadius && pos_.z > pos.z) {
				lane5ChangeFlag_ = true;
			}
		}
	}
}

void Enemy::LaneChangeCheck(Vector3& pos)
{
	Vector3 pos_ = worldTransform_.translation_;

	if (pos_.x == pos.x) {
		if (pos.z <= pos_.z + laneRadius && pos.z > pos_.z) {
			laneChangeFlag_ = true;
		}
	}
	
}

void Enemy::LeftLaneChangeCheck(Vector3& pos)
{
	Vector3 leftpos = { worldTransform_.translation_.x - (1 * loadWidth),worldTransform_.translation_.y,worldTransform_.translation_.z };
	if (leftpos.z += laneRadius <= pos.z) {
		leftLaneChangeFlag_ = true;
	}
}

void Enemy::RightLaneChangeCheck(Vector3& pos)
{
	Vector3 rightpos = { worldTransform_.translation_.x + (1 * loadWidth),worldTransform_.translation_.y,worldTransform_.translation_.z };
	if (rightpos.z += laneRadius <= pos.z) {
		rightLaneChangeFlag_ = true;
	}
}

void Enemy::SetWouldTransform(WorldTransform worldTransform)
{
	worldTransform_ = worldTransform;
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	//if (isDead_ == false) {
		model_->Draw(worldTransform_, viewProjection);
	//}
}
