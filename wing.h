#pragma once

#include"Model.h"
#include"WorldTransform.h"
#include"DebugText.h"

class Wing {
public:
	//������
	void Initialize(Model* model);

	//�X�V
	void Update(Vector3 player);

	//�`��
	void Draw(ViewProjection viewProjection);

	//����
	void Distance();
private:
	//���[���h���W
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�f�o�b�O�e�L�X�g
	DebugText* debugText_ = nullptr;
	//�\���t���O
	bool make;
	//�`�掞��
	int drawTime;
};
