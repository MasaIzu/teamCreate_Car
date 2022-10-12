#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Affin.h"
#include <cassert>
#include "collision.h"
#include "Player.h"

enum class CarModel {
	truck,// �g���b�N�i�x���ԁj
	prius,// �v���E�X�i��ʎԁj
	ferrari,// �t�F���[���i�����ԁj
};

//���@�N���X�̑O���錾
class Player;

class Enemy
{
public:// �����o�֐�

	// �����������֐�
	void Initialize(Model* model, Vector3& pos, CarModel carModel);

	// �X�V�����֐�
	void Update();

	// �Ԑ��ύX�����֐�
	void Lane1ChangeCheck(Vector3& pos);

	void Lane5ChangeCheck(Vector3& pos);

	void LaneChangeCheck(Vector3& pos);

	void LeftLaneChangeCheck(Vector3& pos);

	void RightLaneChangeCheck(Vector3& pos);

	// �|�W�V�����̃Q�b�^�[
	Vector3 GetPos() { return worldTransform_.translation_; }

	// ���[���h�g�����X�t�H�[���̃Q�b�^�[
	WorldTransform GetWorldTransform() { return worldTransform_; }

	// �Ԑ��ύX�t���O�̃Q�b�^�[
	bool laneChangeFlag() const { return laneChangeFlag_; }

	bool lane1ChangeFlag() const { return lane1ChangeFlag_; }

	bool lane5ChangeFlag() const { return lane5ChangeFlag_; }

	bool leftLaneChangeFlag() const { return leftLaneChangeFlag_; }

	bool rightLaneChangeFlag() const { return rightLaneChangeFlag_; }

	// �Z�b�^�[
	void SetWouldTransform(WorldTransform worldTransform);

	void SetLeftLaneChangeFlag(bool leftLaneChangeFlag);

	void  SetPlayer(Player* player) { player_ = player; }

	// �`�揈���֐�
	void Draw(const ViewProjection& viewProjection);

	// ���S�t���O��n��
	bool IsDead() const { return isDead_; }

	//�t���O�u�N
	void ContactPlayer();
	bool ContactFlag() { return contactFlag; }

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
	int lifeInterval = 5 * 60;

	// ��̃��[���̕�
	float loadWidth = 18.5f;

	// �Ԑ��ύX�t���O
	bool laneChangeFlag_ = false;
	bool lane1ChangeFlag_ = false;
	bool lane5ChangeFlag_ = false;
	bool leftLaneChangeFlag_ = false;
	bool rightLaneChangeFlag_ = false;

	// �Ԑ��ύX���s���ۂ̑O�̂̎ԂƂ̔�����Ƃ锼�a
	float laneRadius = 8 * 10;

	// �ŏ��̈ʒu��ۑ�
	Vector3 initPos;

	//������������t���O
	bool contactFlag = false;

	//�܂������ɓ��������ꍇ
	bool contactVer0 = false;
	int fukitobiTimeMax = 60;
	int fukitobiTime = 0;

	//�E�ړ����ɓ��������ꍇ
	bool contactVer1 = false;
	//���ړ����ɓ��������ꍇ
	bool contactVer2 = false;

	collision* collision_ = nullptr;
	Player* player_ = nullptr;
};

