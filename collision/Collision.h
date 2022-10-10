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
    //�v���C���[�ƃG�l�~�[�̍��W�����
    //�v���C���[�̔��a��x,y,z�̏��ɓ����
    //�G�l�~�[�̔��a��x,y,z�̏��ɓ����
    bool boxCollision(Vector3 player, Vector3 enemy, Vector3 playerWidth,Vector3 enemyWidth);
    bool boxCollision(Vector3 player, Vector3 enemy, Vector3 playerWidth, Vector3 enemyWidth,bool flag);

    void Contact(int playerMove ,Vector3 player,WorldTransform enemy,Vector3 enemyRotationMove, Vector3 enemyMove);
private:
    //���[���h�ϊ��f�[�^
    WorldTransform worldTransform;

    DebugText* debugText = nullptr;
    //���f��
    Model* model = nullptr;
    //���f��
    Model* enemyBulletModel = nullptr;

    
};
