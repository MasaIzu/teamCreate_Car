#pragma once
#include"DebugText.h"
#include"Model.h"

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
    void Draw();

    /// <summary>
    /// �X�s�[�h�Q�b�^�[
    /// </summary>
    float GetPlayerSpeed();

    /// <summary>
    /// �����̃Q�b�^�[
    /// </summary>
    float GetKmH();


private:

    DebugText* debugText_ = nullptr;
    Model* model_ = nullptr;


    //�����o�ϐ�
    float playerSpeed;
    float playerMaxAccelerator;
    float playerJumpSpeed;

    float kmH;//km/h ����

    int jumpFlag;




};