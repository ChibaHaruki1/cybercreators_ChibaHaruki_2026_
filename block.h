//======================================
//
//��Q���̃N���X�Ǘ�[block.h]
//Auther:Chiba Haruki
//
//======================================

#pragma once

//======================================
//�C���N���[�h
#include "objectX.h"


//==================================================================
//�X�g���e�W�[���N���X
//==================================================================
class CBlockXStrategy
{
public:
	CBlockXStrategy();          //�R���X�g���N�^
	~CBlockXStrategy();         //�f�X�g���N�^

	const char* GetBlockFileNamePass() { return m_aBlockFile; }                               //�t�@�C���p�X���擾
	void SetBlockFileNamePass(const char* aBlockFileName) { m_aBlockFile = aBlockFileName; }  //�t�@�C���p�X��ݒ�
private:
	const char* m_aBlockFile; //�t�@�C���p�X��ۊǂ���p�̕ϐ�
};


//==================================================================
//�X�g���e�W�[�N���X�p��
class CBlock000 : public CBlockXStrategy
{
public:
	CBlock000();   //�R���X�g���N�^
	~CBlock000();  //�f�X�g���N�^
};


//==================================================================
//�X�g���e�W�[�N���X�p��
class CBlock001 : public CBlockXStrategy
{
public:
	CBlock001();   //�R���X�g���N�^
	~CBlock001();  //�f�X�g���N�^
};


//==================================================================
//�X�g���e�W�[�N���X�p��
class CBlock002 : public CBlockXStrategy
{
public:
	CBlock002();   //�R���X�g���N�^
	~CBlock002();  //�f�X�g���N�^
};


//==================================================================
//�X�g���e�W�[�N���X�p��
class CBlock003 : public CBlockXStrategy
{
public:
	CBlock003();   //�R���X�g���N�^
	~CBlock003();  //�f�X�g���N�^
};


//==================================================================
//�X�g���e�W�[�N���X�p��
class CBlock004 : public CBlockXStrategy
{
public:
	CBlock004();   //�R���X�g���N�^
	~CBlock004();  //�f�X�g���N�^
};

//==================================================================

//�X�g���e�W�[�N���X�p��
class CBlock005 : public CBlockXStrategy
{
public:
	CBlock005();   //�R���X�g���N�^
	~CBlock005();  //�f�X�g���N�^
};


//==================================================================
//�X�g���e�W�[�N���X�p��
class CBlock006 : public CBlockXStrategy
{
public:
	CBlock006();   //�R���X�g���N�^
	~CBlock006();  //�f�X�g���N�^
};


//==================================================================
//���̃X�e�[�W�֍s���p��obj
class CSpaceBattleShip : public CBlockXStrategy
{
public:
	CSpaceBattleShip();   //�R���X�g���N�^
	~CSpaceBattleShip();  //�f�X�g���N�^
};


//==================================================================
//�{�X��p�̃u���b�N�i�X�e�[�W�j
class CFinalBlock : public CBlockXStrategy
{
public:
	CFinalBlock();   //�R���X�g���N�^
	~CFinalBlock();	 //�f�X�g���N�^
};


//==================================================================
// �{�X��p�̃u���b�N�i�X�e�[�W�j
class CFinalBlock1 : public CBlockXStrategy
{
public:
	CFinalBlock1() { SetBlockFileNamePass("data\\XFILE\\BLOCK\\FianlStageCeiling.x"); }  //�R���X�g���N�^
	~CFinalBlock1() {};																	 //�f�X�g���N�^
};


//==================================================================
//���ꂫ�Ɋւ���u���b�N
class CRubble : public CBlockXStrategy
{
public:
	CRubble() {};  //�R���X�g���N�^
	~CRubble() {}; //�f�X�g���N�^
};


//==================================================================
//�u���b�N�̊��N���X
//==================================================================
class CManagerBlock : public  CObjectX
{
public:
	CManagerBlock(int nPriority = DEFAULT_PRIORITY1);  //�R���X�g���N�^
	~CManagerBlock()override;						   //�f�X�g���N�^
	HRESULT Init()override;                            //����������  
	void Uninit()override;                             //�j������
	void Update() override;                            //�X�V����
	void Draw()override;
	void TextFileWrite(float m_fPosX, float m_fPosY, float m_fPosZ,CObjectX::TYPE type); //�e�L�X�g�t�@�C���ɏ����������ޏ���

	static CManagerBlock* Create(D3DXVECTOR3 pos, STRATEGYTYPE type); //��������

private:
	static int m_nCreateCount;          //���ꂽ����ۊǂ���
	CBlockXStrategy* m_pBlockXStrategy; //�X�g���e�W�[���N���X�̃|�C���^�[
};


//==================================================================
//3D��Q���̃N���X�Ǘ�
class CFiledBlock : public  CManagerBlock
{
public:
	CFiledBlock(int nPriority = DEFAULT_PRIORITY1); //�R���X�g���N�^
	~CFiledBlock()override;                         //�f�X�g���N�^
};


//==================================================================
//��ɏオ�邽�߂̃u���b�N
class CGoUpBlock : public CManagerBlock
{
public:
	CGoUpBlock(int nPriority = DEFAULT_PRIORITY1); //�R���X�g���N�^
	~CGoUpBlock()override;                         //�f�X�g���N�^
};


//==================================================================
//���p�̃u���b�N
class CRoadBlock : public CManagerBlock
{
public:
	CRoadBlock(int nPriority = DEFAULT_PRIORITY1); //�R���X�g���N�^
	~CRoadBlock()override;                         //�f�X�g���N�^
};


//==================================================================
//�ǌ����p�u���b�N
class CWallRoadBlock : public CManagerBlock
{
public:
	CWallRoadBlock(int nPriority = DEFAULT_PRIORITY1); //�R���X�g���N�^
	~CWallRoadBlock()override;                         //�f�X�g���N�^
};


//==================================================================
//�������u���b�N
class CSmallBlock : public CManagerBlock
{
public:
	CSmallBlock(int nPriority = DEFAULT_PRIORITY1);//�R���X�g���N�^
	~CSmallBlock()override;                        //�f�X�g���N�^
};


//==================================================================
//��ǂ̃u���b�N
class CUpWallBlock : public CManagerBlock
{
public:
	CUpWallBlock(int nPriority = DEFAULT_PRIORITY1); //�R���X�g���N�^
	~CUpWallBlock()override;                         //�f�X�g���N�^
};


//==================================================================
//���̃X�e�[�W�֍s���ׂ̃V�b�v
class CSpaceBattleShip000 : public CManagerBlock
{
public:
	CSpaceBattleShip000(int nPriority = DEFAULT_PRIORITY1); //�R���X�g���N�^
	~CSpaceBattleShip000()override;                         //�f�X�g���N�^
};


//==================================================================
//����
class CScaffold : public CManagerBlock
{
public:
	CScaffold(int nPriority = DEFAULT_PRIORITY1); //�R���X�g���N�^
	~CScaffold()override;                         //�f�X�g���N�^
};


//==================================================================
//�V��
class CCeiling : public CManagerBlock
{
public:
	CCeiling(int nPriority = DEFAULT_PRIORITY1); //�R���X�g���N�^
	~CCeiling()override;                         //�f�X�g���N�^
};


//==================================================================
//�؂̔Q
class CWoodenBorad : public CManagerBlock
{
public:
	CWoodenBorad(int nPriority = DEFAULT_PRIORITY1); //�R���X�g���N�^
	~CWoodenBorad()override;	                     //�f�X�g���N�^
	void Update()override;                           //�X�V����
};
