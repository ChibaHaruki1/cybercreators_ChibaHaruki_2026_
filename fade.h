//======================================
//
//�t�F�[�h����[fade.h]
//Auther:Chiba Haruki
//
//======================================

#pragma once


//======================================
//�C���N���[�h
#include "object2D.h"


class CFade : public CObject2D
{
public:

	//�t�F�[�h�̎��
	enum class FADE
	{
		FADE_NONE = 0,  //�����Ȃ�
		FADE_IN,        //�t�F�[�h�C��
		FADE_OUT,       //�t�F�[�h�A�E�g
		FADE_MAX        //�ő吔
	};

	CFade(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CFade()override;						  //�f�X�g���N�^
	HRESULT Init()override;					  //����������
	void Uninit()override;					  //�j������
	void  Update()override;					  //�X�V����
	void Draw()override;					  //�`�揈��

	static CFade* Create();                   //��������


	//============================================
	//���̐ݒ�
	void SetFade(FADE fade) { m_Fade = fade; } //�t�F�[�h�̐ݒ�


	//�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	constexpr static int FINISH_FADE_OUT = 255; //�t�F�[�h�A�E�g�̏I������l

private:
	//�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	constexpr static int MAX_FADE_SPEED = 3;    //�t�F�[�h�̏����̐F�̕ω����鑬�x����

	constexpr static int RED = 0;          //�ԐF
	constexpr static int GREEN = 0;        //�ΐF
	constexpr static int BLUE = 0;         //�F

	FADE m_Fade;     //FADE�̏����i�[����ϐ�
};
