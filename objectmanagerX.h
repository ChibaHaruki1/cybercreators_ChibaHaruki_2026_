//========================================
//
//�I�u�W�F�N�g�N���X�Ǘ�[object.h]
//Auther:Chiba Haruki
//
//========================================

#pragma once

//========================================
//�C���N���[�h
#include "main.h"


//�S�Ă��Ǘ�����̂ŉ��z�֐��i�������z�֐��j
class CObjectManagerX
{
public:

	//�e�^�C�v�̐ݒ�
	enum class TYPE
	{
		NONE = 0,                    //����
		ENEMY,                       //�G
		ENEMY001,                    //�G001
		ENEMY002,                    //�G002
		ENEMYINMOTION,               //���[�V�����t���̓G
		ENEMYINMOTION001,            //���[�V�����t���̓G001

		BOSS,                        //�{�X
		PLAYER,                      //�v���C���[
		FIELDBLOCK,                  //�n�ʗp�u���b�N
		GOUPBLOCK,                   //��ɏオ��p�̃u���b�N
		ROADBLOCK,                   //���p�u���b�N
		WALLROADBLOCK,               //�ǌ����p�u���b�N
		WALLROADBLOCK_001,           //�ǌ����p�u���b�N001
		SMALLBLOCK,                  //�������u���b�N
		SMALLBLOCK_001,              //�������u���b�N001
		UPWALLBLOCK,                 //��ǂ̃u���b�N

		TELEPHONPOLE,                //�d��
		SURVEILLANCECAMERAUP,        //�Ď��J�����̏㕔��
		SURVEILLANCECAMERADOWN,      //�Ď��J�����̉�����
		SHOP,                        //�X
		DEBRIS,                      //�j��
		BREAKHOUSE,                  //��ꂽ��
		SPECEBATTLESHIP000,          //TYPE�p�̃X�y�[�X�V�b�v
		MAX
	};

	//�X�g���e�W�[�^�C�v�̐ݒ�
	enum class STRATEGYTYPE
	{
		NONESTRATEGY = 0,     //����
		FIELDBLOCK,             //�u���b�N�O��
		GOUPBLOCK,			  //�u���b�N�P��
		ROADBLOCK,			  //�u���b�N�Q��
		WALLROADBLOCK,			  //�u���b�N�R��
		WALLROADBLOCK001,		  //�u���b�N�R�Ԃ̂Q��
		SMALLBLOCK,			  //�u���b�N�S��
		SMALLBLOCK001,		  //�u���b�N�S�Ԃ̂Q��
		UPWALLBLOCK,			  //�u���b�N�O��
		BLOCK006,			  //�u���b�N�O��
		SPECEBATTLESHIP000,   //�o�g���V�b�v�̔ԍ�
		FINALBLOCK,           //�ŏI�X�e�[�W�p�̃u���b�N
		FINALCEILLING,        //�ŏI�X�e�[�W�p�̓V��
		WODDENBORAD,          //�؂̔Q
	};

	CObjectManagerX(int nPriority = DEFAULT_PRIORITY1);                                                           //�R���X�g���N�^
	virtual ~CObjectManagerX();                                                                                   //�f�X�g���N�^
	virtual HRESULT Init() = 0;                                                                                   //������
	virtual void Uninit() = 0;                                                                                    //�I������
	virtual void Update() = 0;                                                                                    //�X�V����
	virtual void Draw() = 0;                                                                                      //�`�揈��
	static void ReleaseAll();                                                                                     //�S�I�u�W�F�N�g�̉��
	static void UpdateAll();                                                                                      //�S�I�u�W�F�N�g�̍X�V
	static void DrawAll();                                                                                        //�S�I�u�W�F�N�g�̕`��
	static CObjectManagerX* GetObjectManagerX(int nPri, int nIndex) { return m_apObjectManagerX[nPri][nIndex]; }  //�I�u�W�F�N�g�擾
	TYPE GetType() { return m_type; }                                                                             //�^�C�v�擾
	void SetType(TYPE type) { m_type = type; }                                                                    //�^�C�v�ݒ�
	void Release();                                                                                               //�������g�̉��

protected:
	//�}�N����`
	constexpr static int MAX_OBJECTMANAGERX = 200;       //�I�u�W�F�N�g�̍ő吔
	constexpr static int DEFAULT_PRIORITY1 = 3;          //�f�t�H���g�̕`�揇
	constexpr static int MAX_PRIORITY_MANAGER_OBJ = 4;   //�`�揇�̍ő吔

private:
	static CObjectManagerX* m_apObjectManagerX[MAX_PRIORITY_MANAGER_OBJ][MAX_OBJECTMANAGERX]; //�S�I�u�W�F�N�g�̊Ǘ�
	int m_nPriority;  //���g�̃v���C�I���e�B    
	int m_nID;        //�������g��ID
	TYPE m_type;      //�I�u�W�F�N�g�^�C�v

};


