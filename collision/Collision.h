#pragma once
#include "WorldTransform.h"
#include "Model.h"
#include <cassert>
#include "DebugText.h"
#include "Input.h"
#include "ViewProjection.h"
#include <memory>
#include <list>

class collision {
public:
    //プレイヤーとエネミーの座標を入る
    //プレイヤーの半径をx,y,zの順に入れる
    //エネミーの半径をx,y,zの順に入れる
    bool boxCollision(Vector3 player, Vector3 enemy, Vector3 playerWidth,Vector3 enemyWidth);
    bool boxCollision(Vector3 player, Vector3 enemy, Vector3 playerWidth, Vector3 enemyWidth,bool flag);

    void Contact(int playerMove ,Vector3 player,WorldTransform enemy,Vector3 enemyRotationMove, Vector3 enemyMove);
private:
    //ワールド変換データ
    WorldTransform worldTransform;

    DebugText* debugText = nullptr;
    //モデル
    Model* model = nullptr;
    //モデル
    Model* enemyBulletModel = nullptr;

    
};
