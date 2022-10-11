#pragma once
#include <memory.h>
#include <list>
#include "Enemy.h"
#include "Collision.h"
#include"DebugText.h"

//自機クラスの前方宣言
class Player;

class EnemyPop
{
public:// メンバ関数

	EnemyPop();

	// 更新処理
	void Update(Model* model);

	// 描画処理
	void Draw(const ViewProjection& viewProjection);

	//当たり判定(車の後ろにいる時)
	void CarBack();

	//当たり判定(交通事故)
	void TrafficAccidentEnemyVer();


public://ゲッターセッター

	int GetTrafficAccidentFlag();
	void  SetPlayer(Player* player) { player_ = player; }

private:
	// 車種のパターンを抽選する関数
	void CarModelLottery();
private:// メンバ変数

	// 敵の生成パターンのリスト
	std::list<std::unique_ptr<Enemy>> enemy1;
	std::list<std::unique_ptr<Enemy>> enemy2;

	DebugText* debugText_ = nullptr;

	//自キャラ
	Player* player_ = nullptr;
	collision* collision_ = nullptr;

	
	// 一つのレーンの幅
	float loadWidth = 18.5f;

	// 敵の位置のパターンの配列
	Vector3 enemyPos1[3] = { { 0 * loadWidth, 0, 22*loadWidth},
							 {-2 * loadWidth, 0, 20*loadWidth},
							 { 2 * loadWidth, 0, 21*loadWidth} };

	Vector3 enemyPos2[3] = { {-1 * loadWidth, 0, 22*loadWidth},
							 {-2 * loadWidth, 0, 21*loadWidth},
							 { 1 * loadWidth, 0, 20*loadWidth} };

	Vector3 enemyPos3[3] = { { 2 * loadWidth, 0, 22*loadWidth},
							 {-1 * loadWidth, 0, 21*loadWidth},
							 { 1 * loadWidth, 0, 20*loadWidth} };
	// 敵のランダムパターン
	int carModelnum_ = 0;
	CarModel carModel_ = CarModel::truck;
	int carPattern_ = 0;

	// 敵のポップするタイマー
	int popTimer = 0;
	
	// 敵のポップする間隔のタイマー
	int popInterval = 2 * 60;

	int TrafficAccidentFlag;
};

