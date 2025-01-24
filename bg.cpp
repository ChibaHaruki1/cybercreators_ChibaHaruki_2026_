//===================================
//
//�w�i�̏����ݒ�[bg.cpp]
//Author:chiba haruki
//
//===================================


//===================================
//�C���N���[�h
#include "bg.h"
#include "rendererh.h"
#include "manager.h"
#include <time.h>


//==========================
//�����t���R���X�g���N�^
//==========================
CManagerBg::CManagerBg(int nPriority) : CObject2D(nPriority)
{
	SetAlph(255); //�A���t�@�l��ݒ�
}


//======================
//�R���X�g���N�^
//======================
CManagerBg::~CManagerBg()
{

}


//======================
//�w�i�̏���������
//======================
HRESULT CManagerBg::Init()
{
	//�����������s������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK; //������Ԃ�
}


//======================
//�w�i�̏I������
//======================
void CManagerBg::Uninit(void)
{
	CObject2D::Uninit(); //�j���������Ă�
}


//=======================
//�w�i�̍X�V����
//=======================
void CManagerBg::Update()
{
	VERTEX_2D* pVtx; //�o�[�e�N�X�̃|�C���^�[

	//���_�o�b�t�@�����b�N���A���_�f�[�^�ւ̃|�C���^���擾
	GetBuffer()->Lock(0U, 0U, (void**)&pVtx, 0);

	//���_�J���[�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(255, 255, 255, GetAlph());
	pVtx[1].col = D3DCOLOR_RGBA(255, 255, 255, GetAlph());
	pVtx[2].col = D3DCOLOR_RGBA(255, 255, 255, GetAlph());
	pVtx[3].col = D3DCOLOR_RGBA(255, 255, 255, GetAlph());

	//���_�o�b�t�@���A�����b�N
	GetBuffer()->Unlock();
}


//=====================
//�w�i�̕`�揈��
//=====================
void CManagerBg::Draw()
{
	CObject2D::Draw(); //�`�揈�����Ă�
}


//===================================
//�I�u�W�F�N�g����
//===================================
CManagerBg* CManagerBg::Create(CScene::MODE mode)
{
	CManagerBg* pBg = nullptr; //���N���X�̃|�C���^�[

	//�^�C�g����
	if (mode == CScene::MODE::MODE_TITLE)
	{
		pBg = new CTitleBg(0);                                            //���I�m��
		pBg->SetFileNamePass("data\\TEXTURE\\UI\\scene\\Title001.png");   //�t�@�C���p�X��ݒ�
	}

	//���U���g��														     
	else if (mode == CScene::MODE::MODE_RESULT)
	{
		pBg = new CResultBg(3);                                           //���I�m��
		pBg->SetFileNamePass("data\\TEXTURE\\UI\\scene\\Result.png");      //�t�@�C���p�X��ݒ�
	}

	//���S��
	else if (mode == CScene::MODE::MODE_GAMEOVER)
	{
		pBg = new CGameOverBg(3);                                         //���I�m��
		pBg->SetFileNamePass("data\\TEXTURE\\UI\\SCREEN\\GameOver.jpg");  //�t�@�C���p�X��ݒ�
	}

	//������������������
	if (SUCCEEDED(pBg->Init()))
	{
		pBg->Lood(); //�e�N�X�`���̓ǂݍ��݊֐����Ă�
		return pBg;  //����Ԃ�
	}

	return nullptr; //����Ԃ�
}


//================================================================================================================================================
//�^�C�g���w�i
//================================================================================================================================================

//==========================
//�����t���R���X�g���N�^
//==========================
CTitleBg::CTitleBg(int nPriority) : CManagerBg(nPriority)
{
	
}


//======================
//�R���X�g���N�^
//======================
CTitleBg::~CTitleBg()
{

}


//================================================================================================================================================
//���U���g�w�i
//================================================================================================================================================

//==========================
//�����t���R���X�g���N�^
//==========================
CResultBg::CResultBg(int nPriority) : CManagerBg(nPriority)
{
	
}


//======================
//�R���X�g���N�^
//======================
CResultBg::~CResultBg()
{

}


