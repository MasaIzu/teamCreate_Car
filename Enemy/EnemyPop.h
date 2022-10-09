#pragma once
#include <memory.h>
#include <list>
#include "Enemy.h"
class EnemyPop
{
public:// メンバ関数

	// 更新処理
	void Update(Model* model);

	// 描画処理
	void Draw(const ViewProjection& viewProjection);
private:
	// 車種のパターンを抽選する関数
	void CarModelLottery();
private:// メンバ変数
	// 敵の生成パターンのリスト
	std::list<std::unique_ptr<Enemy>> enemy1;
	std::list<std::unique_ptr<Enemy>> enemy2;
	
	// 敵の位置のパターンの配列
	Vector3 enemyPos1[3] = { { 0, 0, 1},
							 {-2, 0,-2},
						     { 2, 0,-3} };

	Vector3 enemyPos2[3] = { {-2, 0, 0},
						     {-4, 0, 1},
						     { 2, 0,-2} };

	Vector3 enemyPos3[3] = { { 4, 0,-2},
							 {-2, 0,-2},
							 { 2, 0, 2} };
	// 敵のランダムパターン
	int carModelnum_ = 0;
	CarModel carModel_ = CarModel::truck;
	int carPattern_ = 0;

	// 敵のポップするタイマー
	int popTimer = 0;
	
	// 敵のポップする間隔のタイマー
	int popInterval = 5 * 60;


};

