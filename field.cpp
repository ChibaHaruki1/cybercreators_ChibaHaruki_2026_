//===================================
//
//�n�ʂ̐ݒ�����鏈��[field.cpp]
//Author:chiba haruki
//
//===================================


//===================================
//�C���N���[�h
#include "main.h"
#include "field.h"
#include "rendererh.h"
#include "manager.h"
#include <iostream>
#include <cstdio>


//===================================
//�l�[���X�y�[�X�̐錾
using namespace std; //c++�̊�b�̏ȗ�


//===================================
//������̐ݒ�
string u8FieldText = u8"�n�ʂ̏��ݒ�"; //���{��Ή�


//===================================
//static�ϐ��̏�����
int CField::m_nCountField = 0; //���ꂽ�n�ʂ̏�����


//============================
//�R���X�g���N�^
//============================
CField::CField(int nPriority) : CObject3D(nPriority)
{
	SetSizeX(SIZEX);                             //�����̑傫����ݒ�
	SetFileNamePass("data\\TEXTURE\\bg101.jpg"); //�t�@�C���p�X��ݒ�
}


//============================
//�f�X�g���N�^
//============================
CField::~CField()
{

}


//============================
//����������
//============================
HRESULT CField::Init()
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
void CField::Uninit()
{
	CObject3D::Uninit(); //�j���������Ă�
}

//========================
//�X�V����
//========================
void CField::Update()
{
	SetSize(GetSizeX(), 0.0f, GetSizeX()); //�傫���̐ݒ�

	//if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_1) == true)
	//{
	//	m_fSizeX += 1;
	//}
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_2) == true)
	//{
	//	m_fSizeX -= 1;
	//}
	//else if (CManager::GetKeyBorad()->GetKeyboardPress(DIK_O) == true)
	//{
	//	//TextFileWrite();
	//}
}


//======================================
//�e�L�X�g�t�@�C���ɏ������ޏ���
//======================================
void CField::TextFileWrite(float m_fPosX, float m_fPosY, float m_fPosZ)
{
	FILE* m_pFile;                                       //�t�@�C���|�C���^�[
	m_pFile = fopen("data\\TEXT\\ResultScore.txt", "a"); //�t�@�C����ǂݍ���

	//�t�@�C���̏�񂪖���������
	if (m_pFile == nullptr)
	{
		return; //�����𔲂���
	}

	m_nCountField++;                                                    //���ꂽ���𑝂₷
	fprintf(m_pFile, "%s", "\n\n");                                     //���s
	fprintf(m_pFile, "%s", "#=====================================\n"); //��������������
	fprintf(m_pFile, "%s", "#");                                        //��������������
	fprintf(m_pFile, "%d", m_nCountField);                              //��������������
	fprintf(m_pFile, "%s", u8FieldText.data());                         //��������������(�S�p����)
	fprintf(m_pFile, "%s", "\n");                                       //���s���s��
	fprintf(m_pFile, "%s", "#=====================================\n"); //��������������
	fprintf(m_pFile, "%s", "FILED\n");                                  //��������������
	fprintf(m_pFile, "%s", "		POS = ");                           //�uPOS�v�̕�������������
	fprintf(m_pFile, "%.1f ", m_fPosX);                                 //�u�ʒu�v�̕�������������(�����_��P�܂�)
	fprintf(m_pFile, "%.1f ", m_fPosY);                                 //�u�ʒu�v�̕�������������(�����_��P�܂�)
	fprintf(m_pFile, "%.1f ", m_fPosZ);                                 //�u�ʒu�v�̕�������������(�����_��P�܂�)
	fprintf(m_pFile, "%s", "\n");                                       //���s���s��
	fprintf(m_pFile, "%s", "END_FILED\n");                              //��������������
	fclose(m_pFile);                                                    //�t�@�C�������
}


//======================
//�`�揈��
//======================
void CField::Draw()
{
	CObject3D::Draw(); //���N���X�̕`�揈�����Ă�
}


//========================
//���𐶐�
//========================
CField* CField::Create(D3DXVECTOR3 pos)
{
	CField* pCField = new CField(2); //���I�m��

    //������������������
	if (SUCCEEDED(pCField->Init()))
	{
		pCField->SetPos(pos); //�ʒu�������Ɠ���������
		pCField->Lood();      //�e�N�X�`���̓ǂݍ���
		return pCField;       //����Ԃ�
	}

	return nullptr;               //����Ԃ�
}