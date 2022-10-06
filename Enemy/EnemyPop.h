#pragma once
#include <memory.h>
#include <list>
#include "Enemy.h"
class EnemyPop
{
public:// �����o�֐�
	void Update();
	void Draw();
private:// �����o�ϐ�
	// �G�̐����p�^�[���̃��X�g
	std::list<std::unique_ptr<Enemy>> enemy1;
	std::list<std::unique_ptr<Enemy>> enemy2;
	
	// �G�̈ʒu�̃p�^�[���̔z��
	Vector3 enemyPos1[3] = { { 0, 0, 0},
							 {-1, 0, 0},
						     { 1, 0, 0} };

	Vector3 enemyPos2[3] = { {-1, 0, 0},
						     {-2, 0, 1},
						     { 1, 0,-1} };

	Vector3 enemyPos3[3] = { { 2, 0,-1},
							 {-1, 0,-1},
							 { 1, 0, 1} };
	// �G�̃����_���p�^�[��
	int carModelnum_ = 0;
	CarModel carModel_ = CarModel::truck;
	int carPattern_ = 0;

	// �G�̃|�b�v����^�C�}�[
	int popTimer = 0;
	
	// �G�̃|�b�v����Ԋu�̃^�C�}�[
	int popInterval = 3 * 60;

};

