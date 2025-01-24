//=====================================================
//
//���[�V�����t���̓G�̃N���X�Ǘ�[enemyinmotion.h]
//Auther;Haruki Chiba
//
//=====================================================

#pragma once


//=====================================================
//�C���N���[�h
#include "enemycharacter.h"


//================================================================================
//���[�V�����G�̃}�l�[�W���[�Ǘ��N���X
class CManagerEnemyInMotion : public CEnemyCharacter
{
public: //�A�N�Z�X�\

	CManagerEnemyInMotion(int nPriority = DEFAULT_PRIORITY1);   //�R���X�g���N�^
	~CManagerEnemyInMotion()override;                           //�f�X�g���N�^
	HRESULT Init()override;                                     //����������
	void Uninit()override;                                      //�j������
	void Update() override;                                     //�X�V����
	void Draw()override;                                        //�`�揈��

	static CManagerEnemyInMotion* Create(D3DXVECTOR3 pos,CObjectX::TYPE type);      //��������

protected:
	int m_nJumpFrame;    //��Ԃ܂ł̎���
	int JumpNumber;      //�s��������Ԃ悤�ɔԍ�������ׂ̕ϐ�
	int JumpRecastTime;  //��Ԉׂ̃��L���X�g�^�C���i�A���ŐG��Ă��锻��ɂȂ�ׂ��̏C���j

	//�}�N����`
	constexpr static float MAX_SPEED = 2.0f;     //�ǂ������鑬�x
	constexpr static int MAX_BUULET_SPEED = 30;  //�e�̑���

};


//================================================================================
//���[�V�����t���̓G�i�ʏ�j
class CEnemyInMotion : public CManagerEnemyInMotion
{
public: //�A�N�Z�X�\
	CEnemyInMotion(int nPriority = DEFAULT_PRIORITY1);   //�R���X�g���N�^
	~CEnemyInMotion()override;                           //�f�X�g���N�^
	void Update() override;                              //�X�V����

private:
	constexpr static int MAX_FRAME_BUULET = 60;          //�e�����܂ł̎���
	constexpr static int MAX_FRAME_JUMP = 20;            //��Ԃ܂ł̎���
};


//================================================================================
//���[�V�����t���̓G�i����j
class CEnemyInMotion001 : public CManagerEnemyInMotion
{
public: //�A�N�Z�X�\
	CEnemyInMotion001(int nPriority = DEFAULT_PRIORITY1);   //�R���X�g���N�^
	~CEnemyInMotion001()override;                           //�f�X�g���N�^
	void Update() override;                                 //�X�V����
	void AdjustmentBulletAndRot();                          //�v���C���[�ɑ΂���@�̂ƒe�̒�������
	void WhenCollisionBlock();                              //�n�ʗp�u���b�N�ɐG��Ă��鎞�̏���
	void Correctionrot();                                   //�������C������֐�
	void PlayerBloWwaway();

private:
	//�}�N����`
	constexpr static int MAX_LIFE = 10;                                //���C�t�̍ő�l
	constexpr static int PLUS_SCORE = 2000;                            //�X�R�A�̉��Z�l
	constexpr static int MIN_RANDOM1 = 250;                            //����1�̍ŏ��l
	constexpr static int MAX_RANDOM1 = 250;                            //����1�̍ő�l
	constexpr static int MIN_RANDOM2 = 50;                             //����2�̍ŏ��l
	constexpr static int MAX_RANDOM2 = 50;                             //����2�̍ő�l
													                   
	constexpr static float ADDJUST_PRTAS_ROTX = 0.01f;                 //�p�[�c��X���̌����𒲐�����l
	constexpr static float ADDJUST_BULLET_ROTY = 0.3f;                 //�e��Y���̌����𒲐�����l
	constexpr static float MULTIPLICATIOB_ADDJUST_BULLET_ROTY = 4.0f;  //�e��Y���̌����𒲐�����|���Z�̒l
	constexpr static float IF_ADDJUST_BULLET_ROTY = 3.0f;              //�e��Y���̌����𒲐�����������̊|���Z�̒l
	constexpr static float MAX_EXPLOSION_SIZE1 = 200.0f;               //�����G�t�F�N�g�̑傫���̒l�P
	constexpr static float MAX_EXPLOSION_SIZE2 = 300.0f;               //�����G�t�F�N�g�̑傫���̒l�Q
	constexpr static float MAX_DAMAGE = 0.1f;                          //�_���[�W��

	int m_nHitFrame; //�v���C���[�Ɠ����������̃��L���X�g�^�C��
	bool m_bHit;     //�����������ǂ����̔���p�ϐ�
};
