#include "EnemyPop.h"
#include <stdlib.h>
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
		enemy->Update();
	}
}

void EnemyPop::Draw(const ViewProjection& viewProjection)
{
	//敵キャラの描画
	for (std::unique_ptr<Enemy>& enemy : enemy1) {
		enemy->Draw(viewProjection);
	}
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
