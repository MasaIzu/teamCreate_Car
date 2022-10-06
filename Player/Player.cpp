#include "Player.h"

Player::Player(){
    playerSpeed = 3.0f;
    playerJumpSpeed = 0;
    playerMaxAccelerator = 12.5f;
    jumpFlag = 0;
    kmH = 0;

    debugText_ = DebugText::GetInstance();
}

Player::~Player(){
    delete model_;
}

void Player::Initialize(){
    playerSpeed = 3.0f;
    playerJumpSpeed = 0;
    playerMaxAccelerator = 12.5f;
    jumpFlag = 0;
    kmH = 0;


}

void Player::Updata(){
    if (playerSpeed < playerMaxAccelerator) {
        playerSpeed += 0.1;
        kmH = playerSpeed * 20;

    }
    debugText_->SetPos(50, 70);
    debugText_->Printf(
        "speed:(%f,%f)", playerSpeed, kmH);

}

void Player::Draw(){


}

float Player::GetPlayerSpeed(){


    return playerSpeed;
}

float Player::GetKmH()
{
    return kmH;
}
