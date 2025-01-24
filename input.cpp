//=================================
//
//���͏���[input.cpp]
//Author:chiba haruki
//
//=================================


//=================================
//�C���N���[�h
#include "input.h"
#include <vector>


//============================================���N���XInput�̏���============================================

//======================
//�R���X�g���N�^
//======================
CInput::CInput()
{
	m_Input = nullptr;  //���͏����̏��̏�����
	m_Device = nullptr; //�f�o�C�X�̏�����
}

//======================
//�f�X�g���N�^
//======================
CInput::~CInput()
{

}


//=============================
//����������
//=============================
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	//��񂪂Ȃ���
	if (m_Input == nullptr)
	{
		//DirectInput�I�u�W�F�N�g�̐����Ɏ��s
		if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_Input, NULL)))
		{
			return E_FAIL; //���s��Ԃ�
		}
	}

	return S_OK;           //������Ԃ�
}


//======================
//�I������
//======================
void CInput::Uninit()
{
	//�f�o�C�X�̏�񂪂��鎞
	if (m_Device != nullptr)
	{
		m_Device->Unacquire(); //���[�h�̎�����
		m_Device->Release();   //��������
		m_Device = nullptr;    //���𖳂���
	}

	//���͏�񂪂��鎞
	if (m_Input != nullptr)
	{
		m_Input->Release();    //��������
		m_Input = nullptr;     //���𖳂���
	}
}


//======================
//�X�V����
//======================
void CInput::Update()
{

}


//============================================�L�[�{�[�h�̏���============================================

//======================
//�R���X�g���N�^
//======================
CInputKeyBoard::CInputKeyBoard()
{
	//std::vector<int>nMAX_KEY;
	//nMAX_KEY.resize(MAX_KEY);

	////�L�[�̍ő吔����
	//for(int& nKey : nMAX_KEY)
	//{
	//	m_aKeyState[nKey] = {};
	//	m_aKeyStateTrigger[nKey] = {};

	//	if (nKey >= MAX_KEY)
	//	{
	//		continue;
	//	}
	//}

	//�L�[�̍ő吔����
	for (int nKey = 0; nKey < MAX_KEY; nKey++)
	{
		m_aKeyState[nKey] = {};        //�v���X���̏�����
		m_aKeyStateTrigger[nKey] = {}; //�g���K�[���̏�����
	}
}

//======================
//�f�X�g���N�^
//======================
CInputKeyBoard::~CInputKeyBoard()
{

}

//===========================
//�L�[�{�[�h�̏���������
//===========================
HRESULT CInputKeyBoard::Init(HINSTANCE hInstance, HWND hWnd)
{
	//�������Ɏ��s������
	if (FAILED(CInput::Init(hInstance, hWnd)))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//���̓f�o�C�X�i�L�[�{�[�h�j�̐����Ɏ��s������
	if (FAILED(GetInput()->CreateDevice(GUID_SysKeyboard, &GetDevice(), NULL)))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//�f�[�^�t�H�[�}�b�g��ݒ�Ɏ��s������
	if (FAILED(GetDevice()->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//�������[�h��ݒ�Ɏ��s������
	if (FAILED(GetDevice()->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL; //���s��Ԃ�
	}

	//�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	GetDevice()->Acquire();

	return S_OK; //������Ԃ�
}

//========================
//�L�[�{�[�h�̏I������
//========================
void CInputKeyBoard::Uninit(void)
{
	CInput::Uninit(); //�I���������Ă�
}


//==========================
//�L�[�{�[�h�̍X�V����
//==========================
void CInputKeyBoard::Update(void)
{
	BYTE aKeyState[MAX_KEY]; //�L�[�{�[�h�̓��͏��
	
	//���̓f�o�C�X����f�[�^���擾�ɐ���������
	if (SUCCEEDED(GetDevice()->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		//�L�[�̍ő吔����
		for (int nCntKey = 0; nCntKey < MAX_KEY; nCntKey++)
		{
			m_aKeyStateTrigger[nCntKey] = (m_aKeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey]; //�L�[�{�[�h�̃g���K�[����ۑ�	
			m_aKeyState[nCntKey] = aKeyState[nCntKey];                                                      //�L�[�{�[�h�̃v���X����ۑ�	
		}
	}
	else
	{
		GetDevice()->Acquire(); //�L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}


//============================================�W���C�p�b�g�̏���============================================


//================================
//�R���X�g���N�^
// //================================
CInputJoyPad::CInputJoyPad()
{

}


//================================
//�f�X�g���N�^
//================================
CInputJoyPad::~CInputJoyPad()
{

}


//==========================================
//�W���C�p�b�h�̏���������
//==========================================
HRESULT CInputJoyPad::Init(void)
{
	//�������̃N���A
	memset(&m_JyoPad.joykeyState, 0, sizeof(XINPUT_STATE));
	memset(&m_JyoPad.joykeyStateTrigger, 0, sizeof(XINPUT_STATE));

	//XInput�̃X�e�[�g�ݒ�(�L���ɂ���)
	XInputEnable(true);

	return S_OK; //������Ԃ�
}

//==========================================
//�W���C�p�b�h�̏I������
//==========================================
void CInputJoyPad::Uninit(void)
{
	//XInput�̃X�e�[�g��ݒ�
	XInputEnable(false);
}


//==========================================
//�W���C�p�b�h�̍X�V����
//==========================================
void CInputJoyPad::Update(void)
{
	XINPUT_STATE joykeystate; //�W���C�p�b�h�̓��͏��

	//�W���C�p�b�h�̏����擾
	if (XInputGetState(0, &joykeystate) == ERROR_SUCCESS)
	{
		m_JyoPad.Button = m_JyoPad.joykeyState.Gamepad.wButtons;                              //�{�^���̏���ݒ�
		m_JyoPad.joykeyStateTrigger.Gamepad.wButtons = m_JyoPad.Button & ~m_JyoPad.OldButton; //�g���K�[�̏���ݒ�
		m_JyoPad.OldButton = m_JyoPad.joykeyState.Gamepad.wButtons;                           //�Â��{�^���̏���ݒ�

		m_JyoPad.joykeyState = joykeystate;                                                   //�W���C�p�b�h�̃v���X����ۑ�
	}
}
