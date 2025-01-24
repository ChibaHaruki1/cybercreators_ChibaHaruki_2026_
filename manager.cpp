//===========================================
//
//�S�̂��Ǘ����鏈��[manager.cpp]
//Auther:Chiba Haruki
//
//===========================================


//===========================================
//�C���N���[�h
#include "manager.h"
#include "rendererh.h"


//===========================================
//static�ϐ��̏�����
CRenderer* CManager::m_pRenderer = nullptr;       //�����_���[�̏�����
CInputKeyBoard* CManager::m_pKeyBoard = nullptr;  //�L�[�{�[�h�̏�����
CInputJoyPad* CManager::m_pJyoPad = nullptr;      //JOYPAD�̏�����
CSound* CManager::m_pSound = nullptr;             //�����̏�����
CScene* CManager::m_pScene = nullptr;             //�V�[���̏�����
CInstance* CManager::m_pInstance = nullptr;       //�C���X�^���X�̏�����
CObjectSet* CManager::m_pObjectSet = nullptr;     //�I�u�W�F�N�g�z�u�̏�����
CEvent* CManager::m_pEvent = nullptr;             //�C�x���g�̏�����
CMain* CManager::m_pMain = nullptr;               //���C���̏�����


//===================
//�R���X�g���N�^
//===================
CManager::CManager()
{

}

//===================
//�f�X�g���N�^
//===================
CManager::~CManager()
{

}

//==================
//����������
//==================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	m_pSound = new CSound();                     //���I�m��
	m_pSound->InitSound(hWnd);                   //�����̏�����
							                     
	m_pMain = new CMain();                       //���I�m��
								                 
	m_pRenderer = new CRenderer();               //���I�m�ۂ�����
										         
	m_pKeyBoard = new CInputKeyBoard();          //�L�[�{�[�h�̓��I�m��
										         
	m_pJyoPad = new CInputJoyPad();              //�W���C�p�b�g�̓��I�m��

	m_pRenderer->Init(hInstance, hWnd, bWindow); //�����_���[��Window�̏������Ăяo��

	//�L�[�{�[�h�̏����������Ɏ��s������
	if (FAILED(m_pKeyBoard->Init(hInstance, hWnd)))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//�W���C�p�b�g�̏����������Ɏ��s������
	if (FAILED(m_pJyoPad->Init()))
	{
		return E_FAIL; //���s��Ԃ�
	}

	return S_OK;       //������Ԃ�
}

//==================
//�I������
//==================
void CManager::Uninit()
{
	//�����_���[�̏�񂪂��鎞
	if (m_pRenderer != nullptr)
	{
		m_pRenderer->Uninit(); //�j���������Ă�
		delete m_pRenderer;    //��������
		m_pRenderer = nullptr; //���𖳂���
	}

	//�L�[�{�[�h�̏�񂪂��鎞
	if (m_pKeyBoard != nullptr)
	{
		m_pKeyBoard->Uninit(); //�j���������Ă�
		delete m_pKeyBoard;    //��������
		m_pKeyBoard = nullptr; //���𖳂���
	}


	//�W���C�p�b�g�̏�񂪂��鎞
	if (m_pJyoPad != nullptr)
	{
		m_pJyoPad->Uninit(); //�j���������Ă�
		delete m_pJyoPad;    //��������
		m_pJyoPad = nullptr; //���𖳂���
	}

	//�����̏�񂪂��鎞
	if (m_pSound != nullptr)
	{
		m_pSound->UninitSound(); //�j���������Ă�
		delete m_pSound;         //��������
		m_pSound = nullptr;      //���𖳂���
	}

	//��ʑJ�ڂ̏�񂪂���Ƃ�
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit(); //�j���������Ă�
		delete m_pScene;    //��������
		m_pScene = nullptr; //���𖳂���
	}

	//�C���X�^���X��񂪂���Ƃ�
	if (m_pInstance != nullptr)
	{
		m_pInstance->Uninit(); //�j���������Ă�
		delete m_pInstance;    //��������
		m_pInstance = nullptr; //���𖳂���
	}

	//text�t�@�C���̏�񂪂��鎞
	if (m_pObjectSet != nullptr)
	{
		delete m_pObjectSet;    //��������
		m_pObjectSet = nullptr; //���𖳂���
	}

	//�C�x���g�̏�񂪂��鎞
	if (m_pEvent != nullptr)
	{
		delete m_pEvent;        //��������
		m_pEvent = nullptr;     //���𖳂���
	}

	//���C���̏�񂪂��鎞
	if (m_pMain != nullptr)
	{
		delete m_pMain;         //��������
		m_pMain = nullptr;      //���𖳂���
	}
}

//==================
//�X�V����
//==================
void CManager::Update()
{
	m_pKeyBoard->Update(); //�L�[�{�[�h�̍X�V����
	m_pJyoPad->Update();   //�W���C�p�b�g�̍X�V����
	m_pRenderer->Update(); //�����_���[�̍X�V����
	m_pScene->Update();    //�X�V�������Ă�
	m_pScene->AnyUpdate(); //���̑��X�V�������Ă�(���N���X����p�����Ă��Ȃ��N���X�̏���)
}


//==================
//�`�揈��
//==================
void CManager::Draw()
{
	m_pRenderer->Draw();   //�����_���[�̕`�揈��
}


//===============================
//��ʑJ�ڂ̃��[�h�̕ύX
//===============================
void CManager::SetMode(CScene::MODE mode)
{
	//scene�̏�񂪂��鎞
	if (m_pScene != nullptr)
	{
		m_pScene->Uninit();  //�j���������Ă�
		delete m_pScene;     //��������
		m_pScene = nullptr;  //���𖳂���
	}

	//�C���X�^���X��񂪂���Ƃ�
	if (m_pInstance != nullptr)
	{
		m_pInstance->Uninit();  //�j���������Ă�
		delete m_pInstance;     //��������
		m_pInstance = nullptr;  //���𖳂���
	}

	//event�̏�񂪂��鎞
	if (m_pEvent != nullptr)
	{
		delete m_pEvent;     //��������
		m_pEvent = nullptr;  //���𖳂���
	}

	m_pSound->StopSound();           //�������~�߂�
	m_pInstance = new CInstance();   //�C���X�^���X�̐���
	m_pScene = CScene::Create(mode); //�V�[���̐���

	//�^�C�g���ȊO�̎�text�t�@�C���̏���ǂݍ���
	if (mode != CScene::MODE::MODE_TITLE)
	{
		m_pObjectSet = CObjectSet::Create(); //text����ǂݎ�����I�u�W�F�N�g��z�u����
		m_pEvent = new CEvent();             //���I�m�ۂ���
	}

	//�V�[�������U���g�̎�
	if (mode == CScene::MODE::MODE_RESULT)
	{
		//��񂪂��鎞
		if (m_pObjectSet != nullptr)
		{
			delete m_pObjectSet;     //��������
			m_pObjectSet = nullptr;  //���𖳂���
		}
	}
}
