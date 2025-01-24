//========================================
//
//�r���{�[�h����[billboard.cpp]
//Auther:Haruki Chiba
//
//========================================


//========================================
//�C���N���[�h
#include "billboard.h"
#include "object3D.h"
#include "rendererh.h"
#include "manager.h"


//=========================
//�R���X�g���N�^
//=========================
CBillboard::CBillboard(int nPriority) : CObject3D(nPriority)
{
	
}


//=========================
//�f�X�g���N�^
//=========================
CBillboard::~CBillboard()
{

}


//=========================
//����������
//=========================
HRESULT CBillboard::Init()
{
	//�������Ɏ��s�����Ƃ�
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	SetPos(D3DXVECTOR3(MAX_BILLBOARD_SIZE_X, MAX_BILLBOARD_SIZE_Y, 0.0f)); //�ʒu�̐ݒ�
	SetRot(D3DXVECTOR3(0.0f, 0.0f, 0.0f));                                 //�����̐ݒ�

	return S_OK;       //������Ԃ�
}


//=========================
//�I������
//=========================
void CBillboard::Uninit()
{
	CObject3D::Uninit(); //�j���������Ă�
}


//=========================
//�X�V����
//=========================
void CBillboard::Update()
{
	
}


//=========================
//�`�揈��
//=========================
void CBillboard::Draw()
{
   CObject3D::Draw(); //�`�揈�����Ă�
}

//=========================
//�r���{�[�h�̐���
//=========================
CBillboard* CBillboard::Create()
{
	CBillboard* pBillboard = new CBillboard(3); //���I�m��

    //�������ɐ���������
	if (SUCCEEDED(pBillboard->Init()))
	{
		pBillboard->Lood(); //�e�N�X�`���̓ǂݍ���
		return pBillboard;  //����Ԃ�
	}

	return nullptr;             //����Ԃ�
}