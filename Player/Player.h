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
    /// ������
    /// </summary>
    void Initialize();

    /// <summary>
    /// �X�V
    /// </summary>
    void Updata();

    /// <summary>
    /// �`��
    /// </summary>
    void Draw(ViewProjection viewProjection_);

    /// <summary>
    /// �X�s�[�h�Q�b�^�[
    /// </summary>
    float GetPlayerSpeed();

    /// <summary>
    /// �����̃Q�b�^�[
    /// </summary>
    float GetKmH();

    /// <summary>
    /// ���W�̃Q�b�^�[
    /// </summary>
    Vector3 GetWorld();


private:
    //���[���h�ϊ��f�[�^
    WorldTransform worldTransform_;

    DebugText* debugText_ = nullptr;
    Input* input_ = nullptr;
    Model* model_ = nullptr;


    //�����o�ϐ�
    float playerSpeed;
    float playerMaxAccelerator;
    float playerJumpSpeed;

    float kmH;//km/h ����
    float gravity;

    int jumpFlag;
    int junpFrame;

    int leftFlag;
    int rightFlag;
    float nextPos;

    float playerSideMove;


};