#include "Load.h"
#include <cassert>
#include "MatSet.h"

void Load::Initialize(Model* model) {
	//NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

	//�������W���Z�b�g
	for (int i = 0; i < 12; i++) {
		float z = i * 39;
		worldTransform_[i].translation_ = Vector3{0,-50,z + 390};

		//���[���h�ϊ��̏�����
		worldTransform_[i].Initialize();

		worldTransform_[i].scale_ = Vector3{10,10,10};
	}

	speed = 3;
}

void Load::Update() {
	//�X�V�p�̕ϐ�
	MatSet2 matSet;

	for (int i = 0; i < 12; i++) {
		worldTransform_[i].translation_.z -= speed;

		if (worldTransform_[i].translation_.z < -90) {
			worldTransform_[i].translation_.z = 370;
		}

		//���[���h�g�����X�t�H�[���̍X�V
		matSet.MatIdentity(worldTransform_[i]);
		worldTransform_[i].TransferMatrix();
	}
}

void Load::Draw(ViewProjection viewProjection) {
	//3D���f����`��
	for (int i = 0; i < 12; i++) {
		model_->Draw(worldTransform_[i], viewProjection);
	}
}