//================================================================================================================================================
//�Q�[���I�[�o�[�w�i
//================================================================================================================================================

//==========================
//�����t���R���X�g���N�^
//==========================
CGameOverBg::CGameOverBg(int nPriority) : CManagerBg(nPriority)
{
	
}


//======================
//�R���X�g���N�^
//======================
CGameOverBg::~CGameOverBg()
{

}

//=================================
//�X�V����
//=================================
void CGameOverBg::Update()
{
	SetRandom(1 + rand() % MAX_RAND);  //�����𐶐�
	GetFrame()++;                      //�t���[���𑝂₷

	//�t���[�����K�萔�ȏ�s������
	if (GetFrame() >= PROCESS_FRAME)
	{
		//===============================================
		//���ŕ����i�S���邩��S�����̒l�Ōv�Z�j
		//===============================================

		if (GetRandom() >= 1 && GetRandom() <= MAX_RAND*0.25)
		{
			SetSIze(0.0f, CMain::SCREEN_WIDTH, 100.0f, CMain::SCREEN_HEIGHT + 100.0f); //�傫���̐ݒ�
			SetAlph(255);  //alpha�l�̏�����
			SetFrame(0);   //�t���[���̏�����
		}

		else if (GetRandom() >= MAX_RAND * 0.25+1 && GetRandom() <= MAX_RAND*0.5)
		{
			SetSIze(0.0f, CMain::SCREEN_WIDTH, -100.0f, CMain::SCREEN_HEIGHT - 100.0f); //�傫���̐ݒ�
			SetAlph(255);  //alpha�l�̏�����
			SetFrame(0);   //�t���[���̏�����
		}

		else if (GetRandom() >= MAX_RAND * 0.5+1 && GetRandom() <= MAX_RAND*0.75)
		{
			SetSIze(-200.0f, CMain::SCREEN_WIDTH - 200.0f, 0.0f, CMain::SCREEN_HEIGHT);
			SetAlph(155);  //alpha�l��������
			SetFrame(0);   //�t���[���̏�����
		}

		else
		{
			SetSIze(200.0f, CMain::SCREEN_WIDTH + 200.0f, 0.0f, CMain::SCREEN_HEIGHT);
			SetAlph(55);   //alpha�l��������
			SetFrame(0);   //�t���[���̏�����
		}
	}

	//�t���[�����K��l�ȏ�֍s������
	else if (GetFrame() >= ADJUSTMENT_FRAME)
	{
		SetSIze(0.0f, CMain::SCREEN_WIDTH, 0.0f, CMain::SCREEN_HEIGHT); //�傫���̐ݒ�
	}
	SetCol(RED,GREEN,BLUE,GetAlph());                                   //�F�ݒ肷��
}


//===========================================================================================================================================================
//SHOP���̔w�i�̏���
//===========================================================================================================================================================

//=======================
//�R���X�g���N
//=======================
CShopScreen::CShopScreen(int nPriority) : CManagerBg(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Screen\\Yellow.png"); //�t�@�C���p�X��ݒ�
}


//=======================
//�f�X�g���N�^
//=======================
CShopScreen::~CShopScreen()
{

}


//=======================
//����������
//=======================
HRESULT CShopScreen::Init()
{
	//�����������s������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CObject2D::SetSIze(0.0f, CMain::SCREEN_WIDTH, 0.0f, CMain::SCREEN_HEIGHT); //�傫����ݒ�
	SetCol(RED, GREEN, BLUE, ALPHA);                                           //�F�ݒ肷��

	return S_OK; //������Ԃ�
}


//========================
//�X�V����
//========================
void CShopScreen::Update()
{
	
}


//========================
//��������
//========================
CShopScreen* CShopScreen::Create()
{
	CShopScreen* pText = new CShopScreen(0); //���I�m��

    //�������ɐ���������
	if (SUCCEEDED(pText->Init()))
	{
		pText->Lood(); //�e�N�X�`���̓ǂݍ���
		return pText;  //����Ԃ�
	}
	return nullptr; //����Ԃ�
}
