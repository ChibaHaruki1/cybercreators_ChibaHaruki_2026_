//==================================
//
//��Q���̏���[block.cpp]
//Auther:Chiba Haruki
//
//==================================


//==================================
//�C���N���[�h
#include "main.h"
#include"manager.h"
#include "rendererh.h"
#include "skydoom.h"


//============================
//�R���X�g���N�^
//============================
CSkyDoom::CSkyDoom(int nPriority) : CObjectX(nPriority)
{
	
}


//============================
//�f�X�g���N�^
//============================
CSkyDoom::~CSkyDoom()
{

}


//============================
//����������
//============================
HRESULT CSkyDoom::Init()
{
	//�����������ɐ���������
	if (FAILED(CObjectX::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK;       //������Ԃ�
}

//==========================
//�I������
//==========================
void CSkyDoom::Uninit()
{
	CObjectX::Uninit(); //�j������
}

//========================
//�X�V����
//========================
void CSkyDoom::Update()
{
	////�����̍X�V�i�����Ă���悤�Ɍ�����j
    //GetRot().x += 0.0001f;
	//GetRot().z += 0.0001f;

	//D�L�[�������ꂽ��
	if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_D) == true)
	{
		GetRot().y += 0.0001f; //�����������Ɠ��������ɌX��
		SetAddjustMove().x += CManager::GetScene()->GetPlayerX()->GetMove().x;
	}

	//A�L�[�������ꂽ��
	else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_A) == true)
	{
		GetRot().y -= 0.0001f; //�����������Ɠ��������ɌX��
		SetAddjustMove().x += CManager::GetScene()->GetPlayerX()->GetMove().x;
	}

	GetPos().y = CManager::GetScene()->GetPlayerX()->GetPos().y; //�v���C���[�̂����Ə�ɓ��������遁���������Ɏ��R�Ɍ������
	GetPos().x = CManager::GetScene()->GetPlayerX()->GetPos().x; //�v���C���[�̂����Ə�ɓ���������

	CObjectX::Update(); //�ʒu�̍X�V����
}

//======================
//�`�揈��
//======================
void CSkyDoom::Draw()
{
	CObjectX::Draw(); //�`�揈��
}


//========================
//�����𐶐�
//========================
CSkyDoom* CSkyDoom::Create(D3DXVECTOR3 pos, int nNumber)
{
	CSkyDoom* pCBlockX = new CSkyDoom(1); //���I�m��

	//�������ɐ���
	if (SUCCEEDED(pCBlockX->Init()))
	{
		//�ԍ����O�̎�
		if (nNumber == 0)
		{
			pCBlockX->SetFileName("data\\XFILE\\StageObj\\SkyDoom.x");      //�F��
		}

		//�ԍ����P�̎�
		else if (nNumber == 1)
		{
			pCBlockX->SetFileName("data\\XFILE\\StageObj\\SkyDoom001.x");  //�܂��
		}
		pCBlockX->GetPos() = pos;   //�ʒu�𓯊�������
		pCBlockX->CObjectX::Lood(); //X�t�@�C����ǂݍ��ފ֐����Ă�
		return pCBlockX;            //����Ԃ�
	}

	return nullptr;                 //����Ԃ�
}
