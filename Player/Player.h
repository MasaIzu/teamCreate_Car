#pragma once
#include"Model.h"
#include"WorldTransform.h"
#include"ViewProjection.h"
#include"Input.h"
#include"Vector3.h"
#include"Affin.h"
#include"Collision.h"

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
    /// �����X�V
    /// </summary>
    void PlayerMove();

    /// <summary>
    /// �Ԃ̌��ɂ������̏���
    /// </summary>
    void EnemyCarBack();

    /// <summary>
    /// �ԂƎԂ̏Փˎ�����
    /// </summary>
    void TrafficAccident();

    /// <summary>
    /// �ԂƎԂ̏Փˎ�����(�t���O����)
    /// </summary>
    void TrafficAccidentFlag();

    /// <summary>
    /// �n�܂������̃J�E���g�_�E��
    /// </summary>
    void countDown();

    /// <summary>
    /// �X�s�[�h�ɂ��ʒu����
    /// </summary>
    void SpeedAccordingPosition();



public://�Q�b�^�[

    /// <summary>
    /// �X�s�[�h�Q�b�^�[
    /// </summary>
    Vector3 GetPlayerPos();

    /// <summary>
    /// �X�s�[�h�Q�b�^�[
    /// </summary>
    float GetPlayerSpeed();

    /// <summary>
    /// �����̃Q�b�^�[
    /// </summary>
    float GetKmH();

    /// <summary>
    /// �����Ă�t���O
    /// </summary>
    int GetMovingFlag();

    /// <summary>
    /// �ǂ������Z�b�g
    /// </summary>
    void SetOverTakingCount(int count);

    /// <summary>
    /// �X�^�[�g�^�C�}�[�擾
    /// </summary>
    int GetTimer();

private:
    //���[���h�ϊ��f�[�^
    WorldTransform worldTransform_;

    Input* input_ = nullptr;
    Model* model_ = nullptr;
    collision* collision_ = nullptr;


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
    int moving;
    float nextPos;

    float enemyBackSpeed;

    float playerSideMove;
    int timer;
    int accidentFlag;

    float saveSpeed;
    int saveSpeedFlag;
    int overTakingCount;
    int speedTimer;

    int bustFlag;
    float bustMax;
};