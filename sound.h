//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
// aaadvf
//
//=============================================================================

//=============================================================================
//
//class���ɕύX
//Auther:Haruki Chiba
//
//=============================================================================


#ifndef _SOUND_H_
#define _SOUND_H_


//=============================================================================
//�C���N���[�h
#include "main.h"

//*****************************************************************************
// �T�E���h�ꗗ
//*****************************************************************************

//�T�E���h�N���X
class CSound
{
public:

	//�����̏������[
	typedef struct
	{
		const char* pFilename;	// �t�@�C����
		float Volume;           //���ʒ���
		int nCntLoop;		    // ���[�v�J�E���g
	} SOUNDINFO;

	enum class SOUND_LABEL
	{
		SOUND_LABEL_ITEM_GET = 0,  //�A�C�e�����l��
		SOUND_LABEL_BOSSBGM,	   //�{�X��pBGM
		SOUND_LABEL_NORMALBGM,	   //�ʏ�BGM
		SOUND_LABEL_SE_JUMP,	   // �W�����v��
		SOUND_LABEL_SE_SHOT,       //���Ƃ��̉�
		SOUND_LABEL_SE_CHARGE,     //�`���[�W�������̉��i�v���C���[�̕K�E�Z�j
		SOUND_LABEL_SE_WING,       //���̉�
		SOUND_LABEL_MAX,           //�����̍ő吔
	};

	CSound();  //�R���X�g���N�^
	~CSound(); //�f�X�g���N�^

	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition); //�`�����N�̃`�F�b�N�֐�
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset); //�`�����N�f�[�^�̓ǂݍ��݊֐�

	HRESULT InitSound(HWND hWnd);           //����������
	void UninitSound();                     //�I������
	HRESULT PlaySound(SOUND_LABEL label);   //�����̍Đ�����
	void StopSound(SOUND_LABEL label);      //�w�肵�������̒�~����
	void StopSound();                       //�����̒�~

private:
	IXAudio2* g_pXAudio2 = nullptr;								                    // XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice* g_pMasteringVoice = nullptr;			                // �}�X�^�[�{�C�X
	IXAudio2SourceVoice* g_apSourceVoice[(int)SOUND_LABEL::SOUND_LABEL_MAX] = {};	// �\�[�X�{�C�X
	BYTE* g_apDataAudio[(int)SOUND_LABEL::SOUND_LABEL_MAX] = {};					// �I�[�f�B�I�f�[�^
	DWORD g_aSizeAudio[(int)SOUND_LABEL::SOUND_LABEL_MAX] = {};					    // �I�[�f�B�I�f�[�^�T�C�Y
};

#endif
