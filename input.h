
//=============================================
//
//�L�[�{�[�h�̃v���g�^�C�v�錾[input.h]
//Author:chiba haruki
//
//=============================================

#pragma once

//=============================================
//�C���N���[�h
#include "main.h"


//�L�[�{�[�h�̑�܂��ȏ����N���X
class CInput
{
public:
	CInput();                                                    //�R���X�g���N�^
	virtual ~CInput();                                           //�f�X�g���N�^
	virtual HRESULT Init(HINSTANCE hInstance, HWND hWnd);        //����������
	virtual void Uninit();                                       //�j������
	virtual void Update();                                       //�X�V����

	LPDIRECTINPUT8& GetInput() { return m_Input; }               //���͏����擾
	LPDIRECTINPUTDEVICE8& GetDevice() { return m_Device; }       //�f�o�C�X�����擾

private:
	//�S���͏����ŋ��L
    LPDIRECTINPUT8 m_Input;         //���͏���ۊǂ���p�̕ϐ�
	LPDIRECTINPUTDEVICE8 m_Device;  //�f�o�C�X����ۊǂ���p�̕ϐ�
};


//�L�[�{�[�h�̃N���X
class CInputKeyBoard : public CInput
{
public:
	CInputKeyBoard();                                       //�R���X�g���N�^
	~CInputKeyBoard()override;                              //�f�X�g���N�^
	HRESULT Init(HINSTANCE hInstance, HWND hWnd)override;   //����������
	void Uninit()override;                                  //�j������
	void Update()override;                                  //�X�V����


	//==================================
	//���̎擾
	inline bool  GetKeyboardPress(int nKey) { return ((m_aKeyState[nKey] & 0x80) != 0) ? true : false; }        //�v���X�̏����擾
	inline bool GetKeyboardTrigger(int nKey) { return((m_aKeyStateTrigger[nKey] & 0x80) != 0) ? true : false; } //�g���K�[�̏����擾

private:
	//�}�N����`
	constexpr static int MAX_KEY = 256;                     //�L�[�̍ő吔

	BYTE m_aKeyState[MAX_KEY];                              //�L�[�{�[�h�̏����i�[
	BYTE m_aKeyStateTrigger[MAX_KEY];                       //�L�[�{�[�h�g���K�[�̏����i�[
};

//�W���C�p�b�g�̃N���X
class CInputJoyPad
{
public:

	//�L�[�̎��
	enum class JOYKEY
	{
		JOYKEY_UP = 0, //��L�[
		JOYKEY_DOWN,   //���L�[
		JOYKEY_LEFT,   //���L�[
		JOYKEY_RIGHT,  //�E�L�[
		JOYKEY_START,  //start�L�[
		JOYKEY_BACK,   //back�L�[
		JOYKEY_L3,     //L3�L�[
		JOYKEY_R3,     //R3�L�[
		JOYKEY_LB,     //LB�L�[
		JOYKEY_RB,     //RB�L�[
		JOYKEY_LT,     //LT�L�[
		JOYKEY_RT,     //RT�L�[
		JOYKEY_A,      //A�L�[
		JOYKEY_B,      //B�L�[
		JOYKEY_X,      //X�L�[
		JOYKEY_Y,      //Y�L�[
		JOYKEY_MAX     //�ő吔
	};

	CInputJoyPad();      //�R���X�g���N�^
	~CInputJoyPad();     //�f�X�g���N�^
	HRESULT Init(void);  //����������
	void Uninit(void);   //�j������
	void Update(void);   //�X�V����


	//==================================
	//���̎擾
	inline bool GetJoypadPress(JOYKEY key) { return (m_JyoPad.joykeyState.Gamepad.wButtons & (0x01 << (int)key)); }           //JyoPad�̃v���X����ݒ�
	inline bool GetJoypadTrigger(JOYKEY key) { return (m_JyoPad.joykeyStateTrigger.Gamepad.wButtons & (0x01 << (int)key)); }  //JyoPad�̃g���K�[����ݒ�

private:

	//�R���g���[���[�̍\����
	typedef struct {
		int KeyPressCount;					//�L�[�������Ă鎞�Ԃ̃J�E���g
		int JoyKeyPressCount;				//�L�[�������Ă鎞�Ԃ̃J�E���g
		XINPUT_STATE joykeyState;			//�W���C�p�b�h�̃v���X���
		XINPUT_STATE joykeyStateTrigger;	//�W���C�p�b�h�̃g���K�[���
		int Time;							//���Ԃ��v��
		D3DXVECTOR3 joykeyStickPos;			// �X�e�B�b�N�̌X��
		XINPUT_STATE XInput;				// ���͏��
		XINPUT_STATE joykeyStateRelease;	// �R���g���[���[�̃����[�X���
		XINPUT_STATE joykeyCurrentTime;		// �R���g���[���[�̌��݂̎���
		XINPUT_STATE joykeyExecLastTime;	// �R���g���[���[�̍Ō�ɐ^��Ԃ�������
		XINPUT_STATE joykeyInput;			// �R���g���[���[�̓��͏��
		XINPUT_VIBRATION joykeyMoter;		// �R���g���[���[�̃��[�^�[
		WORD Button;						//�{�^���̔���
		WORD OldButton;						//�Â��{�^���̔���

	}Joypad;

	Joypad m_JyoPad; //JoyPad�̍\���̂̏����i�[����ׂ̕ϐ�
};

