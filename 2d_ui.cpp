//===================================
//
//�Q���̂t�h�̏����ݒ�[2d_ui.cpp]
//Author:chiba haruki
//
//===================================

//===================================
//�C���N���[�h
#include "2d_ui.h"
#include "rendererh.h"
#include "manager.h"


//=============================================================================================================================
//�QDUI�̃}�l�[�W���[�Ǘ��N���X�̏���
//=============================================================================================================================

//==========================
//�����t���R���X�g���N�^
//==========================
CManager2DUI::CManager2DUI(int nPriority) : CObject2D(nPriority)
{
	
}

//==========================
//�f�X�g���N�^
//==========================
CManager2DUI::~CManager2DUI()
{

}

//======================
//����������
//======================
HRESULT CManager2DUI::Init()
{
	//�����������s������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK;       //������Ԃ�
}


//======================
//�I������
//======================
void CManager2DUI::Uninit()
{
	CObject2D::Uninit(); //�j���������Ă�
}


//=======================
//�X�V����
//=======================
void CManager2DUI::Update()
{

}

//=====================
//�`�揈��
//=====================
void CManager2DUI::Draw()
{
	CObject2D::Draw(); //�`�揈�����Ă�
}

//=====================
//��������
//=====================
CManager2DUI* CManager2DUI::Create(TYPE_UI TypeUI)
{
	CManager2DUI* pManager2DUI = nullptr; //���N���X�̃|�C���^�[

	//�^�C�v���X�̃��j���[�̎�
	if (TypeUI== TYPE_UI::SHOPMENU)
	{
		pManager2DUI = new CShopMenu(0); //���I�m��

		//�������ɐ���������
		if (SUCCEEDED(pManager2DUI->Init()))
		{
			pManager2DUI->Lood(); //�e�N�X�`���̓ǂݍ���
			return pManager2DUI;  //����Ԃ�
		}
	}

	return nullptr;               //����Ԃ�
}

//==============================================
//���ݍ���Ă���I�u�W�F�N�gUI�̐�������
//==============================================
CManager2DUI* CManager2DUI::NowCreate(int nNumber)
{
	CManager2DUI* pManager2DUI = new CNowCreateUI(); //���I�m��

	//�������ɐ���������
	if (SUCCEEDED(pManager2DUI->Init()))
	{
		//�ԍ����O�Ԃ̎�
		if (nNumber == 0)
		{
			pManager2DUI->SetFileNamePass("data\\TEXTURE\\StageObj\\SHOP.png");    //�t�@�C���p�X��ݒ�
		}

		//�ԍ����P�Ԃ̎�
		else if (nNumber == 1)
		{
			pManager2DUI->SetFileNamePass("data\\TEXTURE\\StageObj\\images.jpg");  //�t�@�C���p�X��ݒ�
		}

		pManager2DUI->Lood(); //�e�N�X�`���̓ǂݍ���
		return pManager2DUI;  //����Ԃ�
	}

	return nullptr;           //����Ԃ�
}



//=============================================================================================================================
//����낤�Ƃ��Ă��镨��UI�\���̏���
//=============================================================================================================================

//==========================
//�����t���R���X�g���N�^
//==========================
CNowCreateUI::CNowCreateUI(int nPriority) : CManager2DUI(nPriority)
{
	
}


//======================
//�R���X�g���N�^
//======================
CNowCreateUI::~CNowCreateUI()
{

}


//======================
//����������
//======================
HRESULT CNowCreateUI::Init()
{
	//�����������s������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CObject2D::SetSIze(0.0f, SIZEX, 0.0f, SIZEY); //�T�C�Y�̐ݒ�

	return S_OK; //������Ԃ�
}


//===========================================================================================================================================================
//���j���[UI�̏���
//===========================================================================================================================================================

//=======================
//�R���X�g���N
//=======================
CShopMenu::CShopMenu(int nPriority) : CManager2DUI(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Text\\Menyu001.png"); //�t�@�C���p�X�̐ݒ�
}


//=======================
//�f�X�g���N�^
//=======================
CShopMenu::~CShopMenu()
{

}


//=======================
//����������
//=======================
HRESULT CShopMenu::Init()
{
	//�����������s������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CObject2D::SetSIze(0.0f, SIZEX, 0.0f, SIZEY); //�T�C�Y�̎擾

	return S_OK; //������Ԃ�
}


//===========================================================================================================================================================
//���j���[UI�̏���
//===========================================================================================================================================================

//=======================
//�R���X�g���N
//=======================
CBuyText::CBuyText(int nPriority) : CManager2DUI(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Text\\buy001.png"); //�t�@�C���p�X��ݒ�
}


