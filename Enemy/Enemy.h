#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Affin.h"
#include <cassert>

enum class CarModel {
	truck,// トラック（遅い車）
	prius,// プリウス（一般車）
	ferrari,// フェラーリ（速い車）
};

class Enemy
{
public:// メンバ関数

	// 初期化処理関数
	void Initialize(Model* model ,Vector3& pos, CarModel carModel);

	// 更新処理関数
	void Update();

	// 描画処理関数
	void Draw(const ViewProjection& viewProjection);

	// 死亡フラグを渡す
	bool IsDead() const { return isDead_; }

private:// メンバ変数

	// ワールド変換データ
	WorldTransform worldTransform_;

	//モデル
	Model* model_ = nullptr;

	// 速度全般
	// 進む速度
	Vector3 moveSpeed_ = { 0.0f,0.0f,1.0f };
	// 回転速度
	Vector3 rotationSpeed_ = { 0.1f,0.1f, 0.1f };

	// デスフラグ
	bool isDead_ = false;

	// 車のパターン
	CarModel carModel_ = CarModel::prius;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// アフィン変換

};

