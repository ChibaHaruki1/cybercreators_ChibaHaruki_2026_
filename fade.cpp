//===================================
//
//�t�F�[�h�̏����ݒ�[bg.cpp]
//Author:chiba haruki
//
//===================================


//===================================
//�C���N���[�h
#include "fade.h"
#include "rendererh.h"
#include "manager.h"


//==========================
//�����t���R���X�g���N�^
//==========================
CFade::CFade(int nPriority) : CObject2D(nPriority)
{
	SetAlph(255);                                  //aru�̐ݒ�
	m_Fade = FADE::FADE_IN;                        //�t�F�[�h�̃^�C�v�̏�����
	SetFileNamePass("data\\TEXTURE\\black.jpg");   //�t�@�C���p�X��ݒ�
}


//======================
//�R���X�g���N�^
//======================
CFade::~CFade()
{

}


//======================
//����������
//======================
HRESULT CFade::Init()
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
void CFade::Uninit(void)
{
	CObject2D::Uninit(); //�j���������Ă�
}

//=======================
//�X�V����
//=======================
void CFade::Update()
{
	//�t�F�[�h�C���̎�
	if (m_Fade == FADE::FADE_IN)
	{
		//�A���t�@�n���K��l�ȏ�̎�
		if (GetAlph() >= MAX_FADE_SPEED)
		{
			SetAddjustAlpha() -= MAX_FADE_SPEED;  //�A���t�@�l�����炷
		}

		SetCol(RED, GREEN, BLUE, GetAlph());      //�F�̐ݒ�
	}

	//�t�F�[�h�A�E�g�̎�
	else if (m_Fade == FADE::FADE_OUT)
	{
		//�A���t�@�l���K��l�ȉ��̎�
		if (GetAlph() <= FINISH_FADE_OUT)
		{
			SetAddjustAlpha() += MAX_FADE_SPEED;  //�A���t�@�l�𑝂₷
		}

		SetCol(RED, GREEN, BLUE, GetAlph());      //�F�̐ݒ�
	}
}


//=====================
//�`�揈��
//=====================
void CFade::Draw()
{
	CObject2D::Draw(); //�`�揈�����Ă�
}


//===================================
//�I�u�W�F�N�g����
//===================================
CFade* CFade::Create()
{
	CFade* pFade = new CFade(0); //���I�m��

    //������������������
	if (SUCCEEDED(pFade->Init()))
	{
		pFade->Lood(); //�e�N�X�`���̓ǂݍ���
		return pFade;  //����Ԃ�
	}

	return nullptr;        //����Ԃ�
}
