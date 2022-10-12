#include "wing.h"
#include <cassert>
#include "Affin.h"

void Wing::Initialize(Model* model) {
	//NULL�|�C���^�`�F�b�N
	assert(model);

	//�����Ƃ��Ď󂯎�����f�[�^�������o�ϐ��ɋL�^����
	model_ = model;

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	worldTransform_.scale_ = { 6,6,6 };

	//�t���O������
	make = false;

	//���ԏ�����
	drawTime = 0;

	//�f�o�b�N�e�L�X�g������
	debugText_ = DebugText::GetInstance();
}

void Wing::Update(Vector3 player) {
	worldTransform_.translation_ = player;

	//�\�����ԃJ�E���g
	if (drawTime > 0) {
		drawTime--;
	}
	else {
		make = false;
		drawTime = 0;
	}

	debugText_->SetPos(50, 100);
	debugText_->Printf("drawTime : %d", drawTime);

	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Wing::Draw(ViewProjection viewProjection) {
	//3D���f����`��
	if (make == true) {
		model_->Draw(worldTransform_, viewProjection);
	}
}

void Wing::Distance() {
	make = true;
	drawTime = 1;
}