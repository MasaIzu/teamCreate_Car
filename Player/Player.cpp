#include "Player.h"

Player::Player(){
    playerSpeed = 3.0f;
    playerJumpSpeed = 0;
    playerMaxAccelerator = 12.5f;
    jumpFlag = 0;
    kmH = 0;
    gravity = 6.0f;
    junpFrame = 0;

    //ワールド変換の初期化
    worldTransform_.Initialize();
    worldTransform_.translation_ = { 0, 0, 0 };
    //行列更新
    AffinTrans::affin(worldTransform_);
    worldTransform_.TransferMatrix();

    input_ = Input::GetInstance();
    debugText_ = DebugText::GetInstance();

    model_ = Model::Create();

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
    gravity = 9.0f;
    junpFrame = 0;

    //ワールドトランスフォームの初期化
    worldTransform_.Initialize();

}

void Player::Updata(){

    if (playerSpeed < playerMaxAccelerator) {
        playerSpeed += 0.1f;
        kmH = playerSpeed * 20;

    }
    if (input_->TriggerKey(DIK_SPACE)) {
        jumpFlag = 1;
    }
    if (jumpFlag == 1) {
        //ジャンプフレーム
        junpFrame++;
        playerJumpSpeed = 0.8f - gravity * (static_cast<float>(junpFrame) / 150.0f);
        worldTransform_.translation_.y += playerJumpSpeed;
    }

    if (worldTransform_.translation_.y < 0) {
        playerJumpSpeed = 0;
        junpFrame = 0;
        worldTransform_.translation_.y = 0;
        jumpFlag = 0;
    }

   

    debugText_->SetPos(50, 70);
    debugText_->Printf(
        "speed:(%f,%f)", playerSpeed, kmH);


    //行列更新
    AffinTrans::affin(worldTransform_);
    worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection viewProjection_){

    model_->Draw(worldTransform_, viewProjection_);

}

float Player::GetPlayerSpeed(){
    return playerSpeed;
}

float Player::GetKmH(){
    return kmH;
}
