//==================================================================
//
//�X�e�[�W�ɔz�u����I�u�W�F�N�g�̏����̏���[statge_obj.cpp]
//Auther:Chiba Haruki
//
//==================================================================

//===========================
//�C���N���[�h
#include "main.h"
#include"manager.h"
#include "rendererh.h"
#include "stage_obj.h"
#include <string>


//===========================
//������̐ݒ�i���{��j
std::string u8TelephonPoleText = u8"�d���̏��ݒ�"; //���{��Ή�
std::string u8TelephonPoleNumberText = u8"�Ԗڂ�";   //���{��Ή�


//===========================
//static�ϐ��̏�����
int CStageObj::m_nTelephonPoleCount = 0; //�d���̃t�@�C���ɏ������ސ���������


//============================
//�R���X�g���N�^
//============================
CStageObj::CStageObj(int nPriority) : CObjectX(nPriority)
{
	
}

//============================
//�f�X�g���N�^
//============================
CStageObj::~CStageObj()
{

}

//============================
//����������
//============================
HRESULT CStageObj::Init()
{
	//�������ɐ������邩�ǂ���
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK;       //������Ԃ�
}

//==========================
//�I������
//==========================
void CStageObj::Uninit()
{
	CObjectX::Uninit(); //�j���������Ă�
}

//========================
//�X�V����
//========================
void CStageObj::Update()
{
	CObjectX::Update(); //�X�V�������Ă�
}

//======================================
//�e�L�X�g�t�@�C���ɏ������ޏ���
//======================================
void CStageObj::TextFileWrite(CObjectX::TYPE type,float m_fPosX, float m_fPosY, float m_fPosZ)
{
	FILE* m_pFile;                                                //�t�@�C���̃|�C���^�[
	m_pFile = fopen("data\\TEXT\\OBJECT\\TelephonPole.txt", "a"); //�t�@�C����ǂݍ���

	//�t�@�C���̏�񂪖���������
	if (m_pFile == nullptr)
	{
		return; //�����𔲂���
	}

	//�^�C�v���d���̎�
	if (type == CObjectX::TYPE::TELEPHONPOLE)
	{
		m_nTelephonPoleCount++;
		fprintf(m_pFile, "%s", "\n\n");                                     //���s
		fprintf(m_pFile, "%s", "#=====================================\n"); //�������������
		fprintf(m_pFile, "%s", "#");                                        //�������������
		fprintf(m_pFile, "%d", m_nTelephonPoleCount);                       //��������������
		fprintf(m_pFile, "%s", u8TelephonPoleNumberText.data());            //��������������
		fprintf(m_pFile, "%s", u8TelephonPoleText.data());                  //��������������(�S�p����)
		fprintf(m_pFile, "%s", "\n");                                       //���s���s��
		fprintf(m_pFile, "%s", "#=====================================\n"); //�������������
		fprintf(m_pFile, "%s", "TELEPHONPOLESET\n");                        //��������������
		fprintf(m_pFile, "%s", "		POS = ");                           //�uPOS�v�̕�������������
		fprintf(m_pFile, "%.1f ", m_fPosX);                                 //�u�ʒu�v�̕�������������(�����_��P�܂�)
		fprintf(m_pFile, "%.1f ", m_fPosY);                                 //�u�ʒu�v�̕�������������(�����_��P�܂�)
		fprintf(m_pFile, "%.1f ", m_fPosZ);                                 //�u�ʒu�v�̕�������������(�����_��P�܂�)
		fprintf(m_pFile, "%s", "\n");                                       //���s���s��
		fprintf(m_pFile, "%s", "END_TELEPHONPOLESET\n");                    //��������������
		fclose(m_pFile);                                                    //�t�@�C�������
	}
}

//======================
//�`�揈��
//======================
void CStageObj::Draw()
{
	CObjectX::Draw(); //�`�揈�����Ă�
}

