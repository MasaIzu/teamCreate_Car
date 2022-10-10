#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Affin.h"
#include <cassert>

enum class CarModel {
	truck,// �g���b�N�i�x���ԁj
	prius,// �v���E�X�i��ʎԁj
	ferrari,// �t�F���[���i�����ԁj
};

class Enemy
{
public:// �����o�֐�

	// �����������֐�
	void Initialize(Model* model ,Vector3& pos, CarModel carModel);

	// �X�V�����֐�
	void Update();

	// �Ԑ��ύX�����֐�
	void LaneChangeCheck(Vector3& pos);

	void LeftLaneChangeCheck(Vector3& pos);

	void RightLaneChangeCheck(Vector3& pos);

	// �|�W�V�����̃Q�b�^�[
	Vector3 GetPos() { return worldTransform_.translation_; }

	// �Z�b�^�[
	void SetWouldTransform(WorldTransform worldTransform);

	// �`�揈���֐�
	void Draw(const ViewProjection& viewProjection);

	// ���S�t���O��n��
	bool IsDead() const { return isDead_; }

private:// �����o�ϐ�

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;

	//���f��
	Model* model_ = nullptr;

	// ���x�S��
	// �i�ޑ��x
	Vector3 moveSpeed_ = { 0.0f,0.0f,1.0f };
	// ��]���x
	Vector3 rotationSpeed_ = { 0.1f,0.1f, 0.1f };

	// �f�X�t���O
	bool isDead_ = false;

	// �Ԃ̃p�^�[��
	CarModel carModel_ = CarModel::prius;

	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	// �����Ă��鎞��
	int lifeTimer = 0;
	int lifeInterval = 6 * 60;

	// ��̃��[���̕�
	float loadWidth = 18.5f;

	// �Ԑ��ύX�t���O
	bool laneChangeFlag = false;
	bool leftLaneChangeFlag = false;
	bool rightLaneChangeFlag = false;

	// �Ԑ��ύX���s���ۂ̑O�̂̎ԂƂ̔�����Ƃ锼�a
	float laneRadius = 2 * loadWidth;
};

