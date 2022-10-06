#pragma once
#include <memory.h>
#include <list>
#include "Enemy.h"
class EnemyPop
{
public:// メンバ関数
	void Update();
	void Draw();
private:// メンバ変数
	// 敵の生成パターンのリスト
	std::list<std::unique_ptr<Enemy>> enemy1;
	std::list<std::unique_ptr<Enemy>> enemy2;
	
	// 敵の位置のパターンの配列
	Vector3 enemyPos1[3] = { { 0, 0, 0},
							 {-1, 0, 0},
						     { 1, 0, 0} };

	Vector3 enemyPos2[3] = { {-1, 0, 0},
						     {-2, 0, 1},
						     { 1, 0,-1} };

	Vector3 enemyPos3[3] = { { 2, 0,-1},
							 {-1, 0,-1},
							 { 1, 0, 1} };
	// 敵のランダムパターン
	int carModelnum_ = 0;
	CarModel carModel_ = CarModel::truck;
	int carPattern_ = 0;

	// 敵のポップするタイマー
	int popTimer = 0;
	
	// 敵のポップする間隔のタイマー
	int popInterval = 3 * 60;

};