//========================
//�����𐶐�
//========================
CStageObj* CStageObj::Create(D3DXVECTOR3 pos, CObjectX::TYPE type)
{
	CStageObj* pStageObj = nullptr; //���N���X�̃|�C���^�[������

	//�^�C�v���d���̎�
	if (type == CObjectX::TYPE::TELEPHONPOLE)
	{
		pStageObj = new CTelephonPole(3); //���I�m��

		//��񂪂��鎞
		if (pStageObj != nullptr)
		{
			pStageObj->SetFileName("data\\XFILE\\StageObj\\telephone_pole.x");  //�p�X�̐ݒ�
			pStageObj->SetType(TYPE::TELEPHONPOLE);                             //�^�C�v�̐ݒ�
		}
	}

	//�^�C�v���Ď��J�����̏㕔���̎�
	else if (type == CObjectX::TYPE::SURVEILLANCECAMERAUP)
	{
		pStageObj = new CSurveillanceCameraUP(3); //���I�m��

		//��񂪂��鎞
		if (pStageObj != nullptr)
		{
			pStageObj->SetFileName("data\\XFILE\\StageObj\\surveillance_cameraUP.x"); //�p�X�̐ݒ�
		}
	}

	//�^�C�v���Ď��J�����̉������̎�
	else if (type == CObjectX::TYPE::SURVEILLANCECAMERADOWN)
	{
		pStageObj = new CSurveillanceCameraDown(3); //���I�m��

		//��񂪂��鎞
		if (pStageObj != nullptr)
		{
			pStageObj->SetFileName("data\\XFILE\\StageObj\\surveillance_cameraDown.x"); //�p�X�̐ݒ�
		}
	}

	//�^�C�v���Ď��J�����̉������̎�
	else if (type == CObjectX::TYPE::SHOP)
	{
		pStageObj = new CShop(3); //���I�m��

		//��񂪂��鎞
		if (pStageObj != nullptr)
		{
			pStageObj->SetFileName("data\\XFILE\\StageObj\\Shop.x"); //�p�X�̐ݒ�
		}
	}

	//�^�C�v����ꂽ�Ƃ̎�
	else if (type == CObjectX::TYPE::BREAKHOUSE)
	{
		pStageObj = new CBreakHouse(3); //���I�m��

		//��񂪂��鎞
		if (pStageObj != nullptr)
		{
			pStageObj->SetFileName("data\\XFILE\\StageObj\\BreakHouse000.x"); //�p�X�̐ݒ�
		}
	}

	//��񂪂��鎞
	if (pStageObj != nullptr)
	{
		//�������ɐ���
		if (SUCCEEDED(pStageObj->Init()))
		{
			pStageObj->GetPos() = pos;       //�ʒu�𓯊�������
			pStageObj->CObjectX::Lood();     //X�t�@�C����ǂݍ��ފ֐����Ă�
			pStageObj->Size();               //�T�C�Y�̎擾
			pStageObj->SetType(TYPE::SHOP);  //�^�C�v�̐ݒ�
			return pStageObj;                //����Ԃ�
		}
	}

	return nullptr; //����Ԃ�
}


//==========================================================================================================================
//�d���̏���
//==========================================================================================================================

//============================
//�R���X�g���N�^
//============================
CTelephonPole::CTelephonPole(int nPriority) : CStageObj(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CTelephonPole::~CTelephonPole()
{

}


//==========================================================================================================================
//�Ď��J�����̏㕔���̏���
//==========================================================================================================================

//============================
//�R���X�g���N�^
//============================
CSurveillanceCameraUP::CSurveillanceCameraUP(int nPriority) : CStageObj(nPriority)
{
	
}

//============================
//�f�X�g���N�^
//============================
CSurveillanceCameraUP::~CSurveillanceCameraUP()
{

}

//============================
//����������
//============================
HRESULT CSurveillanceCameraUP::Init()
{
	//���������������邩�ǂ���
	if (FAILED(CStageObj::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK;       //������Ԃ�
}

//==========================
//�I������
//==========================
void CSurveillanceCameraUP::Uninit()
{
	CStageObj::Uninit(); //�I���������Ă�
}

//========================
//�X�V����
//========================
void CSurveillanceCameraUP::Update()
{
	CStageObj::Update(); //�X�V�������Ă�
}

//======================
//�`�揈��
//======================
void CSurveillanceCameraUP::Draw()
{
	CStageObj::Draw();   //�`�揈�����Ă�
}


//==========================================================================================================================
//�Ď��J�����̉������̏���
//==========================================================================================================================

//============================
//�R���X�g���N�^
//============================
CSurveillanceCameraDown::CSurveillanceCameraDown(int nPriority) : CStageObj(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CSurveillanceCameraDown::~CSurveillanceCameraDown()
{

}


//==========================================================================================================================
//�X�̏���
//==========================================================================================================================

//============================
//�R���X�g���N�^
//============================
CShop::CShop(int nPriority) : CStageObj(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CShop::~CShop()
{

}


//==========================================================================================================================
//��ꂽ�Ƃ̏���
//==========================================================================================================================

//============================
//�R���X�g���N�^
//============================
CBreakHouse::CBreakHouse(int nPriority) : CStageObj(nPriority)
{

}

//============================
//�f�X�g���N�^
//============================
CBreakHouse::~CBreakHouse()
{

}

//============================
//�X�V����
//============================
void CBreakHouse::Update()
{
	//��񂾂�������ʂ�
	if (GetOneFlag() == false)
	{
		CManager::GetInstance()->GetCreateObjectInstnace(CObject3D::TYPE::FIRE, 0, D3DXVECTOR3(0.0f, 0.0f, 0.0f));    //���G�t�F�N�g���Ă�
		CManager::GetInstance()->GetFire()->GetLife() = 60 * 3;                                                       //���C�t��ݒ�
		CManager::GetInstance()->GetFire()->GetAlpha() = 150;                                                         //���C�t��ݒ�
		CManager::GetInstance()->GetFire()->SetSize(920.0f, 700.0f, 0.0f);                                            //�傫����ݒ�
		CManager::GetInstance()->GetFire()->SetEffect(D3DXVECTOR3(GetPos().x+200.0f, GetPos().y+600.0f, GetPos().z)); //���G�t�F�N�g���Ă�
		SetOneFlag(true); //��x�ƒʂ�Ȃ�����
	}

	//�G�t�F�N�g�̃��C�t������̐��l�܂ōs������
	if (CManager::GetInstance()->GetFire()->GetLife() <= 10)
	{
		SetOneFlag(false); //������x�ʂ�悤�ɂ���
	}
}