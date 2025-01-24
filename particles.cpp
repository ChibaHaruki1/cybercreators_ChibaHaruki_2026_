//==========================================
//
//�p�[�e�B�N���̏���[particles.cpp]
//Author:chiba haruki
//
//==========================================


//==========================================
//�C���N���[�h
#include "main.h"
#include "particles.h"
#include "rendererh.h"
#include "manager.h"


//============================
//�R���X�g���N�^
//============================
CParticles001::CParticles001(int nPriority) : CObject3D(nPriority)
{
	SetLife(MAX_PARTICLES001_LIFE);                  //���C�t�̐ݒ�
	SetFileNamePass("data\\TEXTURE\\Circle003.png"); //�t�@�C���p�X�̐ݒ�
}


//============================
//�f�X�g���N�^
//============================
CParticles001::~CParticles001()
{

}


//============================
//����������
//============================
HRESULT CParticles001::Init()
{
	//������������������
	if (FAILED(CObject3D::Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK;       //������Ԃ�
}


//==========================
//�I������
//==========================
void CParticles001::Uninit()
{
	CObject3D::Uninit(); //�j������
}


//========================
//�X�V����
//========================
void CParticles001::Update()
{
	SetSize(SIZEX, SIZEY, SIZEZ);   //�傫���̐ݒ�

	SetAddjustLife()--;             //���C�t�����炷

	SetAddjustPos().y += PLUS_POSY; //Y���̈ʒu�𑝂₷

	//���C�t���O���傫����
	if (GetLife() <= 0)
	{
		CObject3D::Release();       //���g�̉��
		return;                     //�����𔲂��邱�Ƃɂ���āA�o�b�t�@�̃A�N�Z�X�ᔽ��h���i�j�����Ă��邩��j
	}
}


//======================
//�`�揈��
//======================
void CParticles001::Draw()
{
	CObject3D::DrawEffect(); //�`�揈��
}


//========================
//��������
//========================
CParticles001* CParticles001::Create(D3DXVECTOR3 pos)
{
	CParticles001* pPraticles = new CParticles001(2); //���I�m��

	//��񂪂��鎞
	if (pPraticles != nullptr)
	{
		//�������ɐ���������
		if (SUCCEEDED(pPraticles->Init()))
		{
			pPraticles->SetPos(pos);        //�ʒu�������Ɠ���������
			pPraticles->CObject3D::Lood();  //�e�N�X�`���̓ǂݍ���
			return pPraticles;              //����Ԃ�
		}
	}

	return nullptr;                         //����Ԃ�
}