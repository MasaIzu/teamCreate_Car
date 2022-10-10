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
    bool boxCollision(Vector3 player, Vector3 enemy, float playerWidthX, float playerWidthZ, float playerHight, float enemyWidthX, float enemyWidthZ, float enemyHight);

    void Contact(int playerMove ,Vector3 player,WorldTransform enemy);
private:
    //���[���h�ϊ��f�[�^
    WorldTransform worldTransform;

    DebugText* debugText = nullptr;
    //���f��
    Model* model = nullptr;
    //���f��
    Model* enemyBulletModel = nullptr;

    
};
