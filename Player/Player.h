#pragma once
#include"DebugText.h"

class Player {

public:
    Player();

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
    void Draw();

    /// <summary>
    /// スピードゲッター
    /// </summary>
    float GetPlayerSpeed();

    /// <summary>
    /// 時速のゲッター
    /// </summary>
    float GetKmH();


private:

    DebugText* debugText_ = nullptr;

    //メンバ変数
    float playerSpeed;
    float playerMaxAccelerator;
    float playerJumpSpeed;

    float kmH;//km/h 時速

    int jumpFlag;




};