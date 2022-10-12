#include "wing.h"
#include <cassert>
#include "Affin.h"

void Wing::Initialize(Model* model) {
	//NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

	//�������W���Z�b�g
	worldTransform_.translation_ = Vector3{ 0,0,0 };

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();

	worldTransform_.scale_ = Vector3{ 10,10,10 };
}

void Wing::Update(Vector3 pos) {
	//�v���C���[�̍��W�����킹��
	worldTransform_.translation_ = pos;

	//�s��X�V
	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();

}

void Wing::Draw(ViewProjection viewProjection) {
	//3D���f����`��
	model_->Draw(worldTransform_, viewProjection);
}