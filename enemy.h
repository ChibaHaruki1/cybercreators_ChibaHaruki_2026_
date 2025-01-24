//==================================
//
//�G�̃N���X�Ǘ�[enemy.h]
//Auther:Chiba Haruki
//
//==================================

#pragma once

//==================================
//�C���N���[�h
#include "objectX.h"
#include "enemycharacter.h"


//==========================================================
//�G�̃}�l�[�W���[�Ǘ��N���X
class CManagerEnemy : public CObjectX
{
public:
	CManagerEnemy(int nPriority = CObject::DEFAULT_PRIORITY);   //�����t���R���X�g���N�^
	~CManagerEnemy()override;                          //�f�X�g���N�^
	HRESULT Init()override;                            //����������
	void Uninit()override;                             //�I������
	void Update() override;                            //�X�V����
	void Draw()override;                               //�`�揈��
	static CManagerEnemy* Create(D3DXVECTOR3 pos, CObjectX::TYPE type); //��������
};


//==========================================================
//�G�̃N���X
class CEnemyX : public CManagerEnemy
{
public:
	CEnemyX(int nPriority = DEFAULT_PRIORITY1);  //�R���X�g���N�^
	~CEnemyX()override;                          //�f�X�g���N�^
	void Update()override;                       //�X�V����

private:
	//�}�N����`
	constexpr  static int MAX_LIFE = 3;                //���C�t�̍ő�l
	constexpr  static int PLUS_SCORE = 1000;           //���Z����X�R�A�l
	constexpr  static float m_fMAX_SPPED = 2.0f;       //�ړ����x
	constexpr  static float MAX_ENEMY_DAMAGE = 0.001f; //�_���[�W��
	constexpr static int MAX_BUULET_SPEED = 30;        //�e�̑���
	constexpr static int SET_BULLET_LIFE = 120;        //���C�t�̍ő吔
};


//==========================================================
//�G001�̃N���X
class CEnemy001X : public CManagerEnemy
{
public:
	CEnemy001X(int nPriority = DEFAULT_PRIORITY1);  //�R���X�g���N�^
	~CEnemy001X()override; 							//�f�X�g���N�^
	void Update()override;							//�X�V����


	//=======================
	//�}�N����`
	constexpr static int MAX__ENEMY001_LIFE = 3;   //���C�t�̍ő�l
	
private:
	//�}�N����`
	constexpr static int PLUS_SCORE = 100;         //�X�R�A�̉��Z�l
	constexpr static float MAX_DAMAGE = 0.005f;    //�v���C���[�ɗ^����_���[�W��
	constexpr static float PLUS_ROTY = 0.1f;       //Y���̌��������Z����l
};


//==========================================================
//�G002�̃N���X
class CEnemy002X : public CManagerEnemy
{
public:
	CEnemy002X(int nPriority = DEFAULT_PRIORITY1);  //�R���X�g���N�^
	~CEnemy002X()override; 							//�f�X�g���N�^
	void Update()override;							//�X�V����
	void Move();                                    //�s������


	//=======================
	//�}�N����`
	constexpr static int MAX__ENEMY002_LIFE = 3;   //���C�t�̍ő�l


private:
	//�}�N����`
	constexpr static int PLUS_SCORE = 200;         //�X�R�A�̉��Z�l
	constexpr static float MAX_DAMAGE = 0.005f;    //�v���C���[�ɗ^����_���[�W��
	constexpr static float PLUS_ROTY = 0.1f;       //Y���̌��������Z����l
	constexpr static float ADDJUST_POSY = 10.0f;    //Y���̈ʒu�����Z����l
};
