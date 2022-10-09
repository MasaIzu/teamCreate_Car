#include "Player.h"

Player::Player() {
	playerSpeed = 3.0f;
	playerJumpSpeed = 0;
	playerMaxAccelerator = 12.5f;
	jumpFlag = 0;
	kmH = 0;
	gravity = 6.0f;
	junpFrame = 0;

	leftFlag = 0;
	rightFlag = 0;
	nextPos = 0;
	playerSideMove = 0.02;


	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
	worldTransform_.translation_ = { 0, 0, 0 };
	//�s��X�V
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
	playerSpeed = 3.0f;
	playerJumpSpeed = 0;
	playerMaxAccelerator = 12.5f;
	jumpFlag = 0;
	kmH = 0;
	gravity = 9.0f;
	junpFrame = 0;

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();

}

void Player::Updata() {

	//���񂾂�Ɠ����X�s�[�h���グ��
	if (playerSpeed < playerMaxAccelerator) {
		playerSpeed += 0.1f;
		kmH = playerSpeed * 20;
	}
	//�X�y�[�X�����ꂽ��W�����v
	if (input_->TriggerKey(DIK_SPACE)) {
		jumpFlag = 1;
	}
	if (jumpFlag == 1) {
		//�W�����v�t���[��
		junpFrame++;
		playerJumpSpeed = 0.8f - gravity * (static_cast<float>(junpFrame) / 150.0f);
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
	if (input_->TriggerKey(DIK_LEFT)) {
		if (nextPos > -4) {
			nextPos -= 2;
		}
	}
	//�Ԑ��ύX �E
	if (input_->TriggerKey(DIK_RIGHT)) {
		if (nextPos < 4) {
			nextPos += 2;
		}
	}
	//���ړ�
	if (worldTransform_.translation_.x > nextPos) {
		worldTransform_.translation_.x -= playerSideMove;
	}
	if (worldTransform_.translation_.x < nextPos) {
		worldTransform_.translation_.x += playerSideMove;
	}





	debugText_->SetPos(50, 70);
	debugText_->Printf(
		"speed:(%f,%f)", nextPos, worldTransform_.translation_.x);


	//�s��X�V
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
