#include "Enemy.h"

void Enemy::Initialize(Model* model ,Vector3& pos, CarModel carModel)
{
	// NULLポインタチェック
	assert(model);

	model_ = model;

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// 初期座標を設定
	worldTransform_.translation_ = pos;

	// 車種を設定
	carModel_ = carModel;

	// 車種ごとのスピードを設定
	switch (carModel_)
	{
	case CarModel::truck:
		moveSpeed_ = { 0.6f,0.6f, 0.6f };
		break;
	case CarModel::prius:
		moveSpeed_ = { 1.0f,1.0f, 1.0f };
		break;
	case CarModel::ferrari:
		moveSpeed_ = { 1.6f,1.6f, 1.6f };
		break;
	default:
		break;
	}
}

void Enemy::Update()
{
	
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	if (isDead_ == false) {
		model_->Draw(worldTransform_, viewProjection, textureHandle_);
	}
}
