//=======================================
//
//�X�R�A�̃v���g�^�C�v�錾[score.h]
//Author:chiba haruki
//
//=======================================

#pragma once

//=======================================
//�C���N���[�h
#include "object2D.h"
#include "scene.h"


//============================================================
//�X�R�A�̊Ǘ��N���X
class CManagerScore : public CObject2D
{
public://�O������̃A�N�Z�X�\

	//�e�\���̂̒�`
	typedef struct
	{
		D3DXVECTOR3 pos; //�ʒu
		bool bUse;       //�g�p���Ă��邩�ǂ���
	}Score;

	CManagerScore(int nPriority = DEFAULT_PRIORITY);               //�R���X�g���N�^
	~CManagerScore()override;                                      //�f�X�g���N�^
	 HRESULT Init()override;                                       //������
	 void Uninit()override;                                        //�I������
	 void Update() override;                                       //�X�V����
	 void Draw()override;                                          //�`�揈��
	 void SetScorepos(D3DXVECTOR3 pos);                            //�X�R�A�̈ʒu�ݒ菈��
	 void SetScore(int nScore);                                    //�X�R�A�̐ݒ菈��
	 void AddScore(int nValue);                                    //�X�R�A�̃J�E���g��������
	 void InitAddScore(int nValue);                                //�X�R�A�̃J�E���g��������
	 void PosScore(void);                                          //�X�R�A�̐ݒ菈��
	 static  CManagerScore* Create(CScene::MODE mode, int Number); //�X�R�A�̐�������

	 //�}�N����` �iconstexpr�ŃR���p�C�����ɏ������j
	 constexpr static int MAX_SCORE = 10;             //�X�R�A�̍ő吔
	 constexpr static float DIVISION_SCORE = 0.1f;    //�X�R�A�̍ő吔
	 constexpr static int DIGIT = 10;                 //���Ǘ��p
	 constexpr static int MAX_SIZE_X = 20;            //�X�R�A��X���̑傫��
	 constexpr static int MAX_SIZE_Y = 40;            //�X�R�A��Y���̑傫��
	 constexpr static int MAX_TEXTURE_SIZEX = 10;     //�X�R�A��X���̑傫��
	 constexpr static float FMAX_SCORE = 10.0f;       //�X�R�A�̍ő吔(float�^)
	 constexpr static float PLUSSCORE_POSX = 40.0f;   //�X�R�A��X���̑���������l
	 constexpr static float CORE_POSX = 900.0f;       //�X�R�A��X���̈ʒu
	 constexpr static float CORE_POS1X = 40.0f;       //�X�R�A��X���̈ʒu
	 constexpr static float SCORE_POSY = 60.0f;       //�X�R�A��Y���̈ʒu

private://�O������̃A�N�Z�X�s�\
	Score m_aScore[MAX_SCORE]; //�X�R�A�̏��
	int m_nSocre;              //�X�R�A�̒l��ۊǂ���p
	float m_fPosX;             //�X�R�A�̏������ʒu(x)�̍X�V
	float m_fPosY;             //�X�R�A�̏������ʒu(x)�̍X�V
};


//============================================================
//�Q�[���X�R�A
class CGameScore : public CManagerScore
{
public:
	CGameScore(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CGameScore()override;                         //�f�X�g���N�^
};


//============================================================
//���U���g�X�R�A�N���X
class CResultScore : public CManagerScore
{
public:
	CResultScore(int nPriority = DEFAULT_PRIORITY);  //�R���X�g���N�^
	~CResultScore()override;                         //�f�X�g���N�^
};
