#include "Player.h"

Player::Player(){
    playerSpeed = 0;
    playerJumpSpeed = 0;
    playerMaxAccelerator = 50;
    jumpFlag = 0;
    kmH = 0;

    debugText_ = DebugText::GetInstance();
}

void Player::Initialize(){
    playerSpeed = 0;
    playerJumpSpeed = 0;
    playerMaxAccelerator = 50;
    jumpFlag = 0;
    kmH = 0;


}

void Player::Updata(){
    if (playerSpeed < playerMaxAccelerator) {
        playerSpeed += 0.2;
        kmH = playerSpeed * 5;

    }


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
