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
	worldTransform_.scale_ = { 5,5,5 };

	// 車種を設定
	carModel_ = carModel;

	// 車種ごとのスピードを設定
	switch (carModel_)
	{
	case CarModel::truck:
		moveSpeed_ = { 0.0f,0.0f, 3.0f };
		break;
	case CarModel::prius:
		moveSpeed_ = { 0.0f,0.0f, 2.0f };
		break;
	case CarModel::ferrari:
		moveSpeed_ = { 0.0f,0.0f, 1.5f };
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
	worldTransform_.translation_ -= moveSpeed_;

	// 行列を計算し転送
	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();

	// 生きている時間が限界に達したら消す
	if (lifeTimer >= lifeInterval) {
		isDead_ = true;
	}
}

void Enemy::LaneChangeCheck(Vector3& pos)
{
	// 一番右側のレーンにいた場合の車線変更
	if (worldTransform_.translation_.x >= 2 * loadWidth) {
		if (worldTransform_.translation_.z += laneRadius <= pos.z) {
			//float leftpos = worldTransform_.translation_.x + (1 * loadWidth);
			laneChangeFlag = true;
		}
	}
}

void Enemy::LeftLaneChangeCheck(Vector3& pos)
{
	Vector3 leftpos = { worldTransform_.translation_.x - (1 * loadWidth),worldTransform_.translation_.y,worldTransform_.translation_.z };
	if (leftpos.z += laneRadius <= pos.z) {
		leftLaneChangeFlag = true;
	}
}

void Enemy::RightLaneChangeCheck(Vector3& pos)
{
	Vector3 rightpos = { worldTransform_.translation_.x + (1 * loadWidth),worldTransform_.translation_.y,worldTransform_.translation_.z };
	if (rightpos.z += laneRadius <= pos.z) {
		rightLaneChangeFlag = true;
	}
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	//if (isDead_ == false) {
		model_->Draw(worldTransform_, viewProjection);
	//}
}
