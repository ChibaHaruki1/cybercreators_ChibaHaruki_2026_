//=====================================
//
//�Q�[�W�Ɋւ���N���X[gage.h]
//Auther:Haruki Chiba
//
//=====================================

#pragma once

//=====================================
//�C���N���[�h
#include "object2D.h"
#include "object3D.h"

//==================================================
//�R���Q�[�W
class CFuelGage : public CObject3D
{
public:
	CFuelGage(int nPriority = DEFAULT_PRIORITY);          //�R���X�g���N�^;
	~CFuelGage();                                         //�R���X�g���N�^;
	HRESULT Init()override;                               //����������
	void Uninit()override;                                //�j������
	void Update()override;                                //�X�V����
	void Draw()override;                                  //�`�揈��

	static CFuelGage* Create();                           //��������

	inline bool& GetUse() { return m_bUse; }              //�g���Ă��邩�ǂ����̔�����擾����
	inline bool& GetChage() { return m_bCharge; }         //�`���[�W���������Ă���ǂ����̔�����擾����

private:
	//�}�N����`
	constexpr static int RED = 255;          //�ԐF
	constexpr static int GREEN = 255;        //�ΐF
	constexpr static int BLUE = 255;         //�F
	constexpr static int MAX_ALPHA = 255;    //�A���t�@�l�̍ő吔
	constexpr static int MIN_ALPHA = 10;     //�A���t�@�l�̍ŏ���
	constexpr static int MINUS_ALPHA = 5;    //�A���t�@�l�̌��Z�l

	constexpr static float MAX_SIZEX = 15.0f;             //X�̂̑傫��
	constexpr static float MAX_SIZEY = 100.0f;            //Y���̑傫��
	constexpr static float MAX_SIZEZ = 20.0f;             //Z���̑傫��
	constexpr static float MIN_SIZEY = 10.0f;             //Y���̍ŏ��l
	constexpr static float ADDJUST_POSX = 50.0f;          //X���̈ʒu�̒����l
	constexpr static float ADDJUST_POSY = 80.0f;          //Y���̈ʒu�̒����l
	constexpr static float MAX_MAINAS_GAGESPEED = 0.5f;   //�Q�[�W�̌��鑬��
	constexpr static float MAX_PLUS_GAGESPEED = 0.5f;     //�Q�[�W�̑����鑬��
	constexpr static float MAX_PLUS_PLAYER_MOVE = 1.0f;   //�v���C���[�ړ��ʂ̑����鑬��
	constexpr static float MAX_PLAYER_GRAVITY = 1.0f;     //�v���C���[�̏d�͂̌��E�l


	bool m_bUse;                                          //�Q�[�W�����炷���ǂ������肷�邽�߂̕ϐ�
	bool m_bCharge;
};


//==================================================
//�Q�[�W�̊Ǘ��N���X
//==================================================
class CManagerGage : public CObject2D
{
public:  //�A�N�Z�X�\
	CManagerGage(int nPriority = DEFAULT_PRIORITY);           //�R���X�g���N�^;
	~CManagerGage()override;                                  //�f�X�g���N�^
	HRESULT Init()override;                                   //����������
	void Uninit()override;                                    //�j������
	void  Update()override;                                   //�X�V����
	void Draw()override;                                      //�`�揈��
	static CManagerGage* Create(CObject2D::TYPE type);        //�Q�[�W�̐���
	static CManagerGage* CreateLeave(CObject2D::TYPE type);   //�c���Q�[�W�̐���


	//===================================
	//���̎擾
	//�ibullet.cpp�ȂǂŌ��炷�j
	float& GetPlayerHPSizeX() { return m_fHPSizeX; }          //�v���C���[��HP�Q�[�W���擾
	float& GetBossHPSizeX() { return m_fBossHPSizeX; }        //�{�X��HP�Q�[�W���擾
	float& GetSaveSizeX() { return m_fSaveSizeX; }            //�Q�[�W�̕ۊǂ��擾


	//========================
	//�}�N����`
	constexpr static float MAX_PLAYER_HP_SIZE = 400.0f;   //�v���C���[�̃Q�[�W�ő吔


protected://�p���N���X�̂݃A�N�Z�X�\
	float m_fSaveSizeX;


	//===================================
	//�}�N����`
	constexpr static float MAX_PLAYERGAGE_SIZE_Y = 40.0f; //�v���C���[�̃Q�[�W��Y���̑傫��
	constexpr static float MAX_PLAYERGAGE_SIZE_Z = 70.0f; //�v���C���[�̃Q�[�W��Z���̑傫��

private:  //�A�N�Z�X�s�\

	float m_fHPSizeX;      //�v���C���[��HP�Q�[�W�̑傫�����Ǘ�����p�̕ϐ�
	float m_fBossHPSizeX;  //�{�X��HP�Q�[�W�̑傫�����Ǘ�����p�̕ϐ�
};


//==================================================
//�v���C���[��HP�Q�[�W
class CPlayerHPGage : public CManagerGage
{
public:
	CPlayerHPGage(int nPriority = DEFAULT_PRIORITY);   //�R���X�g���N�^
	~CPlayerHPGage()override;                          //�f�X�g���N�^
	HRESULT Init()override;                            //����������
	void Update()override;                             //�X�V����

private:
	//�}�N����`
	constexpr static float MINUS_HPSIZEX = 1.8f;       //HP�Q�[�W�̌��Z�l
};
	

//==================================================
//�{�X��HP�Q�[�W
class CBossHPGage : public CManagerGage
{
public:
	CBossHPGage(int nPriority = DEFAULT_PRIORITY);     //�R���X�g���N�^
	~CBossHPGage()override;                            //�f�X�g���N�^
	HRESULT Init()override;                            //����������
	void Update()override;                             //�X�V����

private:
	//�}�N����`
	constexpr static float ADDJUST_POSY = 40.0f;       //Y���̈ʒu�̒����l
	constexpr static float MINUS_HPSIZEX = 1.3f;       //HP�Q�[�W�̌��Z�l
};


//==================================================
//�v���C���[��HP�Q�[�W���c��
class CPlayerHPGageLeave : public CManagerGage
{
public:
	CPlayerHPGageLeave(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CPlayerHPGageLeave()override;                         //�f�X�g���N�^
	HRESULT Init()override;                                //����������
};


//==================================================
//�{�X��HP�Q�[�W���c��
class CBossHPGageLeave : public CManagerGage
{
public:
	CBossHPGageLeave(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CBossHPGageLeave()override;                         //�f�X�g���N�^
	HRESULT Init()override;                              //����������
};

