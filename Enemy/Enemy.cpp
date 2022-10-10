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
	initPos = worldTransform_.translation_;
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

	// 左車線に移動可能だったら、一レーン移動させる
	if (leftLaneChangeFlag_ == true) {
		if (worldTransform_.translation_.x > initPos.x - (1 * loadWidth)) {
			worldTransform_.translation_.x -= 0.5f;
		}
		if (worldTransform_.translation_.x <= initPos.x - (1 * loadWidth)) {
			leftLaneChangeFlag_ = false;
		}
	}

	// 右車線に移動可能だったら、一レーン移動させる
	if (rightLaneChangeFlag_ == true) {
		if (worldTransform_.translation_.x < initPos.x + (1 * loadWidth)) {
			worldTransform_.translation_.x += 0.5f;
		}
		if (worldTransform_.translation_.x >= initPos.x + (1 * loadWidth)) {
			rightLaneChangeFlag_ = false;
		}
	}

	// 行列を計算し転送
	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();

	// 生きている時間が限界に達したら消す
	if (lifeTimer >= lifeInterval) {
		isDead_ = true;
	}
}

void Enemy::Lane1ChangeCheck(Vector3& pos)
{
	Vector3 pos_ = worldTransform_.translation_;

	// 一番左側のレーンにいた場合の車線変更
	if (pos_.x == pos.x) {
		if (pos_.x <= -2 * loadWidth) {
			if (pos_.z <= pos.z + laneRadius && pos_.z > pos.z) {
				lane1ChangeFlag_ = true;
			}
		}
	}
}

void Enemy::Lane5ChangeCheck(Vector3& pos)
{
	Vector3 pos_ = worldTransform_.translation_;

	// 一番右側のレーンにいた場合の車線変更
	if (pos_.x == pos.x) {
		if (pos_.x >= 2 * loadWidth) {
			if (pos_.z <= pos.z + laneRadius && pos_.z > pos.z) {
				lane5ChangeFlag_ = true;
			}
		}
	}
}

void Enemy::LaneChangeCheck(Vector3& pos)
{
	Vector3 pos_ = worldTransform_.translation_;

	if (pos_.x == pos.x) {
		if (pos.z <= pos_.z + laneRadius && pos.z > pos_.z) {
			laneChangeFlag_ = true;
		}
	}
	
}

void Enemy::LeftLaneChangeCheck(Vector3& pos)
{
	Vector3 leftpos = { worldTransform_.translation_.x - (1 * loadWidth),worldTransform_.translation_.y,worldTransform_.translation_.z };
	if (leftpos.z += laneRadius <= pos.z) {
		leftLaneChangeFlag_ = true;
	}
}

void Enemy::RightLaneChangeCheck(Vector3& pos)
{
	Vector3 rightpos = { worldTransform_.translation_.x + (1 * loadWidth),worldTransform_.translation_.y,worldTransform_.translation_.z };
	if (rightpos.z += laneRadius <= pos.z) {
		rightLaneChangeFlag_ = true;
	}
}

void Enemy::SetWouldTransform(WorldTransform worldTransform)
{
	worldTransform_ = worldTransform;
}

void Enemy::Draw(const ViewProjection& viewProjection)
{
	//if (isDead_ == false) {
		model_->Draw(worldTransform_, viewProjection);
	//}
}
