#pragma once
#include <memory.h>
#include <list>
#include "Enemy.h"
class EnemyPop
{
public:// �����o�֐�

	// �X�V����
	void Update(Model* model);

	// �`�揈��
	void Draw(const ViewProjection& viewProjection);
private:
	// �Ԏ�̃p�^�[���𒊑I����֐�
	void CarModelLottery();
private:// �����o�ϐ�

	// �G�̐����p�^�[���̃��X�g
	std::list<std::unique_ptr<Enemy>> enemy1;
	std::list<std::unique_ptr<Enemy>> enemy2;
	
	// ��̃��[���̕�
	float loadWidth = 18.5f;

	// �G�̈ʒu�̃p�^�[���̔z��
	Vector3 enemyPos1[3] = { { 0 * loadWidth, 0, 22*loadWidth},
							 {-2 * loadWidth, 0, 20*loadWidth},
							 { 2 * loadWidth, 0, 21*loadWidth} };

	Vector3 enemyPos2[3] = { {-1 * loadWidth, 0, 22*loadWidth},
							 {-2 * loadWidth, 0, 21*loadWidth},
							 { 1 * loadWidth, 0, 20*loadWidth} };

	Vector3 enemyPos3[3] = { { 2 * loadWidth, 0, 22*loadWidth},
							 {-1 * loadWidth, 0, 21*loadWidth},
							 { 1 * loadWidth, 0, 20*loadWidth} };
	// �G�̃����_���p�^�[��
	int carModelnum_ = 0;
	CarModel carModel_ = CarModel::truck;
	int carPattern_ = 0;

	// �G�̃|�b�v����^�C�}�[
	int popTimer = 0;
	
	// �G�̃|�b�v����Ԋu�̃^�C�}�[
	int popInterval = 5 * 60;


};

