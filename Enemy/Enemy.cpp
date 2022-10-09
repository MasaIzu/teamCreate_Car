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
		moveSpeed_ = { 0.0f,0.0f, 0.1f };
		break;
	case CarModel::prius:
		moveSpeed_ = { 0.0f,0.0f, 0.2f };
		break;
	case CarModel::ferrari:
		moveSpeed_ = { 0.0f,0.0f, 0.25f };
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
	worldTransform_.translation_ += moveSpeed_;

	// �s����v�Z���]��
	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();

	// �����Ă��鎞�Ԃ����E�ɒB���������
	if (lifeTimer >= lifeInterval) {
		isDead_ = true;
	}
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	//if (isDead_ == false) {
		model_->Draw(worldTransform_, viewProjection);
	//}
}
