#pragma once
#include"DebugText.h"
#include"Model.h"
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"Input.h"
#include"Vector3.h"
#include"Affin.h"

class Player {

public:
    Player();
    ~Player();

    /// <summary>
    /// 初期化
    /// </summary>
    void Initialize();

    /// <summary>
    /// 更新
    /// </summary>
    void Updata();

    /// <summary>
    /// 描画
    /// </summary>
    void Draw(ViewProjection viewProjection_);

    /// <summary>
    /// スピードゲッター
    /// </summary>
    float GetPlayerSpeed();

    /// <summary>
    /// 時速のゲッター
    /// </summary>
    float GetKmH();

    /// <summary>
    /// 座標のゲッター
    /// </summary>
    Vector3 GetWorld();


private:
    //ワールド変換データ
    WorldTransform worldTransform_;

    DebugText* debugText_ = nullptr;
    Input* input_ = nullptr;
    Model* model_ = nullptr;


    //メンバ変数
    float playerSpeed;
    float playerMaxAccelerator;
    float playerJumpSpeed;

    float kmH;//km/h 時速
    float gravity;

    int jumpFlag;
    int junpFrame;

    int leftFlag;
    int rightFlag;
    float nextPos;

    float playerSideMove;


};