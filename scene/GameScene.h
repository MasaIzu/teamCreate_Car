#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "Player.h"
#include "DebugCamera.h"
#include "EnemyPop.h"
#include "Load.h"
#include "Enemy.h"
#include "Collision.h"
#include "wing.h"
#include "background.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

  private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	//3Dモデル
	Model* model_ = nullptr;

	ViewProjection viewProjection_;

	//プレイヤー
	Player* player_ = nullptr;
	Model* playerModel_ = nullptr;
	
	// 敵の生成
	EnemyPop* enemyPop_ = nullptr;

	DebugCamera* debugCamera_ = nullptr;
	Enemy* enemy_ = nullptr;

	//道路
	Model* loadModel_ = nullptr;
	Load* load_ = nullptr;

	//背景
	Model* groundModel_ = nullptr;
	BackGround* backGround_ = nullptr;

	//風
	Model* wingModel_ = nullptr;
	Wing* wing_ = nullptr;

	//当たり判定
	collision* cali_ = nullptr;


	/// <summary>
	/// ゲームシーン用
	/// </summary>
	int scene;
	//ロード時間
	int waitTimer;
};
