#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <cassert>
#include "DebugText.h"
#include "Input.h"
#include "ViewProjection.h"
#include <memory>
#include <list>

class collision {
public:
private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	DebugText* debugText_ = nullptr;
	//���f��
	Model* model_ = nullptr;
	//���f��
	Model* enemyBulletModel_ = nullptr;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;
};