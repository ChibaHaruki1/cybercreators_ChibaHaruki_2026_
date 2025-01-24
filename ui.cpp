//=================================
//
//UI�����鏈��[ui.cpp]
//Auther;HARUKI CHIBA
//
//=================================


//=================================
//�C���N���[�h
#include "ui.h"
#include "manager.h"
#include <time.h>


//============================
//�R���X�g���N�^
//============================
CUI::CUI(int nPriority) : CObject3D(nPriority)
{
	
}


//============================
//�f�X�g���N
//============================
CUI::~CUI()
{

}


//============================
//����������
//============================
HRESULT CUI::Init()
{
	//������������������
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}
	
	return S_OK;       //������Ԃ�
}


//============================
//�j������
//============================
void CUI::Uninit()
{
	CObject3D::Uninit(); //�j������
}


//============================
//�X�V����
//============================
void CUI::Update()
{

}


//============================
//�`�揈��
//============================
void CUI::Draw()
{
	CObject3D::Draw(); //�`�揈��
}


//============================
//��������
//============================
CUI* CUI::Create(CObject3D::TYPE typeui)
{
	CUI* pUI = nullptr; //���N���X�̃|�C���^�[

	//�^�C�v���������̎�
	if (typeui == CObject3D::TYPE::CLING)
	{
		pUI = new CCreateInObject(); //���I�m��

		//������������������
		if (SUCCEEDED(pUI->Init()))
		{
			pUI->SetFileNamePass("data\\TEXTURE\\UI\\effect000.jpg"); //�t�@�C���p�X�̐ݒ�
			pUI->CObject3D::Lood();                                   //�e�N�X�`���̓ǂݍ���
			return pUI;                                               //����Ԃ�
		}
	}

	//�^�C�v���b���e�L�X�g�̎�
	else if (typeui == CObject3D::TYPE::TALKTEXTR)
	{
		pUI = new CTalkText(0); //���I�m��

		//�������ɐ���������
		if (SUCCEEDED(pUI->Init()))
		{
			pUI->SetFileNamePass("data\\TEXTURE\\UI\\Text\\Talk.png"); //�t�@�C���p�X�̐ݒ�
			pUI->CObject3D::Lood();                                    //�e�N�X�`���̓ǂݍ���
			return pUI;                                                //����Ԃ�
		}
	}

	//�^�C�v�����[�U�[�̎�
	else if (typeui == CObject3D::TYPE::LASER)
	{
		pUI = new CLaserCamare(); //���I�m��

		//�������ɐ���������
		if (SUCCEEDED(pUI->Init()))
		{
			pUI->SetFileNamePass("data\\TEXTURE\\UI\\Laser000.png"); //�t�@�C���p�X�̐ݒ�
			pUI->CObject3D::Lood();                                  //�e�N�X�`���̓ǂݍ���
			return pUI;                                              //����Ԃ�
		}
	}

	return nullptr; //����Ԃ�
}


//=============================================================================================================================
//����text�ɏ����o����I�u�W�F�N�g�̏ꏊ��UI�����鏈��
//=============================================================================================================================

//============================
//�R���X�g���N�^
//============================
CCreateInObject::CCreateInObject(int nPriority) : CUI(nPriority)
{
	
}


//============================
//�f�X�g���N
//============================
CCreateInObject::~CCreateInObject()
{

}


//=============================================================================================================================
//����text�ɏ����o����I�u�W�F�N�g�̏ꏊ��UI�����鏈��
//=============================================================================================================================

//============================
//�R���X�g���N�^
//============================
CTalkText::CTalkText(int nPriority) : CUI(nPriority)
{

}


//============================
//�f�X�g���N
//============================
CTalkText::~CTalkText()
{

}


//============================
//����������
//============================
HRESULT CTalkText::Init()
{
	//�������ɐ���������
	if (FAILED(CUI::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}
	
	CObject3D::SetSize(SIZEX, SIZEY, SIZEZ); //�傫���̐ݒ�

	return S_OK;       //������Ԃ�
}


//============================
//�`�揈��
//============================
void CTalkText::Draw()
{
	CUI::Draw(); //�`�揈��
}


//=============================================================================================================================
//�J��������o�郌�[�U�[�̏���
//=============================================================================================================================

//============================
//�R���X�g���N�^
//============================
CLaserCamare::CLaserCamare(int nPriority) : CUI(nPriority)
{

}


//============================
//�f�X�g���N
//============================
CLaserCamare::~CLaserCamare()
{

}


//============================
//����������
//============================
HRESULT CLaserCamare::Init()
{
	//�������Ɏ��s������
	if (FAILED(CObject3D::BillboardInit()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	CObject3D::SetSize(SIZEX, SIZEY, SIZEZ);               //�傫����ݒ�
	SetRot(D3DXVECTOR3(0.0f, ADDJUST_ROTY, ADDJUST_ROTZ)); //������ݒ�

	//�ʒu���Ď��J�����̏㕔�����ɐݒ肷��
	SetPos(D3DXVECTOR3(CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().x, 
		CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().y - ADDJUST_POSY,
		CManager::GetInstance()->GetSurveillanceCameraUp(CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount())->GetPos().z - ADDJUST_POSZ));

	return S_OK;       //������Ԃ�
}


//============================
//�X�V����
//============================
void CLaserCamare::Update()
{
	//�����蔻��
	if (CObject3D::CollisionPrtsPlayer(SIZEY * ADDJUST_ADDJUST_SIZE, SIZEX * ADDJUST_ADDJUST_SIZE, SIZEZ * ADDJUST_ADDJUST_SIZE) == true)
	{
		srand((unsigned)time(NULL));  //�����n���������
		SetRandom(1 + rand() % 2);     //�����̐���(�͈͎w��1�`�Q�j

		//�������P�̎�
		if (GetRandom() == 1)
		{
			//�G�̐���
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001, 0, D3DXVECTOR3(GetPos().x + ADDJUST_CREATE_POSX, GetPos().y + ADDJUST_CREATE_POSY, 0.0f));
			CObject3D::Release();     //���g�̍폜
			return;                   //�����𔲂���
		}
		else
		{
			//�G�̐���
			CManager::GetInstance()->GetCreateObjectInstanceX(CObjectX::TYPE::ENEMYINMOTION001, 0, D3DXVECTOR3(GetPos().x - ADDJUST_CREATE_POSX, GetPos().y + ADDJUST_CREATE_POSY, 0.0f));
			CObject3D::Release();     //���g�̍폜
			return;                   //�����𔲂���
		}
	}

	////�J�����̏㕔���̏�񂪂Ȃ��Ȃ�����
	//for (int nCamera = 0; nCamera < CManager::GetScene()->GetPlayerX()->GetTelephonPoleCount(); nCamera++)
	//{
	//	if (CManager::GetInstance()->GetSurveillanceCameraUp(nCamera) == nullptr)
	//	{
	//		CObject3D::Release();
	//		return;
	//	}
	//}
}


//============================
//�`�揈��
//============================
void CLaserCamare::Draw()
{
	CObject3D::DrawBillboard(); //�`�揈��
}