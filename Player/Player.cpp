#include "Player.h"

Player::Player() {
	playerSpeed = 1.0f;
	playerJumpSpeed = 0;
	playerMaxAccelerator = 8.0f;
	jumpFlag = 0;
	kmH = 0;
	gravity = 6.0f;
	junpFrame = 0;

	leftFlag = 0;
	rightFlag = 0;
	nextPos = 0;
	playerSideMove = 1.0;

	moving = 0;
	enemyBackSpeed = 0;
	timer = 180;
	accidentFlag = 0;

	//ワールド変換の初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0, 0, -50 };
	worldTransform_.scale_ = { 5,5,5 };
	
	//行列更新
	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();

	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	model_ = Model::Create();
	collision_ = new collision();
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
	countDown();
	if (timer == 0) {
		PlayerMove();
	}
	SpeedAccordingPosition();
}

void Player::Draw(ViewProjection viewProjection_) {

	model_->Draw(worldTransform_, viewProjection_);

}

void Player::PlayerMove(){

	//だんだんと動くスピードを上げる
	if (playerSpeed < playerMaxAccelerator) {
		playerSpeed += 0.05f;
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
			moving = -1;
			if (nextPos > -37) {
				nextPos -= 18.5;
			}
		}
		//車線変更 右
		if (input_->TriggerKey(DIK_RIGHT)) {
			moving = 1;
			if (nextPos < 37) {
				nextPos += 18.5;
			}
		}
	}
	//横移動
	int nowMoving = 0;
	if (moving == -1) {
		if (worldTransform_.translation_.x > nextPos) {
			worldTransform_.translation_.x -= playerSideMove;
			nowMoving = -1;
		}
	}
	else if (moving == 1) {
		if (worldTransform_.translation_.x < nextPos) {
			worldTransform_.translation_.x += playerSideMove;
			nowMoving = 1;
		}
	}

	moving = nowMoving;

	kmH = playerSpeed * 25;

	debugText_->SetPos(50, 70);
	debugText_->Printf(
		"speed:(%f,%f)", playerSpeed, kmH);


	//行列更新
	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();

}

void Player::EnemyCarBack(){

	if (playerSpeed < 16) {
		playerSpeed += 0.01;
	}
}

void Player::TrafficAccident(){
	if (accidentFlag == 1) {
		if (playerSpeed > 2) {
			playerSpeed -= 0.5;
		}
		else {
			accidentFlag = 0;
		}
	}
}

void Player::TrafficAccidentFlag(){
	accidentFlag = 1;
}

void Player::countDown(){
	if (timer > 0) {
		timer--;
	}
}

void Player::SpeedAccordingPosition(){
	worldTransform_.translation_ = { worldTransform_.translation_.x, worldTransform_.translation_.y, -55 };
	worldTransform_.translation_.z +=  playerSpeed * 5;

}

Vector3 Player::GetPlayerPos(){

	//ワールド座標を入れる変数
	Vector3 worldPos;
	//ワールド行列移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

float Player::GetPlayerSpeed() {
	return playerSpeed;
}

float Player::GetKmH() {
	return kmH;
}

int Player::GetMovingFlag()
{
	return moving;
}
