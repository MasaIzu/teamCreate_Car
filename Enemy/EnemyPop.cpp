#include "EnemyPop.h"
#include <stdlib.h>
#include"Player.h"
#include "wing.h"
#include <time.h>

EnemyPop::EnemyPop() {

	collision_ = new collision();
	TrafficAccidentFlag = 0;
	debugText_ = DebugText::GetInstance();
	overTakingCount = 290;
}

void EnemyPop::Initialize()
{
	puriusModel = Model::CreateFromOBJ("puriusu", true);
	trakuModel = Model::CreateFromOBJ("trakku", true);
	ferariModel = Model::CreateFromOBJ("CarFerari", true);
	GoalEnemyModel = Model::CreateFromOBJ("GoalCar", true);
	GoalFlagOBJModel = Model::CreateFromOBJ("GoalFlag", true);
}

void EnemyPop::Update(Model* model)
{
	popTimer++;

	// �G�̃f�X�t���O�������Ă����烊�X�g�������
	enemy1.remove_if([](std::unique_ptr<Enemy>& enemy) { return enemy->IsDead(); });

	// �v���C���[�̃X�s�[�h�ɉ����ēG�̃|�b�v�̊Ԋu���グ��
	popInterval = 3 * 60 - (10 * player_->GetPlayerSpeed());


	// �^�C�}�[���Ԋu���ԂɂȂ����烉���_���ɐ����ƎԎ�𒊑I���āA�ݒ肷��
	if (overTakingCount <= 300) {
		if (popTimer >= popInterval) {

			carPattern_ = rand() % 5 + 1;
			switch (carPattern_)
			{
			case 1:// �Ԃ̐����p�^�[��---------------�P
				for (int i = 0; i < 3; i++) {

					// �Ԏ�̃p�^�[����ݒ�
					CarModelLottery();

					// �G�𐶐����A������
					std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
					newEnemy->SetPlayer(player_);
					if (carModelnum_ == 1) {
						newEnemy->Initialize(trakuModel, enemyPos1[i], carModel_);
					}
					else if (carModelnum_ == 2) {
						newEnemy->Initialize(puriusModel, enemyPos1[i], carModel_);
					}
					else if (carModelnum_ == 3) {
						newEnemy->Initialize(ferariModel, enemyPos1[i], carModel_);
					}
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
					newEnemy->SetPlayer(player_);
					if (carModelnum_ == 1) {
						newEnemy->Initialize(trakuModel, enemyPos2[i], carModel_);
					}
					else if (carModelnum_ == 2) {
						newEnemy->Initialize(puriusModel, enemyPos2[i], carModel_);
					}
					else if (carModelnum_ == 3) {
						newEnemy->Initialize(ferariModel, enemyPos2[i], carModel_);
					}


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
					newEnemy->SetPlayer(player_);

					if (carModelnum_ == 1) {
						newEnemy->Initialize(trakuModel, enemyPos3[i], carModel_);
					}
					else if (carModelnum_ == 2) {
						newEnemy->Initialize(puriusModel, enemyPos3[i], carModel_);
					}
					else if (carModelnum_ == 3) {
						newEnemy->Initialize(ferariModel, enemyPos3[i], carModel_);
					}


					// �G�����X�g�ɓo�^
					enemy1.push_back(std::move(newEnemy));
				}

				// �����^�C�}�[��������
				popTimer = 0;
				break;
			case 4:
				for (int i = 0; i < 4; i++) {
					// �Ԏ�̃p�^�[����ݒ�
					CarModelLottery();

					// �G�𐶐����A������
					std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
					newEnemy->SetPlayer(player_);

					if (carModelnum_ == 1) {
						newEnemy->Initialize(trakuModel, enemyPos4[i], carModel_);
					}
					else if (carModelnum_ == 2) {
						newEnemy->Initialize(puriusModel, enemyPos4[i], carModel_);
					}
					else if (carModelnum_ == 3) {
						newEnemy->Initialize(ferariModel, enemyPos4[i], carModel_);
					}

					// �G�����X�g�ɓo�^
					enemy1.push_back(std::move(newEnemy));
				}
				// �����^�C�}�[��������
				popTimer = 0;
				break;
			case 5:
				for (int i = 0; i < 4; i++) {
					// �Ԏ�̃p�^�[����ݒ�
					CarModelLottery();

					// �G�𐶐����A������
					std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
					newEnemy->SetPlayer(player_);

					if (carModelnum_ == 1) {
						newEnemy->Initialize(trakuModel, enemyPos5[i], carModel_);
					}
					else if (carModelnum_ == 2) {
						newEnemy->Initialize(puriusModel, enemyPos5[i], carModel_);
					}
					else if (carModelnum_ == 3) {
						newEnemy->Initialize(ferariModel, enemyPos5[i], carModel_);
					}

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
	}

	if (overTakingCount == 300) {
		goalFlag = true;

	}
	if (goalFlag == true) {

		GoalEnemy = std::make_unique<Enemy>();
		GoalFlagOBJ = std::make_unique<Enemy>();
		GoalEnemy->SetPlayer(player_);
		GoalFlagOBJ->SetPlayer(player_);
		GoalEnemy->Initialize(GoalEnemyModel, GoalEnemyPos, CarModel::ferrari);
		GoalFlagOBJ->Initialize(GoalFlagOBJModel, GoalEnemyPos, CarModel::ferrari);
		goalFlag = false;
	}
	if (GoalEnemy != nullptr)
	{
		GoalEnemy->Update();
		GoalFlagOBJ->Update();
	}
	// �G�̍X�V�����̌Ăяo��
	for (std::unique_ptr<Enemy>& enemy : enemy1) {
		for (std::unique_ptr<Enemy>& enemy2 : enemy1) {
			// �������g�Ƃ͔���Ƃ�Ȃ��悤�ɂ��鏈��
			if (enemy->GetPos().x == enemy2->GetPos().x &&
				enemy->GetPos().y == enemy2->GetPos().y &&
				enemy->GetPos().z == enemy2->GetPos().z) {
			}
			else {
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
					if (enemy->leftLaneChangeFlag() == false && enemy->rightLaneChangeFlag() == false) {
						for (std::unique_ptr<Enemy>& enemy3 : enemy1) {
							// �������g�Ƃ͔���Ƃ�Ȃ��悤�ɂ��鏈��
							if (enemy->GetPos().x == enemy3->GetPos().x &&
								enemy->GetPos().y == enemy3->GetPos().y &&
								enemy->GetPos().z == enemy3->GetPos().z) {
							}
							else {
								Vector3 pos = enemy3->GetPos();

								// ���Ɉړ��\���`�F�b�N
								if (enemy->rightLaneChangeFlag() == false) {
									enemy->LeftLaneChangeCheck(pos);

									if (enemy->leftLaneChangeFlag() == false) {
										// ���������������ꍇ�ɉE�Ɉړ��\���`�F�b�N
										enemy->RightLaneChangeCheck(pos);

										// �E���\�Ȃ�
										if (enemy->rightLaneChangeFlag() == true) {
											enemy->SetLeftLaneChangeFlag(false);
										}
										// �ǂ����������������ꍇ�����𔲂���
										if (enemy->rightLaneChangeFlag() == false) {
											break;
										}
									}
								}
							}
						}
					}
				}

				// ��ԍ��̎��E�Ɉړ��\���`�F�b�N����
				if (enemy->lane1ChangeFlag() == true) {
					for (std::unique_ptr<Enemy>& enemy3 : enemy1) {
						// �������g�Ƃ͔���Ƃ�Ȃ��悤�ɂ��鏈��
						if (enemy->GetPos().x == enemy3->GetPos().x &&
							enemy->GetPos().y == enemy3->GetPos().y &&
							enemy->GetPos().z == enemy3->GetPos().z) {
						}
						else {
							Vector3 pos = enemy3->GetPos();

							if (enemy->rightLaneChangeFlag() == false) {
								// �E�Ɉړ��\���`�F�b�N
								enemy->RightLaneChangeCheck(pos);
							}
						}
					}
				}

				// ��ԉE�̎����Ɉړ��\���`�F�b�N����
				if (enemy->lane5ChangeFlag() == true) {
					for (std::unique_ptr<Enemy>& enemy3 : enemy1) {
						// �������g�Ƃ͔���Ƃ�Ȃ��悤�ɂ��鏈��
						if (enemy->GetPos().x == enemy3->GetPos().x &&
							enemy->GetPos().y == enemy3->GetPos().y &&
							enemy->GetPos().z == enemy3->GetPos().z) {
						}
						else {
							Vector3 pos = enemy3->GetPos();

							if (enemy->leftLaneChangeFlag() == false)
							{
								// ���Ɉړ��\���`�F�b�N
								enemy->LeftLaneChangeCheck(pos);
							}

						}
					}
				}
			}
		}
		enemy->Update();

		if (player_->GetPlayerPos().z > enemy->GetPos().z) {
			if (enemy->playerOverTaking == 0) {
				enemy->playerOverTaking = 1;
				overTakingCount++;
			}
		}
	}


	CarBack();
	TrafficAccidentEnemyVer();

	debugText_->SetPos(50, 70);
	debugText_->Printf(
		"count:(%d)", overTakingCount);

}

void EnemyPop::Draw(const ViewProjection& viewProjection)
{
	//�G�L�����̕`��
	for (std::unique_ptr<Enemy>& enemy : enemy1) {
		enemy->Draw(viewProjection);
	}
	if (GoalEnemy != nullptr) {
		GoalEnemy->Draw(viewProjection);
		GoalFlagOBJ->Draw(viewProjection);
	}
}

void EnemyPop::CarBack() {

	Vector3 PlayerVec = player_->GetPlayerPos();
	Vector3 Psize = { 5,5,300 };
	Vector3 Esize = { 5,5,5 };
	for (std::unique_ptr<Enemy>& enemy : enemy1) {

		Vector3 enemyPos_ = enemy->GetWorldTransform().translation_;
		if (collision_->boxCollision(PlayerVec, enemyPos_, Psize, Esize, true) == true) {
			player_->EnemyCarBack();
			wing_->Distance();
		}
	}
}

void EnemyPop::TrafficAccidentEnemyVer() {

	Vector3 PlayerVec = player_->GetPlayerPos();
	Vector3 Psize = { 5,2,6 };
	Vector3 Esize = { 5,6,6 };
	for (std::unique_ptr<Enemy>& enemy : enemy1) {

		Vector3 enemyPos_ = enemy->GetWorldTransform().translation_;
		if (collision_->boxCollision(PlayerVec, enemyPos_, Psize, Esize) == true) {
			TrafficAccidentFlag = 1;
			player_->TrafficAccidentFlag();
		}
		/*else {
			TrafficAccidentFlag = 0;
		}*/
	}

}

int EnemyPop::GetTrafficAccidentFlag() {

	return TrafficAccidentFlag;
}

float EnemyPop::GetGoalEmemyPos()
{
	if (GoalEnemy!= NULL) {
		return GoalEnemy->GetPos().z;
	}
	return 100.0f;
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

int EnemyPop::GetEnemyOverTakingCount()
{
	return overTakingCount;
}