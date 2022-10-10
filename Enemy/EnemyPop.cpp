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
		for (std::unique_ptr<Enemy>& enemy2 : enemy1) {
			// �������g�Ƃ͔���Ƃ�Ȃ��悤�ɂ��鏈��
			if (enemy->GetPos().x == enemy2->GetPos().x &&
				enemy->GetPos().y == enemy2->GetPos().y &&
				enemy->GetPos().z == enemy2->GetPos().z) {
				break;
			}
			Vector3 pos = enemy2->GetPos();

			// ��ԍ��̃��[�����`�F�b�N
			enemy->Lane1ChangeCheck(pos);

			// ��ԉE�̃��[���`�F�b�N
			enemy->Lane5ChangeCheck(pos);

			// ����ȊO�̎��̃`�F�b�N
			if (enemy->lane1ChangeFlag() == false && enemy->lane5ChangeFlag() == false) {
				enemy->LaneChangeCheck(pos);
			}
			
			// �O�ɕʂ̎Ԃ�������E�������͍��Ɉړ��\���`�F�b�N����
			if (enemy->laneChangeFlag() == true) {
				for (std::unique_ptr<Enemy>& enemy3 : enemy1) {
					// �������g�Ƃ͔���Ƃ�Ȃ��悤�ɂ��鏈��
					if (enemy->GetPos().x == enemy3->GetPos().x &&
						enemy->GetPos().y == enemy3->GetPos().y &&
						enemy->GetPos().z == enemy3->GetPos().z) {
						break;
					}
					Vector3 pos = enemy3->GetPos();

					// ���Ɉړ��\���`�F�b�N
					enemy->LeftLaneChangeCheck(pos);
					if (enemy->leftLaneChangeFlag() == false) {
						// ���������������ꍇ�ɉE�Ɉړ��\���`�F�b�N
						enemy->RightLaneChangeCheck(pos);
						break;
					}
					break;
				}
			}

			// ��ԍ��̎��E�Ɉړ��\���`�F�b�N����
			if (enemy->lane1ChangeFlag() == true) {
				for (std::unique_ptr<Enemy>& enemy3 : enemy1) {
					// �������g�Ƃ͔���Ƃ�Ȃ��悤�ɂ��鏈��
					if (enemy->GetPos().x == enemy3->GetPos().x &&
						enemy->GetPos().y == enemy3->GetPos().y &&
						enemy->GetPos().z == enemy3->GetPos().z) {
						break;
					}
					Vector3 pos = enemy3->GetPos();

					// �E�Ɉړ��\���`�F�b�N
					enemy->RightLaneChangeCheck(pos);
					break;
				}
			}

			// ��ԉE�̎����Ɉړ��\���`�F�b�N����
			if (enemy->lane5ChangeFlag() == true) {
				for (std::unique_ptr<Enemy>& enemy3 : enemy1) {
					// �������g�Ƃ͔���Ƃ�Ȃ��悤�ɂ��鏈��
					if (enemy->GetPos().x == enemy3->GetPos().x &&
						enemy->GetPos().y == enemy3->GetPos().y &&
						enemy->GetPos().z == enemy3->GetPos().z) {
						break;
					}
					Vector3 pos = enemy3->GetPos();

					// ���Ɉړ��\���`�F�b�N
					enemy->LeftLaneChangeCheck(pos);
					break;
				}
			}
		}
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
