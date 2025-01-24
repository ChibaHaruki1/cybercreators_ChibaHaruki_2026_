//=========================================
//
//�S�I�u�W�F�N�g�̏���[object.cpp] 
//Auther:Chiba Haruki
//
//=========================================


//=========================================
//�C���N���[�h
#include "main.h"
#include "object.h"
#include "object3D.h"
#include "manager.h"

//�ÓI�����o�[�̏�����
CObject* CObject::m_apObject[MAX_PRIORITY_OBJ][MAX_OBJECT] = {}; //�S�I�u�W�F�N�g�̏�����


//==========================
//�����t���R���X�g���N�^
//==========================
CObject::CObject(int nPriority)
{
	m_nPriority = nPriority; //�v���C�I���e�B�������Ɠ�������
	m_type = TYPE::NONE;     //�^�C�v������������
	m_nID = 0;               //���g��ID������������

	//�I�u�W�F�N�g����
	for (int nCnt = 0; nCnt < MAX_OBJECT; nCnt++)
	{
		//��񂪂Ȃ��ꍇ
		if (m_apObject[m_nPriority][nCnt] == nullptr)
		{//�󂢂Ă���ꏊ�Ɏ��g��ǉ�

			m_apObject[m_nPriority][nCnt] = this; //�������g����
			m_nID = nCnt;                         //�������g��ID����
			break;                                //������
		}
	}
}


//====================
//�f�X�g���N�^
//====================
CObject::~CObject()
{

}


//====================
//����������
//====================
HRESULT CObject::Init()
{
	return S_OK; //����
}


//====================
//�I������
//====================
void CObject::Uninit()
{

}


//====================
//�X�V����
//====================
void CObject::Update()
{

}


//====================
//�`�揈��
//====================
void CObject::Draw()
{

}


//====================
//�S�I�u�W�F�N�g�̉��
//====================
void CObject::ReleaseAll()
{
	//puriority����
	for (int nCountPri = 0; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//�I�u�W�F�N�g����
		for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
		{
			//��񂪂���ꍇ
			if (m_apObject[nCountPri][nCount] != nullptr)
			{
				m_apObject[nCountPri][nCount]->Release(); //�폜�������Ă�
			}
		}
	}
}


//====================
//�S�I�u�W�F�N�g�̍X�V
//====================
void CObject::UpdateAll()
{
	//puriority����
	for (int nCountPri = 0; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//�I�u�W�F�N�g����
		for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
		{
			//��񂪂���ꍇ
			if (m_apObject[nCountPri][nCount] != nullptr)
			{
				m_apObject[nCountPri][nCount]->Update(); //�X�V�������Ă�
			}
		}
	}

}


//====================
//�S�I�u�W�F�N�g�̕`��
//====================
void CObject::DrawAll()
{
	//puriority����
	for (int nCountPri = 0; nCountPri < MAX_PRIORITY_OBJ; nCountPri++)
	{
		//�I�u�W�F�N�g����
		for (int nCount = 0; nCount < MAX_OBJECT; nCount++)
		{
			//��񂪂���ꍇ
			if (m_apObject[nCountPri][nCount] != nullptr)
			{
				m_apObject[nCountPri][nCount]->Draw(); //�`�揈�����Ă�
			}
		}
	}
}


//=====================
//�������g�̉��
//=====================
void CObject::Release()
{
	int nID = m_nID;             //���g��ID����
	int nPriority = m_nPriority; //���g��priority����

	//��񂪂���ꍇ
	if (m_apObject[nPriority][nID] != nullptr)
	{
		m_apObject[nPriority][nID]->Uninit(); //�I�������i�j���j���Ă�
		delete m_apObject[nPriority][nID];    //�폜����
		m_apObject[nPriority][nID] = nullptr; //���𖳂���
	}
}