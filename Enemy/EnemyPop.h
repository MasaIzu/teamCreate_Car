#pragma once
#include <memory.h>
#include <list>
#include "Enemy.h"
#include "Collision.h"
#include"DebugText.h"

//���@�N���X�̑O���錾
class Player;

//���N���X�̑O���錾
class Wing;

class EnemyPop
{
public:// �����o�֐�

	EnemyPop();
	void Initialize();

	// �X�V����
	void Update(Model* model);

	// �`�揈��
	void Draw(const ViewProjection& viewProjection);

	//�����蔻��(�Ԃ̌��ɂ��鎞)
	void CarBack();

	//�����蔻��(��ʎ���)
	void TrafficAccidentEnemyVer();


public://�Q�b�^�[�Z�b�^�[
	int GetEnemyOverTakingCount();
	int GetTrafficAccidentFlag();
	void  SetPlayer(Player* player) { player_ = player; }
	void SetWing(Wing* wing) { wing_ = wing; }

	float GetGoalEmemyPos();

private:
	// �Ԏ�̃p�^�[���𒊑I����֐�
	void CarModelLottery();
private:// �����o�ϐ�

	// �G�̐����p�^�[���̃��X�g
	std::list<std::unique_ptr<Enemy>> enemy1;
	std::list<std::unique_ptr<Enemy>> enemy2;

	DebugText* debugText_ = nullptr;

	//���L����
	Player* player_ = nullptr;
	collision* collision_ = nullptr;

	//��
	Wing* wing_ = nullptr;

	
	// ��̃��[���̕�
	float loadWidth = 18.5f;

	// �G�̈ʒu�̃p�^�[���̔z��
	Vector3 enemyPos1[3] = { { 0 * loadWidth, 0, 32*loadWidth},
							 {-2 * loadWidth, 0, 30*loadWidth},
							 { 2 * loadWidth, 0, 31*loadWidth} };

	Vector3 enemyPos2[3] = { {-1 * loadWidth, 0, 32*loadWidth},
							 {-2 * loadWidth, 0, 31*loadWidth},
							 { 1 * loadWidth, 0, 30*loadWidth} };

	Vector3 enemyPos3[3] = { { 2 * loadWidth, 0, 32*loadWidth},
							 {-1 * loadWidth, 0, 31*loadWidth},
							 { 1 * loadWidth, 0, 30*loadWidth} };

	Vector3 enemyPos4[4] = { { 2 * loadWidth, 0, 32 * loadWidth},
							 {-1 * loadWidth, 0, 31 * loadWidth},
							 { 0 * loadWidth, 0, 30 * loadWidth},
		                     {-2 * loadWidth, 0, 34 * loadWidth} };

	Vector3 enemyPos5[4] = { { 1 * loadWidth, 0, 30 * loadWidth},
							 {-2 * loadWidth, 0, 33 * loadWidth},
							 {-1 * loadWidth, 0, 31 * loadWidth},
							 { 0 * loadWidth, 0, 34 * loadWidth} };
	// �G�̃����_���p�^�[��
	int carModelnum_ = 0;
	CarModel carModel_ = CarModel::truck;
	int carPattern_ = 0;

	// �G�̃|�b�v����^�C�}�[
	int popTimer = 0;
	
	// �G�̃|�b�v����Ԋu�̃^�C�}�[
	int popInterval = 2 * 60;

	int TrafficAccidentFlag;

	int overTakingCount=200;

	// �G�̃��f��
	Model* puriusModel = nullptr;
	Model* ferariModel = nullptr;
	Model* trakuModel = nullptr;

	// �S�[���̓G
	std::unique_ptr<Enemy> GoalEnemy = nullptr;
	std::unique_ptr<Enemy> GoalFlagOBJ = nullptr;
	Model* GoalEnemyModel = nullptr;
	Model* GoalFlagOBJModel = nullptr;
	Vector3 GoalEnemyPos = { 0 * loadWidth, 0, 34 * loadWidth };
	bool goalFlag = false;
};

