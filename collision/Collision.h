#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <cassert>
#include "DebugText.h"
#include "Input.h"
#include "ViewProjection.h"
#include <memory>
#include <list>

class collision {
public:
private:
	//ワールド変換データ
	WorldTransform worldTransform_;

	DebugText* debugText_ = nullptr;
	//モデル
	Model* model_ = nullptr;
	//モデル
	Model* enemyBulletModel_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;
};