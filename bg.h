//===================================
//
//�w�i�̃v���g�^�C�v�錾[bg.h]
//Author:chiba haruki
//
//===================================

#pragma once

//===================================
//�C���N���[�h
#include "object2D.h"
#include "scene.h"


//==================================================================
//�w�i�̊Ǘ����N���X
class CManagerBg : public CObject2D
{
public:
	CManagerBg(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CManagerBg()override;						   //�f�X�g���N�^
	HRESULT Init()override;						   //����������
	void Uninit()override;						   //�j������
	void  Update()override;						   //�X�V����
	void Draw()override;						   //�`�揈��

	static CManagerBg* Create(CScene::MODE mode);  //��������
};


//==================================================================
//�^�C�g���w�i
class CTitleBg : public CManagerBg
{
public:
	CTitleBg(int nPriority = DEFAULT_PRIORITY);    //�R���X�g���N�^
	~CTitleBg()override;                           //�f�X�g���N�^
};


//==================================================================
//���U���g�w�i
class CResultBg : public CManagerBg
{
public:
	CResultBg(int nPriority = DEFAULT_PRIORITY);   //�R���X�g���N�^
	~CResultBg()override;                          //�f�X�g���N�^
};


//==================================================================
//�Q�[���I�[�o�[�w�i
class CGameOverBg : public CManagerBg
{
public:
	CGameOverBg(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CGameOverBg()override;                         //�f�X�g���N�^
	void Update()override;                          //�X�V����

private:
	constexpr static int MAX_RAND = 100;        //�����̍ő吔
	constexpr static int PROCESS_FRAME = 50;    //�������s���t���[����
	constexpr static int ADJUSTMENT_FRAME = 20; //�������s���t���[����

	constexpr static int RED = 255;          //�ԐF
	constexpr static int GREEN = 255;        //�ΐF
	constexpr static int BLUE = 255;         //�F
};


//==================================================================
//�V���b�v���̔w�i
class CShopScreen : public CManagerBg
{
public:
	CShopScreen(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CShopScreen()override;                         //�f�X�g���N�^
	HRESULT Init()override;                         //����������
	void Update()override;                          //�X�V����

	static CShopScreen* Create();                   //��������

private:
	constexpr static int RED = 255;          //�ԐF
	constexpr static int GREEN = 255;        //�ΐF
	constexpr static int BLUE = 255;         //�F
	constexpr static int ALPHA = 50;         //�A���t�@�l
};