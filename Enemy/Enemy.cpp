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

	// �Ԏ��ݒ�
	carModel_ = carModel;

	// �Ԏ킲�Ƃ̃X�s�[�h��ݒ�
	switch (carModel_)
	{
	case CarModel::truck:
		moveSpeed_ = { 0.6f,0.6f, 0.6f };
		break;
	case CarModel::prius:
		moveSpeed_ = { 1.0f,1.0f, 1.0f };
		break;
	case CarModel::ferrari:
		moveSpeed_ = { 1.6f,1.6f, 1.6f };
		break;
	default:
		break;
	}
}

void Enemy::Update()
{
	
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	if (isDead_ == false) {
		model_->Draw(worldTransform_, viewProjection, textureHandle_);
	}
}