//=======================
//�f�X�g���N�^
//=======================
CBuyText::~CBuyText()
{

}


//=======================
//����������
//=======================
HRESULT CBuyText::Init()
{
	//�����������s������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CObject2D::SetSIze(0.0f, SIZEX, 0.0f, CMain::SCREEN_HEIGHT); //�T�C�Y�̐ݒ�
	SetCol(RED, GREEN, BLUE, ALPHA);                             //�F�̐ݒ�

	return S_OK; //������Ԃ�
}

//========================
//��������
//========================
CBuyText* CBuyText::Create()
{
	CBuyText* pText = new CBuyText(0); //���I�m��

	//��񂪂��鎞
	if (pText != nullptr)
	{
		//������������������
		if (SUCCEEDED(pText->Init()))
		{
			pText->Lood(); //�e�N�X�`���̓ǂݍ���
			return pText;  //����Ԃ�
		}
	}

	return nullptr;        //����Ԃ�
}


//===========================================================================================================================================================
//�I������UI�̏���
//===========================================================================================================================================================

//=======================
//�R���X�g���N
//=======================
CSelectGage::CSelectGage(int nPriority) : CObject2D(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Text\\SelectGage.png"); //�t�@�C���p�X��ݒ�
	m_fSizeX = 0.0f;                                            //�P�Ԗڂ̃T�C�Y��X���̏�����
	m_fSize1X = SIZE1X;                                         //�Q�Ԗڂ̃T�C�Y��X���̏�����
	m_fSizeY = SIZEY;                                           //�P�Ԗڂ̃T�C�Y��Y���̏�����
	m_fSize1Y = SIZE1Y;                                         //�Q�Ԗڂ̃T�C�Y��Y���̏�����
}


//=======================
//�f�X�g���N�^
//=======================
CSelectGage::~CSelectGage()
{

}


//=======================
//����������
//=======================
HRESULT CSelectGage::Init()
{
	//�����������s������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CObject2D::SetSIze(0.0f, m_fSizeX, 0.0f,m_fSizeY); //�T�C�Y�̐ݒ�
	SetCol(RED, GREEN, BLUE, ALPHA);                   //�F�̐ݒ�

	return S_OK; //������Ԃ�
}


//========================
//�j������
//========================
void CSelectGage::Uninit()
{
	CObject2D::Uninit(); //�j���������Ă�
}


//========================
//�X�V����
//========================
void CSelectGage::Update()
{
	CObject2D::SetSIze(m_fSizeX, m_fSize1X, m_fSizeY, m_fSize1Y); //�T�C�Y�̍X�V
}

//========================
//�`�揈��
//========================
void CSelectGage::Draw()
{
	CObject2D::Draw(); //�`�揈��
}


//========================
//��������
//========================
CSelectGage* CSelectGage::Create()
{
	CSelectGage* pSelectGage = new CSelectGage(3); //���I�m��

	//��񂪂��鎞
	if (pSelectGage != nullptr)
	{
		//�������ɐ���������
		if (SUCCEEDED(pSelectGage->Init()))
		{
			pSelectGage->Lood(); //���t�@�C���̓ǂݍ���
			return pSelectGage;  //����Ԃ�
		}
	}

	return nullptr;              //����Ԃ�
}


//===========================================================================================================================================================
//�I������UI�̏���
//===========================================================================================================================================================

//=======================
//�R���X�g���N
//=======================
CSelectGage001::CSelectGage001(int nPriority) : CSelectGage(nPriority)
{
	SetFileNamePass("data\\TEXTURE\\UI\\Text\\SelectGage001.png"); //�t�@�C���p�X��ݒ�

}


//=======================
//�f�X�g���N�^
//=======================
CSelectGage001::~CSelectGage001()
{

}


//=======================
//����������
//=======================
HRESULT CSelectGage001::Init()
{
	//�����������s������
	if (FAILED(CObject2D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CObject2D::SetSIze(0.0f, GetSizeX(), 0.0f, GetSizeY()); //�T�C�Y�̐ݒ�

	return S_OK; //������Ԃ�
}

//========================
//�X�V����
//========================
void CSelectGage001::Update()
{
	
}

//========================
//��������
//========================
CSelectGage001* CSelectGage001::Create()
{
	CSelectGage001* pSelectGage = new CSelectGage001(3); //���I�m��

    //������������������
	if (SUCCEEDED(pSelectGage->Init()))
	{
		pSelectGage->Lood(); //���t�@�C����ǂݍ���
		return pSelectGage;  //����Ԃ�
	}

	return nullptr;              //����Ԃ�
}