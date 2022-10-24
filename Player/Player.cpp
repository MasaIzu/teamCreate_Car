#include "Player.h"

Player::Player() {
	playerSpeed = 1.0f;
	playerJumpSpeed = 0;
	playerMaxAccelerator = 9.0f;
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

	saveSpeed = 0;
	saveSpeedFlag = 0;
	speedTimer = 2;

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0, 0, -50 };
	worldTransform_.scale_ = { 5,5,5 };
	
	//�s��X�V
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

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();

}

void Player::Updata() {
	countDown();
	if (timer == 0) {
		PlayerMove();
	}
	TrafficAccident();
	SpeedAccordingPosition();
}

void Player::Draw(ViewProjection viewProjection_) {

	model_->Draw(worldTransform_, viewProjection_);

}

void Player::PlayerMove(){

	//���񂾂�Ɠ����X�s�[�h���グ��
	if (speedTimer == 0) {
		if (playerSpeed < playerMaxAccelerator) {
			playerSpeed += 0.05f;
			speedTimer = 2;
		}
	}
	
	
	//�X�y�[�X�����ꂽ��W�����v
	if (input_->TriggerKey(DIK_SPACE)) {
		jumpFlag = 1;
	}
	if (jumpFlag == 1) {
		//�W�����v�t���[��
		junpFrame++;
		playerJumpSpeed = 1.3f - gravity * (static_cast<float>(junpFrame) / 100.0f);
		worldTransform_.translation_.y += playerJumpSpeed;
	}

	//0���牺�ɂ����Ȃ��悤��
	if (worldTransform_.translation_.y < 0) {
		playerJumpSpeed = 0;
		junpFrame = 0;
		worldTransform_.translation_.y = 0;
		jumpFlag = 0;
	}


	//�Ԑ��ύX ��
	if (jumpFlag == 0) {
		if (input_->TriggerKey(DIK_LEFT)) {
			moving = -1;
			if (nextPos > -37) {
				nextPos -= 18.5;
			}
		}
		//�Ԑ��ύX �E
		if (input_->TriggerKey(DIK_RIGHT)) {
			moving = 1;
			if (nextPos < 37) {
				nextPos += 18.5;
			}
		}
	}
	//���ړ�
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
		"speed:(%d,%f)", overTakingCount, playerSpeed);


	//�s��X�V
	AffinTrans::affin(worldTransform_);
	worldTransform_.TransferMatrix();

}

void Player::EnemyCarBack(){

	if (playerSpeed < 16) {
		playerSpeed += 0.016;
	}
}

void Player::TrafficAccident(){
	if (accidentFlag == 1) {
		if (saveSpeedFlag == 0) {
			saveSpeedFlag = 1;
			saveSpeed = 0;
			if (playerSpeed > 8) {
				saveSpeed = (playerSpeed - 7);
			}
		}
		if (playerSpeed > 2 + saveSpeed) {
			playerSpeed -= 0.4;
		}
		else {
			accidentFlag = 0;
			saveSpeedFlag = 0;
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
	if (speedTimer > 0) {
		speedTimer--;
	}
}

void Player::SpeedAccordingPosition(){
	worldTransform_.translation_ = { worldTransform_.translation_.x, worldTransform_.translation_.y, -55 };
	worldTransform_.translation_.z +=  playerSpeed * 5;

}

Vector3 Player::GetPlayerPos(){

	//���[���h���W������ϐ�
	Vector3 worldPos;
	//���[���h�s��ړ��������擾(���[���h���W)
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

void Player::SetOverTakingCount(int count) {

	overTakingCount = count;

}