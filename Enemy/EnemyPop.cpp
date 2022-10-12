#include "EnemyPop.h"
#include <stdlib.h>
#include"Player.h"
#include "wing.h"

EnemyPop::EnemyPop(){

	collision_ = new collision();
	TrafficAccidentFlag = 0;
	debugText_ = DebugText::GetInstance();

}

void EnemyPop::Update(Model* model)
{
	popTimer++;

	// 敵のデスフラグが立っていたらリストから消す
	enemy1.remove_if([](std::unique_ptr<Enemy>& enemy) { return enemy->IsDead(); });


	// タイマーが間隔時間になったらランダムに生成と車種を抽選して、設定する
	if (popTimer >= popInterval){
		carPattern_ = rand() % 3 + 1;
		switch (carPattern_)
		{
		case 1:// 車の生成パターン---------------１
			for (int i = 0; i < 3; i++) {

				// 車種のパターンを設定
				CarModelLottery();

				// 敵を生成し、初期化
				std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
				newEnemy->Initialize(model, enemyPos1[i],carModel_);

				// 敵をリストに登録
				enemy1.push_back(std::move(newEnemy));
			}

			// 生成タイマーを初期化
			popTimer = 0;

			break;
		case 2:// 車の生成パターン---------------２
			for (int i = 0; i < 3; i++) {

				// 車種のパターンを設定
				CarModelLottery();

				// 敵を生成し、初期化
				std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
				newEnemy->Initialize(model, enemyPos2[i], carModel_);

				// 敵をリストに登録
				enemy1.push_back(std::move(newEnemy));
			}

			// 生成タイマーを初期化
			popTimer = 0;
			break;
		case 3:// 車の生成パターン---------------３
			for (int i = 0; i < 3; i++) {

				// 車種のパターンを設定
				CarModelLottery();

				// 敵を生成し、初期化
				std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
				newEnemy->Initialize(model, enemyPos3[i], carModel_);

				// 敵をリストに登録
				enemy1.push_back(std::move(newEnemy));
			}

			// 生成タイマーを初期化
			popTimer = 0;
			break;
		default:
			break;
		}
	}



	// 敵の更新処理の呼び出し
	for (std::unique_ptr<Enemy>& enemy : enemy1) {
		for (std::unique_ptr<Enemy>& enemy2 : enemy1) {
			// 自分自身とは判定とらないようにする処理
			if (enemy->GetPos().x == enemy2->GetPos().x &&
				enemy->GetPos().y == enemy2->GetPos().y &&
				enemy->GetPos().z == enemy2->GetPos().z) {
			}
			else{
				Vector3 pos = enemy2->GetPos();

				// 一番左のレーンをチェック
				enemy->Lane1ChangeCheck(pos);

				// 一番右のレーンチェック
				enemy->Lane5ChangeCheck(pos);

				// それ以外の時のチェック
				if (enemy->lane1ChangeFlag() == false && enemy->lane5ChangeFlag() == false) {
					enemy->LaneChangeCheck(pos);
				}

				// 前に別の車がいたら右もしくは左に移動可能かチェックする
				if (enemy->laneChangeFlag() == true) {
					if (enemy->leftLaneChangeFlag() == false && enemy->rightLaneChangeFlag() == false) {
						for (std::unique_ptr<Enemy>& enemy3 : enemy1) {
							// 自分自身とは判定とらないようにする処理
							if (enemy->GetPos().x == enemy3->GetPos().x &&
								enemy->GetPos().y == enemy3->GetPos().y &&
								enemy->GetPos().z == enemy3->GetPos().z) {
							}
							else {
								Vector3 pos = enemy3->GetPos();

								// 左に移動可能かチェック
								if (enemy->rightLaneChangeFlag() == false) {
									enemy->LeftLaneChangeCheck(pos);

									if (enemy->leftLaneChangeFlag() == false) {
										// 左が無理だった場合に右に移動可能かチェック
										enemy->RightLaneChangeCheck(pos);

										// 右が可能なら
										if (enemy->rightLaneChangeFlag() == true) {
											enemy->SetLeftLaneChangeFlag(false);
										}
										// どっちも無理だった場合処理を抜ける
										if (enemy->rightLaneChangeFlag() == false) {
											break;
										}
									}
								}
							}
						}
					}
				}

				// 一番左の時右に移動可能かチェックする
				if (enemy->lane1ChangeFlag() == true) {
					for (std::unique_ptr<Enemy>& enemy3 : enemy1) {
						// 自分自身とは判定とらないようにする処理
						if (enemy->GetPos().x == enemy3->GetPos().x &&
							enemy->GetPos().y == enemy3->GetPos().y &&
							enemy->GetPos().z == enemy3->GetPos().z) {
						}
						else {
							Vector3 pos = enemy3->GetPos();

							// 右に移動可能かチェック
							enemy->RightLaneChangeCheck(pos);
						}
					}
				}

				// 一番右の時左に移動可能かチェックする
				if (enemy->lane5ChangeFlag() == true) {
					for (std::unique_ptr<Enemy>& enemy3 : enemy1) {
						// 自分自身とは判定とらないようにする処理
						if (enemy->GetPos().x == enemy3->GetPos().x &&
							enemy->GetPos().y == enemy3->GetPos().y &&
							enemy->GetPos().z == enemy3->GetPos().z) {
						}
						else {
							Vector3 pos = enemy3->GetPos();

							// 左に移動可能かチェック
							enemy->LeftLaneChangeCheck(pos);
						}
					}
				}
			}
		}
		enemy->Update();
	}


	CarBack();
	TrafficAccidentEnemyVer();

	debugText_->SetPos(50, 90);
	debugText_->Printf(
		"(%d)", TrafficAccidentFlag);

}

void EnemyPop::Draw(const ViewProjection& viewProjection)
{
	//敵キャラの描画
	for (std::unique_ptr<Enemy>& enemy : enemy1) {
		enemy->Draw(viewProjection);
	}
}

void EnemyPop::CarBack(){

	Vector3 PlayerVec = player_->GetPlayerPos();
	Vector3 Psize = { 5,5,250 };
	Vector3 Esize = { 5,5,5 };
	for (std::unique_ptr<Enemy>& enemy : enemy1) {

		Vector3 enemyPos_ = enemy->GetWorldTransform().translation_;
		if (collision_->boxCollision(PlayerVec, enemyPos_, Psize, Esize, true)== true) {
			player_->EnemyCarBack();
			wing_->Distance();
		}
	}
}

void EnemyPop::TrafficAccidentEnemyVer(){

	Vector3 PlayerVec = player_->GetPlayerPos();
	Vector3 Psize = { 5,5,10 };
	Vector3 Esize = { 5,5,5 };
	for (std::unique_ptr<Enemy>& enemy : enemy1) {

		Vector3 enemyPos_ = enemy->GetWorldTransform().translation_;
		if (collision_->boxCollision(PlayerVec, enemyPos_, Psize, Esize,true) == true) {
			TrafficAccidentFlag = 1;
		}
		/*else {
			TrafficAccidentFlag = 0;
		}*/
	}

}

int EnemyPop::GetTrafficAccidentFlag(){

	return TrafficAccidentFlag;
}

void EnemyPop::CarModelLottery()
{
	// 車種のパターンを抽選
	carModelnum_ = rand() % 3 + 1;

	// 車種のパターンを設定
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
