#include "Player.h"

Player::Player() {
	playerSpeed = 1.0f;
	playerJumpSpeed = 0;
	playerMaxAccelerator = 16.0f;
	jumpFlag = 0;
	kmH = 0;
	gravity = 6.0f;
	junpFrame = 0;

	leftFlag = 0;
	rightFlag = 0;
	nextPos = 0;
	playerSideMove = 1.0;


	//ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = { -1, 0, 0 };
	worldTransform_.scale_ = { 5,5,5 };
	
	//行列更新
	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();

	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	model_ = Model::Create();

}

Player::~Player() {
	delete model_;
}

void Player::Initialize() {
	playerSpeed = 1.0f;
	playerJumpSpeed = 0;
	playerMaxAccelerator = 5.0f;
	jumpFlag = 0;
	kmH = 0;
	gravity = 9.0f;
	junpFrame = 0;

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();

}

void Player::Updata() {

	//だんだんと動くスピードを上げる
	if (playerSpeed < playerMaxAccelerator) {
		playerSpeed += 0.05f;
		kmH = playerSpeed * 25;
	}
	//スペース押されたらジャンプ
	if (input_->TriggerKey(DIK_SPACE)) {
		jumpFlag = 1;
	}
	if (jumpFlag == 1) {
		//ジャンプフレーム
		junpFrame++;
		playerJumpSpeed = 1.5f - gravity * (static_cast<float>(junpFrame) / 120.0f);
		worldTransform_.translation_.y += playerJumpSpeed;
	}

	//0から下にいかないように
	if (worldTransform_.translation_.y < 0) {
		playerJumpSpeed = 0;
		junpFrame = 0;
		worldTransform_.translation_.y = 0;
		jumpFlag = 0;
	}


	//車線変更 左
	if (jumpFlag == 0) {
		if (input_->TriggerKey(DIK_LEFT)) {
			if (nextPos > -37) {
				nextPos -= 18.5;
			}
		}
		//車線変更 右
		if (input_->TriggerKey(DIK_RIGHT)) {
			if (nextPos < 37) {
				nextPos += 18.5;
			}
		}
	}
	//横移動
	if (worldTransform_.translation_.x > nextPos) {
		worldTransform_.translation_.x -= playerSideMove;
	}
	if (worldTransform_.translation_.x < nextPos) {
		worldTransform_.translation_.x += playerSideMove;
	}





	debugText_->SetPos(50, 70);
	debugText_->Printf(
		"speed:(%f,%f)", nextPos, worldTransform_.translation_.x);


	//行列更新
	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection viewProjection_) {

	model_->Draw(worldTransform_, viewProjection_);

}

float Player::GetPlayerSpeed() {
	return playerSpeed;
}

float Player::GetKmH() {
	return kmH;
}
