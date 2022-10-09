#include "Load.h"
#include <cassert>
#include "Affin.h"

void Load::Initialize(Model* model) {
	//NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

	//�������W���Z�b�g
	for (int i = 0; i < 7; i++) {
		float z = i * 39;
		worldTransform_[i].translation_ = Vector3{ 0,-6,z };

		//���[���h�ϊ��̏�����
		worldTransform_[i].Initialize();

		worldTransform_[i].scale_ = Vector3{ 10,10,10 };
	}

	speed = 3;
}

void Load::Update() {
	for (int i = 0; i < 7; i++) {
		worldTransform_[i].translation_.z -= speed;

		if (worldTransform_[i].translation_.z < -90) {
			worldTransform_[i].translation_.z = 180;
		}

		//�s��X�V
		AffinTrans::affin(worldTransform_[i]);
		worldTransform_[i].TransferMatrix();
	}
}

void Load::Draw(ViewProjection viewProjection) {
	//3D���f����`��
	for (int i = 0; i < 7; i++) {
		model_->Draw(worldTransform_[i], viewProjection);
	}
}