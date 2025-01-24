//=========================================================
//
//���I�̔j�ЃI�u�W�F�N�g�̏���[direction_obj.cpp]
//Auther:Haruki Chiba
//
//=========================================================


//============================
//�C���N���[�h
#include "main.h"
#include "direction_obj.h"
#include "manager.h"


//============================
//�R���X�g���N�^
//============================
CDebrisX::CDebrisX(int nPriority) : CObjectX(nPriority)
{
	SetFileName("data\\XFILE\\DirectionObj\\Debris.x"); //�t�@�C���p�X�̐ݒ�
}

//============================
//�f�X�g���N�^
//============================
CDebrisX::~CDebrisX()
{

}

//============================
//����������
//============================
HRESULT CDebrisX::Init()
{
	//������������������
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL;  //���s��Ԃ�
	}

	SetLife(MAX_LIFE);  //���C�t�̐ݒ�

	return S_OK;        //����������
}

//==========================
//�I������
//==========================
void CDebrisX::Uninit()
{
	CObjectX::Uninit(); //�j������
}

//========================
//�X�V����
//========================
void CDebrisX::Update()
{
	SetAddjustLife()--; //���C�t�����炷

	//���C�t���s������
	if (GetLife()<=0)
	{
  		CObjectX::Release(); //���g���폜
		//CManager::GetInstance()->DesignationUninitX(CObjectX::TYPE::DEBRIS, m_nDirectionCount);
		return;              //�����𔲂���
	}
}


//======================
//�`�揈��
//======================
void CDebrisX::Draw()
{
	CObjectX::Draw(); //�`�揈��
}


//=====================
//����
//=====================
CDebrisX* CDebrisX::Create(D3DXVECTOR3 pos)
{
	CDebrisX* m_pDebris3D = new CDebrisX(); //���I�m��

	//�������ɐ���������
	if (SUCCEEDED(m_pDebris3D->Init()))
	{
		m_pDebris3D->GetPos() = pos;       //�ʒu�𓯊�������
		m_pDebris3D->Lood();               //X�t�@�C����ǂݍ��ފ֐����Ă�
		return m_pDebris3D;                //����Ԃ�
	}

	return nullptr;                        //����Ԃ�
}