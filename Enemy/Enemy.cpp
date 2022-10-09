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
		moveSpeed_ = { 0.0f,0.0f, 0.1f };
		break;
	case CarModel::prius:
		moveSpeed_ = { 0.0f,0.0f, 0.2f };
		break;
	case CarModel::ferrari:
		moveSpeed_ = { 0.0f,0.0f, 0.25f };
		break;
	default:
		break;
	}
}

void Enemy::Update()
{
	// 生きている時間を加算
	lifeTimer++;

	//前に進む処理
	worldTransform_.translation_ += moveSpeed_;

	// 行列を計算し転送
	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();

	// 生きている時間が限界に達したら消す
	if (lifeTimer >= lifeInterval) {
		isDead_ = true;
	}
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	//if (isDead_ == false) {
		model_->Draw(worldTransform_, viewProjection);
	//}
}
