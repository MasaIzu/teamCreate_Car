#include "EnemyPop.h"
#include <stdlib.h>
void EnemyPop::Update(Model* model)
{
	popTimer++;

	// �G�̃f�X�t���O�������Ă����烊�X�g�������
	enemy1.remove_if([](std::unique_ptr<Enemy>& enemy) { return enemy->IsDead(); });


	// �^�C�}�[���Ԋu���ԂɂȂ����烉���_���ɐ����ƎԎ�𒊑I���āA�ݒ肷��
	if (popTimer >= popInterval){
		carPattern_ = rand() % 3 + 1;
		switch (carPattern_)
		{
		case 1:// �Ԃ̐����p�^�[��---------------�P
			for (int i = 0; i < 3; i++) {

				// �Ԏ�̃p�^�[����ݒ�
				CarModelLottery();

				// �G�𐶐����A������
				std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
				newEnemy->Initialize(model, enemyPos1[i],carModel_);

				// �G�����X�g�ɓo�^
				enemy1.push_back(std::move(newEnemy));
			}

			// �����^�C�}�[��������
			popTimer = 0;

			break;
		case 2:// �Ԃ̐����p�^�[��---------------�Q
			for (int i = 0; i < 3; i++) {

				// �Ԏ�̃p�^�[����ݒ�
				CarModelLottery();

				// �G�𐶐����A������
				std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
				newEnemy->Initialize(model, enemyPos2[i], carModel_);

				// �G�����X�g�ɓo�^
				enemy1.push_back(std::move(newEnemy));
			}

			// �����^�C�}�[��������
			popTimer = 0;
			break;
		case 3:// �Ԃ̐����p�^�[��---------------�R
			for (int i = 0; i < 3; i++) {

				// �Ԏ�̃p�^�[����ݒ�
				CarModelLottery();

				// �G�𐶐����A������
				std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
				newEnemy->Initialize(model, enemyPos3[i], carModel_);

				// �G�����X�g�ɓo�^
				enemy1.push_back(std::move(newEnemy));
			}

			// �����^�C�}�[��������
			popTimer = 0;
			break;
		default:
			break;
		}
	}

	// �G�̍X�V�����̌Ăяo��
	for (std::unique_ptr<Enemy>& enemy : enemy1) {
		enemy->Update();
	}
}

void EnemyPop::Draw(const ViewProjection& viewProjection)
{
	//�G�L�����̕`��
	for (std::unique_ptr<Enemy>& enemy : enemy1) {
		enemy->Draw(viewProjection);
	}
}

void EnemyPop::CarModelLottery()
{
	// �Ԏ�̃p�^�[���𒊑I
	carModelnum_ = rand() % 3 + 1;

	// �Ԏ�̃p�^�[����ݒ�
	if (carModelnum_ == 1)
	{
		carModel_ = CarModel::truck;
	}
	else if (carModelnum_ == 2) {
		carModel_ = CarModel::prius;
	}
	else if (carModelnum_ == 3) {
		carModel_ = CarModel::ferrari;
	}
}
