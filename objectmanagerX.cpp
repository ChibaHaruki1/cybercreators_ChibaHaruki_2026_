//=========================================
//
//�SX�I�u�W�F�N�g�̏���[objectmanagerX.cpp] 
//Auther:Chiba Haruki
//
//=========================================


//=========================================
//�C���N���[�h
#include "main.h"
#include "manager.h"
#include "objectmanagerX.h"
#include <ppl.h>
//#include "StepTimer.h"
#include <time.h>


//=========================================
//�ÓI�����o�[�̏�����
CObjectManagerX* CObjectManagerX::m_apObjectManagerX[MAX_PRIORITY_MANAGER_OBJ][MAX_OBJECTMANAGERX] = {}; //�SX�I�u�W�F�N�g�̏�����

//using namespace cv;


//==========================
//�����t���R���X�g���N�^
//==========================
CObjectManagerX::CObjectManagerX(int nPriority)
{
	m_nPriority = nPriority; //�v���C�I���e�B�������Ɠ�������
	m_type = TYPE::NONE;     //�^�C�v����������
	m_nID = 0;               //���g��ID������������

	//�I�u�W�F�N�g����
	for (int nCnt = 0; nCnt < MAX_OBJECTMANAGERX; nCnt++)
	{
		//��񂪂Ȃ��ꍇ
		if (m_apObjectManagerX[m_nPriority][nCnt] == nullptr)
		{//�󂢂Ă���ꏊ�Ɏ��g��ǉ�

			m_apObjectManagerX[m_nPriority][nCnt] = this; //�������g����
			m_nID = nCnt;                                 //�������g��ID����
			break;                                        //������
		}
	}
}


//====================
//�f�X�g���N�^
//====================
CObjectManagerX::~CObjectManagerX()
{

}


//====================
//����������
//====================
HRESULT CObjectManagerX::Init()
{
	return S_OK; //����
}


//====================
//�I������
//====================
void CObjectManagerX::Uninit()
{
	//m_nID = 0;
}


//====================
//�X�V����
//====================
void CObjectManagerX::Update()
{

}


//====================
//�`�揈��
//====================
void CObjectManagerX::Draw()
{

}


//====================
//�S�I�u�W�F�N�g�̉��
//====================
void CObjectManagerX::ReleaseAll()
{
	//puriority����(���s����)
	Concurrency::parallel_for(0, CObject::MAX_PRIORITY_OBJ, [&](int nCountPri)
		{
			//�I�u�W�F�N�g����
			for (int nCount = 0; nCount < MAX_OBJECTMANAGERX; nCount++)
			{
				//��񂪂���ꍇ
				if (m_apObjectManagerX[nCountPri][nCount] != nullptr)
				{
					m_apObjectManagerX[nCountPri][nCount]->Release(); //�폜�������Ă�
				}
			}
		});
}


//====================
//�S�I�u�W�F�N�g�̍X�V
//====================
void CObjectManagerX::UpdateAll()
{
	////puriority����(PPLfor��) ���ӓ_�Fskydoom.cpp�̃v���C���[�ƈʒu�̓������A���s�����ɂ��邩��󂪂����������������ɂȂ�
	//Concurrency::parallel_for(0, CObject::MAX_PRIORITY_OBJ, [&](int nCountPri)
	//	{
	//		//�I�u�W�F�N�g����
	//		for (int nCount = 0; nCount < MAX_OBJECTMANAGERX; nCount++)
	//		{
	//			//��񂪂���ꍇ
	//			if (m_apObjectManagerX[nCountPri][nCount] != nullptr)
	//			{
	//				m_apObjectManagerX[nCountPri][nCount]->Update(); //�X�V�������Ă�
	//			}
	//		}
	//	});
	
	//puriority����
	for (int nCountPri = 0; nCountPri < CObject::MAX_PRIORITY_OBJ; nCountPri++)
	{
		//�I�u�W�F�N�g����
		for (int nCount = 0; nCount < MAX_OBJECTMANAGERX; nCount++)
		{
			//��񂪂���ꍇ
			if (m_apObjectManagerX[nCountPri][nCount] != nullptr)
			{
				m_apObjectManagerX[nCountPri][nCount]->Update(); //�X�V�������Ă�
			}
		}
	};
	 
	time_t endTime = time(NULL); //�I��
}


//====================
//�S�I�u�W�F�N�g�̕`��
//====================
void CObjectManagerX::DrawAll()
{
	//puriority����
	for (int nCountPri = 0; nCountPri < CObject::MAX_PRIORITY_OBJ; nCountPri++)
	{
		//�I�u�W�F�N�g����
		for (int nCount = 0; nCount < MAX_OBJECTMANAGERX; nCount++)
		{
			//��񂪂���ꍇ
			if (m_apObjectManagerX[nCountPri][nCount] != nullptr)
			{
				m_apObjectManagerX[nCountPri][nCount]->Draw(); //�`�揈�����Ă�
			}
		}
	}
}


//=====================
//�������g�̉��
//=====================
void CObjectManagerX::Release()
{
	int nID = m_nID;             //���g��ID����
	int nPriority = m_nPriority; //���g��priority����

	//��񂪂���ꍇ
	if (m_apObjectManagerX[nPriority][nID] != nullptr)
	{
		m_apObjectManagerX[nPriority][nID]->Uninit(); //�I�������i�j���j���Ă�
		delete m_apObjectManagerX[nPriority][nID];    //�폜����
		m_apObjectManagerX[nPriority][nID] = nullptr; //���𖳂���
	}
}